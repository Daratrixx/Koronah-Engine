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

class Game {
public:
    Game();
    int init();
    void loop();
    void close();
    void switchTo(GameState* state);
private:
    TimeEngine* Time;
    InputEngine* Input;
    GraphicEngine* Graphic;
    LightEngine* Light;
    ParticleEngine* Particle;
    
    GameState* m_currentState;
};

#endif /* GAME_H */

