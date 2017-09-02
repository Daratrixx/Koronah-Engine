#pragma once

#ifndef INPUT_H
#define INPUT_H

#ifndef TYPES_H
#include "Types.h"
#endif

enum Command {
    COMMAND_NONE,
    COMMAND_SELECT,
    COMMAND_TARGET,
    COMMAND_GENERIC_ORDER,
    COMMAND_LEFT,
    COMMAND_RIGHT,
    COMMAND_UP,
    COMMAND_DOWN,
    COMMAND_CHAT,
    COMMAND_GRID_00,
    COMMAND_GRID_10,
    COMMAND_GRID_20,
    COMMAND_GRID_30,
    COMMAND_GRID_40,
    COMMAND_GRID_01,
    COMMAND_GRID_11,
    COMMAND_GRID_21,
    COMMAND_GRID_31,
    COMMAND_GRID_41,
    COMMAND_GRID_02,
    COMMAND_GRID_12,
    COMMAND_GRID_22,
    COMMAND_GRID_32,
    COMMAND_GRID_42,
    COMMAND_CREATE_GROUP_0,
    COMMAND_CREATE_GROUP_1,
    COMMAND_CREATE_GROUP_2,
    COMMAND_CREATE_GROUP_3,
    COMMAND_CREATE_GROUP_4,
    COMMAND_CREATE_GROUP_5,
    COMMAND_CREATE_GROUP_6,
    COMMAND_CREATE_GROUP_7,
    COMMAND_CREATE_GROUP_8,
    COMMAND_CREATE_GROUP_9,
    COMMAND_SELECT_GROUP_0,
    COMMAND_SELECT_GROUP_1,
    COMMAND_SELECT_GROUP_2,
    COMMAND_SELECT_GROUP_3,
    COMMAND_SELECT_GROUP_4,
    COMMAND_SELECT_GROUP_5,
    COMMAND_SELECT_GROUP_6,
    COMMAND_SELECT_GROUP_7,
    COMMAND_SELECT_GROUP_8,
    COMMAND_SELECT_GROUP_9,
    COMMAND_KEY_COUNT
};

class InputMapping {
public:

    InputMapping();

    bool load();
    bool save();
    void reset();
    bool remap(const Command & c, const SDL_Scancode & key, const SDL_Keymod & mod);
    bool remap(const Command & c, const Uint8 & button);
    bool remap(const Command & c, const SDL_Event & e);
    bool commandTriggered(const Command & c, const SDL_Event & e) const;

    SDL_Scancode key[COMMAND_KEY_COUNT]; // keyboard
    Uint8 button[COMMAND_KEY_COUNT]; // mouse
    SDL_Keymod mod[COMMAND_KEY_COUNT]; // mod (CTRL/ALT/SHIFT)
    std::string name[COMMAND_KEY_COUNT]; // key/button name
    std::string command[COMMAND_KEY_COUNT]; // command name
};

class InputEngine {
public:
    InputEngine();
    void resetEvents();
    void updateEvents(SDL_Event & event);
    void setCursorVisible(const bool & value);
    void setCursorLock(const bool & value);
    // Getters
    bool getKeyboardDown(const SDL_Scancode & key) const;
    bool getKeyboardPushed(const SDL_Scancode & key) const;
    bool getKeyboardReleased(const SDL_Scancode & key) const;
    bool getMouseDown(const Uint8 & button) const;
    bool getMousePushed(const Uint8 & button) const;
    bool getMouseReleased(const Uint8 & button) const;
    bool getMouseMoved() const;
    // Getters concernant la position du curseur
    Int getMousePositionX() const;
    Int getMousePositionY() const;
    Int getMousePositionDeltaX() const;
    Int getMousePositionDeltaY() const;
private:
    SDL_Event EVENT_QUEUE;
    bool KEYBOARD_DOWN[512];
    bool KEYBOARD_PUSH[512];
    bool KEYBOARD_RELEASE[512];
    bool MOUSE_DOWN[8];
    bool MOUSE_PUCH[8];
    bool MOUSE_RELEASE[8];
    Int MOUSE_POSITION_X;
    Int MOUSE_POSITION_Y;
    Int MOUSE_POSITION_DELTA_X;
    Int MOUSE_POSITION_DELTA_Y;
};

#endif

