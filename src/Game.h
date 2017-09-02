/* 
 * File:   Game.h
 * Author: ANTOINE
 *
 * Created on 9 août 2016, 10:59
 */
#pragma once

#ifndef GAME_H
#define	GAME_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef SETTINGS_H
#include "Settings.h"
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

#ifndef PARTICLEENGINE_H
#include "ParticleEngine.h"
#endif

#ifndef LIGHTENGINE_H
#include "LightEngine.h"
#endif

#ifndef GAMESTATEPLAYGROUND_H
#include "GameStatePlayground.h"
#endif

#ifndef GAMESTATESTR_H
#include "GameStateSTR.h"
#endif

#ifndef GAMESTATEMENU_H
#include "GameStateMenu.h"
#endif

#ifndef GAMESTATESETTINGS_H
#include "GameStateSettings.h"
#endif

class Game {
public:
    Game();
    Short init();
    void loop();
    void close();
    void switchTo(GameState* state);
    
    // input
    void keyboardDown(SDL_Event & e);
    void keyboardUp(SDL_Event & e);
    void mouseDown(SDL_Event & e);
    void mouseUp(SDL_Event & e);
    void mouseMotion(SDL_Event & e);
    
private:
    TimeEngine Time;
    InputEngine Input;
    GraphicEngine Graphic;
    //LightEngine Light;
    //ParticleEngine Particle;
    InputMapping Mapping;
    
    GameState* m_currentState;
};

#endif /* GAME_H */

