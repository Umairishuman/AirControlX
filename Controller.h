#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "airline.h"
#include "runway.h"
#include "flight.h"
#include <pthread.h>

class Controller {
    vector<Airline*> airlines;
    vector<Runway*> runways;
    vector<Flight*> arrivals;
    vector<Flight*> departures;

    pthread_t flightGeneratorThread;
    pthread_attr_t flightGeneratorAttr;
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
    } 
    void initilaizeAirlines() {
        airlines.push_back(new Airline(1, "PIA", "Commercial", 6, 4));
        airlines.push_back(new Airline(2, "AirBlue", "Commercial", 4, 4));
        airlines.push_back(new Airline(3, "FedEx", "Cargo", 3, 2));
        airlines.push_back(new Airline(4, "Pakistan Air Force", "Military", 2, 1));
        airlines.push_back(new Airline(5, "Blue Dart", "Cargo", 2, 2));
        airlines.push_back(new Airline(6, "Agha Khan Air Ambulance", "Medical", 2, 1));
    }

    static void* flightGenerator(void* arg){

        // Direction, Flight Type, Time, Emergency Probability
        // North, International Arrivals, Every 3 minutes, 10% (low fuel/diversion)
        // South, Domestic Arrivals, Every 2 minutes, 5% (air ambulance)
        // East, International Departures, Every 2.5 minutes, 15% (military/priority)
        // West, Domestic Departures, Every 4 minutes, 20% (VIP or urgent cargo)
        Controller *controller = (Controller*)arg;


        cout << "Generating flights..." << endl;
        

    }
};

#endif