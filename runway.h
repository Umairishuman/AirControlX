#ifndef RUNWAY_H
#define RUNWAY_H

#include <iostream>
#include <string>

using namespace std;
class Runway {
    int id;
    string name;
    string direction;
    string type;
    //int length;   //no need right now will think about this later
    //int width;
    bool isAvailable;

public:
    Runway(int id, string name, string direction, string type)
        : id(id), name(name), direction(direction), type(type), isAvailable(true) {}

    void setName(string newName) {
        name = newName;
    }
    void setDirection(string newDirection) {
        direction = newDirection;
    }
    void setType(string newType) {
        type = newType;
    }
    void setAvailability(bool availability) {
        isAvailable = availability;
    }
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    string getDirection() const {
        return direction;
    }
    string getType() const {
        return type;
    }
    bool getAvailability() const {
        return isAvailable;
    }
    void printRunwayDetails() const {
        cout << "Runway ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Direction: " << direction << endl;
        cout << "Type: " << type << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }
    void setRunwayStatus(bool status) {
        isAvailable = status;
    }
    bool isRunwayAvailable() const {
        return isAvailable;
    }
    void setRunwayType(string newType) {
        type = newType;
    }
    string getRunwayType() const {
        return type;
    }
    void setRunwayDirection(string newDirection) {
        direction = newDirection;
    }
    string getRunwayDirection() const {
        return direction;
    }
    void setRunwayId(int newId) {
        id = newId;
    }
    int getRunwayId() const {
        return id;
    }
    void setRunwayName(string newName) {
        name = newName;
    }
    string getRunwayName() const {
        return name;
    }
    void print() const {
        cout << "Runway ID: " << id << "\n"
             << "Name: " << name << "\n"
             << "Direction: " << direction << "\n"
             << "Type: " << type << "\n"
             << "Availability: " << (isAvailable ? "Available" : "Not Available") << "\n";
    }
    
};

#endif