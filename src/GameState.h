/* 
 * File:   GameState.h
 * Author: ANTOINE
 *
 * Created on 17 juin 2016, 23:26
 */
#pragma once

#ifndef GAMESTATE_H
#define	GAMESTATE_H

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
    virtual void load();
    virtual void onEnter();
    virtual void onLeave();
    virtual int mainFunction(float time);
    virtual void update();
    virtual int inputManagement();
    virtual void render();
    virtual void setLoopTime(float time);
    
    TimeEngine* Time;
    InputEngine* Input;
    GraphicEngine* Graphic;
    
protected:
    float m_elapsedTime;
    float m_totalElapsedTime;
    float m_gravityTime;
    GUI* m_guiRoot;
    GUI* m_guiAttackOrderButton;
    GUI* m_guiMoveOrderButton;
    GUI* m_guiStopOrderButton;
    GUI* m_guiHoldOrderButton;
    GUI* m_guiPatrolOrderButton;
};

#endif	/* GAMESTATE_H */

