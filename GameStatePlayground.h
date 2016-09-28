#pragma once

#ifndef GAMESTATEPLAYGROUND_H
#define	GAMESTATEPLAYGROUND_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMESTATE_H
#include "GameState.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

#ifndef GEOMETRY_H
#include "Geometry.h"
#endif

#ifndef STRING_H
#include "String.h"
#endif

#ifndef MODEL_H
#include "Model.h"
#endif

#ifndef PARTICLEENGINE_H
#include "ParticleEngine.h"
#endif

#ifndef LIGHTENGINE_H
#include "LightEngine.h"
#endif


class GameStatePlayground : public GameState {
public:
    GameStatePlayground();
    ~GameStatePlayground();
    virtual void load();
    virtual void onEnter();
    virtual void onLeave();
    virtual int mainFunction(float time);
    virtual void update();
    virtual int inputManagement();
    virtual void render();
    virtual void physic(Entity* e);
    
    LightEngine* Light;
    ParticleEngine* Particle;
private:
    Unit* m_player;
    std::vector<GameObject*> m_objects;
    HeightMapData* m_heightMapData;
    
    GUI_Window* m_guiPlayerStatMenu;
    GUI_Window* m_guiActiveInterface;
};

#endif	/* GAMESTATEPLAYGROUND_H */

