#ifndef FLIGHT_H
#define FLIGHT_H

#include "aircraft.h"
//yeh flights aur aircrafts ka bahut gehra connection hai
class Flight {
    int id;
    string type;
    string airline;
    string direction;
    int priority;
    bool isEmergency;
    Aircraft* aircraft;
    //har flight ka ek aircraft hai

public:
    Flight(int id, string type, string airline, string direction, int priority, Aircraft* aircraft)
        : id(id), type(type), airline(airline), direction(direction), priority(priority), aircraft(aircraft), isEmergency(false){}

    void setType(string newType) {
        type = newType;
    }
    void setAirline(string newAirline) {
        airline = newAirline;
    }
    void setDirection(string newDirection) {
        direction = newDirection;
    }
    void setPriority(int newPriority) {
        priority = newPriority;
    }
    int getId() const {
        return id;
    }
    string getType() const {
        return type;
    }
    string getAirline() const {
        return airline;
    }
    string getDirection() const {
        return direction;
    }
    int getPriority() const {
        return priority;
    }
    Aircraft* getAircraft() const {
        return aircraft;
    }
    void setAircraft(Aircraft* newAircraft) {
        aircraft = newAircraft;
    }
    bool isEmergencyFlight() const {
        return isEmergency;
    }
    void setEmergencyFlight(bool emergency) {
        isEmergency = emergency;
    }
    

    void printFlightDetails() const {
        cout << "Flight ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Airline: " << airline << endl;
        cout << "Direction: " << direction << endl;
        cout << "Priority: " << priority << endl;
        if (aircraft) {
            cout << "Aircraft Name: " << aircraft->getName() << endl;
            cout << "Aircraft Type: " << aircraft->getType() << endl;
        }
    }
    
};

#endif
