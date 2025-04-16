#ifndef AIRLINE_H
#define AIRLINE_H



#include "aircraft.h"
//testing git
class Airline{
    int id;
    string name;
    string type;
    int totalAircrafts;
    int flights;
    vector<Aircraft*> aircrafts;
    

public:
    Airline(int id, string name, string type, int totalAircrafts, int flights) : id(id), name(name), type(type), totalAircrafts(totalAircrafts), flights(flights) {
        string firstTwo = name.substr(0, 2);
        
        // constant varibles for assaan readability

        const int INITIAL_X = 0;
        const int INITIAL_Y = 0;
        const string INITIAL_STATUS = "Grounded";
        const int INITIAL_SPEED = 0;

        for(int i = 0; i < totalAircrafts; i++){
            aircrafts.push_back(new Aircraft(i, firstTwo + to_string(i), type, INITIAL_X, INITIAL_Y, INITIAL_STATUS, INITIAL_SPEED));
        }
    }

    void setName(string newName) {
        name = newName;
    }
    void setType(string newType) {
        type = newType;
    }
    void setTotalAircrafts(int newTotalAircrafts) {
        totalAircrafts = newTotalAircrafts;
    }
    void setFlights(int newFlights) {
        flights = newFlights;
    }
    string getName() const {
        return name;
    }
    string getType() const {
        return type;
    }
    int getTotalAircrafts() const {
        return totalAircrafts;
    }
    int getFlights() const {
        return flights;
    }
    int getId() const {
        return id;
    }
    vector<Aircraft*> getAircrafts() const {
        return aircrafts;
    }
    void addAircraft(Aircraft* aircraft) {
        aircrafts.push_back(aircraft);
        totalAircrafts++;
    }
    
    void displayAircrafts() const {
        for (const auto& aircraft : aircrafts) {
            cout << "Aircraft ID: " << aircraft->getId() << ", Name: " << aircraft->getName() << ", Type: " << aircraft->getType() << endl;
        }
    }
    void print() const {
        std::cout << "Airline ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Type: " << type << "\n"
                  << "Total Aircrafts: " << totalAircrafts << "\n"
                  << "Flights: " << flights << "\n";
    }
    void printAircrafts() const {
        for (const auto& aircraft : aircrafts) {
            aircraft->print();
        }
    }
    ~Airline() {
        for (auto aircraft : aircrafts) {
            delete aircraft; // Free the memory
        }
    }
};

#endif