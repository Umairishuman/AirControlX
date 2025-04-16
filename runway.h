#ifndef RUNWAY_H
#define RUNWAY_H

#include <iostream>
#include <string>

using namespace std;
class Runway {
    int id;
    string name;
    string type;
    //int length;   //no need right now will think about this later
    //int width;
    bool isAvailable;

public:
    Runway(int id, string name, string type, bool isAvailable)
        : id(id), name(name), type(type), isAvailable(isAvailable) {}

    void setName(string newName) {
        name = newName;
    }
    void setType(string newType) {
        type = newType;
    }
    void setIsAvailable(bool newIsAvailable) {
        isAvailable = newIsAvailable;
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
    bool getIsAvailable() const {
        return isAvailable;
    }
};

#endif