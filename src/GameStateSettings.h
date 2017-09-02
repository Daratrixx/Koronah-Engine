/* 
 * File:   GameState.h
 * Author: ANTOINE
 *
 * Created on 17 juin 2016, 23:26
 */
#pragma once

#ifndef GAMESTATESETTINGS_H
#define	GAMESTATESETTINGS_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMESTATE_H
#include "GameState.h"
#endif

class GameStateSettings : public GameState {
public:
    GameStateSettings();
    virtual ~GameStateSettings();
    virtual void load();
    virtual void onEnter();
    virtual void onLeave();
    virtual UShort mainFunction(float time);
    virtual void update();
    virtual UShort inputManagement();
    virtual UShort mouseInput(SDL_Event & e);
    virtual UShort keyboardInput(SDL_Event & e);
    virtual void render();
    virtual void setLoopTime(float time);
    
    // input
    virtual UShort keyboardDown(SDL_Event & e);
    virtual UShort keyboardUp(SDL_Event & e);
    virtual UShort mouseDown(SDL_Event & e);
    virtual UShort mouseUp(SDL_Event & e);
    virtual UShort mouseMotion(SDL_Event & e);
    
    TimeEngine* Time;
    InputEngine* Input;
    GraphicEngine* Graphic;
    
protected:
    GUI* m_frameGraphic;
    GUI_InputSettingsPannel* m_frameInput;
    GUI* m_filterMask;
    GUI_Label* m_filterLabel;
    GUI_Button* m_buttonGraphic;
    GUI_Button* m_buttonInput;
    GUI_Button* m_buttonSave;
    GUI_Button* m_buttonClose;
    GUI_Button* m_buttonInputDefault;
    GUI_Label* m_labelCommand[COMMAND_KEY_COUNT];
    
    Uint8 m_currentState;
    Command m_currentCommand;
    GUI* m_currentSlider;
};

#endif	/* GAMESTATESETTINGS_H */

