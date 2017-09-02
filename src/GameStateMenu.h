/* 
 * File:   GameStateMenu.h
 * Author: ANTOINE
 *
 * Created on 11 août 2016, 10:16
 */

#pragma once

#ifndef GAMESTATEMENU_H
#define	GAMESTATEMENU_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMESTATE_H
#include "GameState.h"
#endif

#ifndef STRING_H
#include "String.h"
#endif

void buttonCallBack();
    
class GameStateMenu : public GameState {
public:
    GameStateMenu();
    virtual ~GameStateMenu();
    virtual void load();
    virtual void onEnter();
    virtual void onLeave();
    virtual UShort mainFunction(float time);
    virtual void update();
    virtual UShort inputManagement();
    virtual UShort mouseInput(SDL_Event & EVENT_QUEUE);
    virtual bool guiMouseUp(SDL_Event & e);
    virtual UShort keyboardInput(SDL_Event & EVENT_QUEUE);
    virtual void render();
    
    
private:
    GUI_Button* m_buttonSwitchToPlayGround;
    GUI_Button* m_buttonSwitchToSettings;
    GUI_Button* m_buttonExit;
};


#endif	/* GAMESTATEMENU_H */

