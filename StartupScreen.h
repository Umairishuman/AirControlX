#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include "Screen.h"
class StartupScreen : public Screen {
public:
    // Sound startSound;
    // SoundBuffer startBuffer;
    Clock* logoClock;
    bool logoDisplayed;
    MySprite logo;

public:
    StartupScreen(string backgroundPath) : Screen(backgroundPath), logo("Assets/AirControl1.png", 0, 0) {
        background.setOpacity(0.5);
        logoClock = nullptr;
        logoDisplayed = false;


        
        // if (!startBuffer.loadFromFile("..\\assets\\music\\Riser.wav")) {
        //     cout << "Error loading sound" << endl;
        // }
        // startSound.setBuffer(startBuffer);
        // startSound.setVolume(50);
        // startSound.setLoop(false);
    } 
    ~StartupScreen() {
        if (logoClock)
            delete logoClock;
    }
    void DisplayLogo(RenderWindow& window) {
        if(logoClock == nullptr) {
            logoClock = new Clock();
        }
        if(logoClock->getElapsedTime().asSeconds() < 4) {
            float opacity = logoClock->getElapsedTime().asSeconds() / 4.0f;
            logo.setOpacity(opacity);
            logo.Draw(window);
        }
        else if (logoClock->getElapsedTime().asSeconds() < 8) {
            float opacity = 1.0f - (logoClock->getElapsedTime().asSeconds() - 4.0f) / 4.0f;
            logo.setOpacity(opacity);
            logo.Draw(window);
        }
        if(logoClock->getElapsedTime().asSeconds() >= 8){
            logoDisplayed = true;

        }
    }
    virtual int handleEvents(RenderWindow& window, Event& event)  {
        if(event.type == Event::KeyPressed) {
            cout << "Key Pressed" << endl;
        }
        // startSound.stop();
        // this->isRunning = false;
        return 0;
    }
    virtual void Render(RenderWindow& window) {
        if (!logoDisplayed) {
            DisplayLogo(window);
            // logoDisplayed = true;
        }
        if(logoDisplayed){
            this->isRunning = false;
        }
            

    }   

};





#endif

// #pragma once
// #ifndef STARTSCREEN_H
// #define STARTSCREEN_H

// #include "Screen.h"
// #include <SFML/Audio.hpp>
// #include <SFML/Graphics.hpp>
// #include <iostream>

// using namespace std;
// using namespace sf;

// class StartScreen : public Screen {
//     Text textContinue;
//     Font font;
//     const string FONT_PATH = "..\\assets\\fonts\\HouseofTerror Regular.ttf";
//     const string START_SOUND_PATH = "..\\assets\\music\\Riser.wav";

//     Clock* flickerClock;
//     float flickerTime;
//     bool visible = true;

//     Sound StartSound;
//     SoundBuffer StartBuffer;
//     Clock* LogoClock;
//     bool logoDisplayed;

// public:
//     StartScreen(string backgroundPath) : Screen(backgroundPath, true) {
//         Background.setOpacity(0.5);
//         if (!font.loadFromFile(FONT_PATH)) {
//             cout << "Error loading font" << endl;
//         }
//         textContinue.setFont(font);
//         textContinue.setString("PRESS ENTER TO CONTINUE!!");
//         textContinue.setCharacterSize(50);
//         textContinue.setFillColor(Color::Green);
//         textContinue.setPosition(250, 250);

//         this->flickerClock = new Clock();
//         this->flickerTime = 0.5;

//         if (!StartBuffer.loadFromFile(START_SOUND_PATH)) {
//             cout << "Error loading sound" << endl;
//         }

//         LogoClock = nullptr;
//         StartSound.setBuffer(StartBuffer);
//         StartSound.setVolume(50);
//         StartSound.setLoop(false);
//         if (StartSound.getStatus() != Sound::Status::Playing) {
//             StartSound.play();
//         }

//         logoDisplayed = false;
//     }

//     ~StartScreen() {
//         if (flickerClock)
//             delete this->flickerClock;
//     }

//     void DisplayLogo(RenderWindow& window) {
//         MySprite logo("..\\assets\\Background\\Logo.png", 0, 0);
//         LogoClock = new Clock();
//         while (LogoClock->getElapsedTime().asSeconds() < 4) {
//             float opacity = LogoClock->getElapsedTime().asSeconds() / 4.0f;
//             logo.setOpacity(opacity);
//             logo.Draw(window);
//             window.display();
//             window.clear();
//         }
//         while (LogoClock->getElapsedTime().asSeconds() < 8) {
//             float opacity = 1.0f - (LogoClock->getElapsedTime().asSeconds() - 4.0f) / 4.0f;
//             logo.setOpacity(opacity);
//             logo.Draw(window);
//             window.display();
//             window.clear();
//         }
//         if (LogoClock)
//             delete LogoClock;
//     }

//     virtual int handleInput(Event event, RenderWindow& window) override {
//         if (event.key.code == Keyboard::Key::Return) {
//             StartSound.stop();
//             this->setVisible(false);
//             return 1;
//         }
//         return -1;
//     }

//     virtual void Draw(RenderWindow& window) override {
//         if (!logoDisplayed) {
//             DisplayLogo(window);
//             logoDisplayed = true;
//         }
//         this->Background.Draw(window);
//         if (flickerClock->getElapsedTime().asSeconds() > flickerTime) {
//             this->visible = !this->visible;
//             flickerClock->restart();
//         }
//         if (this->visible) {
//             window.draw(textContinue);
//         }
//     }
// };

// #endif // STARTSCREEN_H
