#ifndef SCREEN_H
#define SCREEN_H

#include "MySprite.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// #include <SFML/Audio.hpp>

class Screen{
public:
    MySprite background;
    bool isRunning;

    Screen(string path) : background(path, 0, 0), isRunning(true) {
    }

    virtual int handleEvents(RenderWindow& window, Event& event) = 0;
    virtual void Render(RenderWindow& window) = 0;


     
};

#endif