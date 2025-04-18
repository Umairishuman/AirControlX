#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "airline.h"
#include "runway.h"
#include <ctime>
#include "flight.h"
#include <pthread.h>
#include <unistd.h>
#include "StartupScreen.h"
#include "MenuScreen.h"
#include "ExitScreen.h"
using namespace std;
using namespace sf;


#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

//some constants for the screen debating whether to add options screen(no marks for it)
#define STARTUP 0
#define MENU 1
#define SIMULATION 2
#define EXIT 3

class Controller {
    vector<Airline*> airlines;
    vector<Runway*> runways;
    vector<Flight*> arrivals;
    vector<Flight*> departures;

    pthread_t flightGeneratorThread;
    pthread_attr_t flightGeneratorAttr;

    // pthread_mutex_t lock;
    
    //dumb screens
    int currentScreenId;
    Screen* currentScreen;
    Screen* startupScreen;
    Screen* menuScreen ;
    Screen* exitScreen;
    // 
    // Screen* simulationScreen;

public:
    Controller() {
        initilaizeAirlines();
        initializeRunways();


        startupScreen = new StartupScreen("Assets/AirControl1.png");
        currentScreen = startupScreen;
        currentScreenId = STARTUP;

        menuScreen = new MenuScreen("Assets/Menu.png");
        exitScreen = new ExitScreen("Assets/Exit.png");
    }
    ~Controller() {
        // Clean up dynamically allocated memory
        for (auto& airline : airlines) {
            delete airline;
        }
        for (auto& runway : runways) {
            delete runway;
        }
        for (auto& flight : arrivals) {
            delete flight;
        }
        for (auto& flight : departures) {
            delete flight;
        
        }
        if(flightGeneratorThread) {
            pthread_cancel(flightGeneratorThread);
        }
        if (startupScreen) {
            delete startupScreen;
        }
        if (menuScreen) {
            delete menuScreen;
        }
        if (exitScreen) {
            delete exitScreen;
        }


    }
    void initializeRunways() {
        runways.push_back(new Runway(1, "RWY-A", "North/South", "Arrival"));
        runways.push_back(new Runway(2, "RWY-B", "East/West", "Departure"));
        runways.push_back(new Runway(3, "RWY-C", "All", "Cargo/Emergency/Military"));


        //testing purposes
        // for(auto &runway : runways){
        //     runway->printRunwayDetails();
        // }
    } 
    void initilaizeAirlines() {
        airlines.push_back(new Airline(1, "PIA", "Commercial", 6, 4));
        airlines.push_back(new Airline(2, "AirBlue", "Commercial", 4, 4));
        airlines.push_back(new Airline(3, "FedEx", "Cargo", 3, 2));
        airlines.push_back(new Airline(4, "Pakistan Air Force", "Military", 2, 1));
        airlines.push_back(new Airline(5, "Blue Dart", "Cargo", 2, 2));
        airlines.push_back(new Airline(6, "Agha Khan Air Ambulance", "Medical", 2, 1));

        //testing purposes
        // for(auto &airline : airlines){
        //     airline->print();
        // }
    }

    void runSimulation(RenderWindow& window){
        //creating the thread to generate flights and making it detachable
        pthread_create(&flightGeneratorThread, &flightGeneratorAttr, flightGenerator, this);
        pthread_attr_init(&flightGeneratorAttr);
        pthread_attr_setdetachstate(&flightGeneratorAttr, PTHREAD_CREATE_DETACHED);
        pthread_attr_destroy(&flightGeneratorAttr);

    }
    void run(){
        
        //creating the sfml window
        bool running = true;
        RenderWindow window(VideoMode(1000, 700), "AirControlX Simulation");
        window.setPosition(Vector2i(100, 0));
        // window.setSize(sf::Vector2u(1000, 700));
        while (window.isOpen() && running) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
                    running = false;
                    window.close();
                    return;
                }
                handle(event, window);        
            }

            // cout << currentScreenId << endl;
            window.clear(Color::Black);
            
            if(currentScreenId == SIMULATION){
                runSimulation(window);
            }
            else {

                currentScreen->Render(window);
                if(currentScreenId == STARTUP && currentScreen->isRunning == false){
                    //so that the startup automatically goes to menu no need to press any key
                    currentScreenId = 1;
                    currentScreen = menuScreen;

                }
            }
            window.display();
        }
    }
    void handle(Event& event, RenderWindow& window) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }
            // all screen will return accordingly
            currentScreenId = currentScreen->handleEvents(window, event);
            
            switch (currentScreenId) {
                case STARTUP:
                    currentScreen = startupScreen;
                    break;
                case MENU:
                    currentScreen = menuScreen;
                    // cout << "Menu Screen not implemented yet." << endl;
                    break;
                case SIMULATION:
                    currentScreen = nullptr;
                    // cout << "Simulation Screen not implemented yet." << endl;
                    break;
                case EXIT:
                    currentScreen = exitScreen;
                    // cout << "Exit Screen not implemented yet." << endl;

                    break;
            }
        }
    }


    bool generateEmergency(double probabilityPercent) {
        if(rand() % 100 < probabilityPercent * 100) {
            return true; // Emergency flight
        }
        return false;
    }
    static Aircraft* selectAvailableAircraft(vector<Aircraft*>& aircrafts) {
        for (auto& aircraft : aircrafts) {
            if (aircraft->getIsAvailable()) {
                aircraft->setIsAvailable(false); // Mark as not available
                return aircraft;
            }
        }
        return nullptr; // No available aircraft
    }
    
    static void* flightGenerator(void* arg) {

        cout << "Flight generator thread started..." << endl;
        // pthread_exit(nullptr);

        Controller* controller = (Controller*)arg;
        srand(time(NULL));
        
        //flight times 
        const double flightTimes[] = {180.0, 120.0, 150, 240.0}; // in minutes


        bool cargoHasBeenGenerated = false;
        double elapsedTime[] = {0.0, 0.0, 0.0, 0.0};
        double emergencyProbabilities[] = {0.1, 0.5, 0.15, 0.2};
        
        // here i am decalaring a variable to hold the arrival intervals
        //the flight should also use an available aircraft
        //so the algo goes like this
        //first i 
        //
        int flightId = 0;
        while (true) {
            for (int i = 0; i < 4; i++) {
                elapsedTime[i] -= 1; // increment elapsed time by 0.1 minutes

                if (elapsedTime[i] <= 0.0) {
                    elapsedTime[i] = flightTimes[i]; // reset elapsed time
                    bool isEmergency = controller->generateEmergency(emergencyProbabilities[i]);
                    string flightType = "";
                    string direction = "";
                    string airlineName = "";
                    Aircraft* aircraft = nullptr;
                    int priority;

                    //first selecting the airline
                    //i am checking if the selected airline has flights left
                    int airlineIndex = rand() % controller->airlines.size();
                    while(controller->airlines[airlineIndex]->getFlightsLeft() == 0){
                        airlineIndex = rand() % controller->airlines.size();
                    }

                    airlineName = controller->airlines[airlineIndex]->getName();
                    controller->airlines[airlineIndex]->setFlightsLeft(controller->airlines[airlineIndex]->getFlightsLeft() - 1);
                    aircraft = selectAvailableAircraft(controller->airlines[airlineIndex]->getAircrafts());
                    flightType = controller->airlines[airlineIndex]-> getType();
                    
                    if(aircraft == nullptr){
                        cout << "No available aircraft for airline: " << controller->airlines[airlineIndex]->getName() << endl;
                        continue; // Skip to the next iteration if no available aircraft
                    }

                    switch (i) {
                        case NORTH:
                            direction = "North";
                            break;
                        case SOUTH:
                            direction = "South";
                            break;
                        case EAST:
                            direction = "East";
                            break;
                        case WEST:
                            direction = "West";
                            break;
                    }
                    
                    
                    Flight* newFlight = new Flight(flightId, flightType, airlineName, direction, priority, nullptr);
                    if (isEmergency) {
                        newFlight->setEmergencyFlight(true);
                    }
                    flightId++;
                    
                    if(direction == "North" || direction == "South"){
                        controller->arrivals.push_back(newFlight);
                    } else {
                        controller->departures.push_back(newFlight);
                    }
                    cout << "============================" << endl;
                    newFlight->printFlightDetails();                  


                    //now here each flight should go on into its seperate thread
                }
            }
            usleep(1000000); 
            
        }  
        return  nullptr;
    }
    // void render(){
    //     //rendering will be done through sfml
    //     //initialize the window

    //     sf::RenderWindow window(sf::VideoMode(800, 600), "Airport Simulation");
    //     while (window.isOpen()) {
    //         sf::Event event;
    //         while (window.pollEvent(event)) {
    //             if (event.type == sf::Event::Closed)
    //                 window.close();
    //         }

    //         window.clear(sf::Color::Black);

    //         // Draw your objects here

    //         window.display();
    //     }
    // }
    
    
};

#endif