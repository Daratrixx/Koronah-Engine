#pragma once

#ifndef INPUT_H
#define INPUT_H

#ifndef TYPES_H
#include "Types.h"
#endif

class InputEngine {
public:
    InputEngine();
    void updateEvents();
    void setCursorVisible(bool value);
    void setCursorLock(bool value);
    // Getters
    bool getKeyboardDown(const SDL_Scancode key);
    bool getKeyboardPushed(const SDL_Scancode key);
    bool getKeyboardReleased(const SDL_Scancode key);
    bool getMouseDown(const Uint8 button);
    bool getMousePushed(const Uint8 button);
    bool getMouseReleased(const Uint8 button);
    bool getMouseMoved();
    // Getters concernant la position du curseur
    int getMousePositionX();
    int getMousePositionY();
    int getMousePositionDeltaX();
    int getMousePositionDeltaY();
private:
    SDL_Event EVENT_QUEUE;
    bool KEYBOARD_DOWN[512];
    bool KEYBOARD_PUSH[512];
    bool KEYBOARD_RELEASE[512];
    bool MOUSE_DOWN[8];
    bool MOUSE_PUCH[8];
    bool MOUSE_RELEASE[8];
    int MOUSE_POSITION_X;
    int MOUSE_POSITION_Y;
    int MOUSE_POSITION_DELTA_X;
    int MOUSE_POSITION_DELTA_Y;
};

#endif

