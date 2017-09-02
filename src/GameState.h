/* 
 * File:   GameState.h
 * Author: ANTOINE
 *
 * Created on 17 juin 2016, 23:26
 */
#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef TIME_H
#include "Time.h"
#endif

#ifndef INPUT_H
#include "Input.h"
#endif

#ifndef GRAPHICENGINE_H
#include "GraphicEngine.h"
#endif

#ifndef GUI_H
#include "GUI.h"
#endif

class GameState {
public:
    GameState();
    virtual ~GameState();
    virtual void load() = 0;
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual UShort mainFunction(float time);
    virtual void update() = 0;
    virtual UShort inputManagement();
    virtual UShort mouseInput(SDL_Event & EVENT_QUEUE);
    virtual UShort keyboardInput(SDL_Event & EVENT_QUEUE);
    virtual void render() = 0;
    virtual void setLoopTime(float time);

    // input
    void resetInput();
    virtual bool guiEvent(SDL_Event & e);
    virtual bool guiMouseDown(SDL_Event & e);
    virtual bool guiMouseUp(SDL_Event & e);
    virtual bool guiMouseMotion(SDL_Event & e);
    virtual GUI* guiTryHover(glm::vec2 pos, GUI* g);
    virtual GUI* guiTryActive(glm::vec2 pos, GUI* g);
    virtual GUI* guiTryClick(glm::vec2 pos, GUI* g);
    virtual UShort keyboardDown(SDL_Event & e);
    virtual UShort keyboardUp(SDL_Event & e);
    virtual UShort mouseDown(SDL_Event & e);
    virtual UShort mouseUp(SDL_Event & e);
    virtual UShort mouseMotion(SDL_Event & e);

    TimeEngine* Time;
    InputEngine* Input;
    InputMapping* InputSetting;
    GraphicEngine* Graphic;

protected:
    GUI* m_guiRoot;
    GUI* m_guiHover;
    GUI* m_guiActive;
    float m_elapsedTime;
    float m_totalElapsedTime;
    float m_gravityTime;
    UShort m_orderOut;

    static bool INPUT_INIT;
    static bool KEYBOARD_DOWN[512];
    static bool MOUSE_DOWN[8];
    static Int MOUSE_POSITION_X;
    static Int MOUSE_POSITION_Y;
    static Int MOUSE_POSITION_DELTA_X;
    static Int MOUSE_POSITION_DELTA_Y;
};

#endif /* GAMESTATE_H */

