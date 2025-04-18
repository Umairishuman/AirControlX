#ifndef EXITSCREEN_H
#define EXITSCREEN_H

#include "Screen.h"
class ExitScreen : public Screen {  
public:
    ExitScreen(string path) : Screen(path) {
        // Initialize exit screen
    }

    int handleEvents(RenderWindow& window, Event& event) {
        // Handle exit events
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                return 0; // Return to the previous screen
            }
        }
        return 3; // Exit the application
    }

    void Render(RenderWindow& window) {
        // Render the exit screen
        background.Draw(window);
    }
};


#endif