#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Aircraft {

    int id;
    string name;
    string type;
    string airline;
    int x, y;
    string status;
    int speed;
    bool isAvailable;

    public:
    Aircraft(int id, string name, string type, int x, int y, string status, int speed)
        : id(id), name(name), type(type), x(x), y(y), status(status), speed(0), isAvailable(true) {}
    
    void setName(string newName) {
        name = newName;
    }
    void setType(string newType) {
        type = newType;
    }
    void setAirline(string newAirline) {
        airline = newAirline;
    }
    void setX(int newX) {
        x = newX;
    }
    void setY(int newY) {
        y = newY;
    }
    void setStatus(string newStatus) {
        status = newStatus;
    }
    void setSpeed(int newSpeed) {
        speed = newSpeed;
    }
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    string getType() const {
        return type;
    }
    string getAirline() const {
        return airline;
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    string getStatus() const {
        return status;
    }
    int getSpeed() const {
        return speed;
    }

    bool getIsAvailable() const {
        return isAvailable;
    }
    void setIsAvailable(bool available) {
        isAvailable = available;
    }

    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }
    void print() const {
        std::cout << "Aircraft ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Type: " << type << "\n"
                  << "Airline: " << airline << "\n"
                  << "Coordinates: (" << x << ", " << y << ")\n"
                  << "Status: " << status << "\n"
                  << "Speed: " << speed << "\n";
    }

};


#endif