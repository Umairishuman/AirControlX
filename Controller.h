#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "airline.h"
#include "runway.h"
#include "flight.h"
#include <pthread.h>

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
    
    static void* flightGenerator(void* arg) {
        Controller* controller = (Controller*)arg;
        srand(time(NULL));
        
        //flight times 
        const double flightTimes[] = {3.0, 2.0, 2.5, 4.0}; // in minutes


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
                elapsedTime[i] += 0.1; // increment elapsed time by 0.1 minutes

                if (elapsedTime[i] == 0.0) {
                    elapsedTime[i] = flightTimes[i]; // reset elapsed time
                    bool isEmergency = controller->generateEmergency(emergencyProbabilities[i]);
                    string flightType;
                    string direction;
                    string airlineName;
                    int priority;

                    switch (i) {
                        case NORTH:
                            flightType = "International Arrivals";
                            direction = "North";
                            airlineName = controller->airlines[0]->getName();
                            priority = 1;
                            break;
                        case SOUTH:
                            flightType = "Domestic Arrivals";
                            direction = "South";
                            airlineName = controller->airlines[1]->getName();
                            priority = 2;
                            break;
                        case EAST:
                            flightType = "International Departures";
                            direction = "East";
                            airlineName = controller->airlines[2]->getName();
                            priority = 3;
                            break;
                        case WEST:
                            flightType = "Domestic Departures";
                            direction = "West";
                            airlineName = controller->airlines[3]->getName();
                            priority = 4;
                            break;
                    }

                    Flight* newFlight = new Flight(flightId++, flightType, airlineName, direction, priority, nullptr);
                    if (isEmergency) {
                        newFlight->setEmergencyFlight(true);
                    }
                    
                    // Add the new flight to the appropriate vector
                    if (i < 2) { // North and South are arrivals
                        controller->arrivals.push_back(newFlight);
                    } else { // East and West are departures
                        controller->departures.push_back(newFlight);
                    }
                    
                    cout << "Generated Flight: ID=" << newFlight->getId() << ", Type=" << flightType << ", Direction=" << direction << ", Airline=" << airlineName << ", Emergency=" << (isEmergency ? "Yes" : "No") << endl;

                }
            }
            usleep(100000); // Sleep for 0.1 seconds
            
        }  
        return  nullptr;
    }
    
    
};

#endif