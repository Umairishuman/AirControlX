#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "airline.h"
#include "runway.h"
#include <ctime>
#include "flight.h"
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <unistd.h>
using namespace std;
using namespace sf;


#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
class Controller {
    vector<Airline*> airlines;
    vector<Runway*> runways;
    vector<Flight*> arrivals;
    vector<Flight*> departures;

    pthread_t flightGeneratorThread;
    pthread_attr_t flightGeneratorAttr;

    pthread_mutex_t lock;
public:
    Controller() {
        initilaizeAirlines();
        initializeRunways();

        //initilize a thread to go into 
        //flightGenerator function
        pthread_attr_init(&flightGeneratorAttr);
        pthread_attr_setdetachstate(&flightGeneratorAttr, PTHREAD_CREATE_DETACHED);
        pthread_create(&flightGeneratorThread, &flightGeneratorAttr, flightGenerator, this);


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

    // static void* flightGenerator(void* arg){

    //     // Direction, Flight Type, Time, Emergency Probability
    //     // North, International Arrivals, Every 3 minutes, 10% (low fuel/diversion)
    //     // South, Domestic Arrivals, Every 2 minutes, 5% (air ambulance)
    //     // East, International Departures, Every 2.5 minutes, 15% (military/priority)
    //     // West, Domestic Departures, Every 4 minutes, 20% (VIP or urgent cargo)
    //     Controller *controller = (Controller*)arg;


    //     cout << "Generating flights..." << endl;

    //     return nullptr;
    // }

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
    void render(){
        //rendering will be done through sfml
        //initialize the window

        sf::RenderWindow window(sf::VideoMode(800, 600), "Airport Simulation");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black);

            // Draw your objects here

            window.display();
        }
    }
    
    
};

#endif