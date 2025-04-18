#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "Screen.h"

class MenuScreen : public Screen {
public:
    MenuScreen(string path) : Screen(path) {
        // Initialize menu screen
    }

    int handleEvents(RenderWindow& window, Event& event) {
        // Handle menu events

        

        //Mahad read this (this function returns what the user selects) 0 was for startup
        //if no change than it should return 1
        //if you switch to simulation screen then return 2
        //if you switch to exit screen then return 3
        return 1; // Return the next screen ID
    }

    void Render(RenderWindow& window) {
        // Render the menu screen
        background.Draw(window);
    }
};

#endif