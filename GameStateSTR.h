/* 
 * File:   GameStateSTR.h
 * Author: ANTOINE
 *
 * Created on 25 septembre 2016, 11:29
 */

#pragma once

#ifndef GAMESTATESTR_H
#define	GAMESTATESTR_H


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

class GameStateSTR : public GameState {
public:
    GameStateSTR();
    ~GameStateSTR();
    virtual void load();
    virtual void onEnter();
    virtual void onLeave();
    virtual int mainFunction(float time);
    virtual void update();
    virtual int inputManagement();
    void clearSelection();
    void doSquareSelection();
    virtual void render();
    void renderSquare();
    int selectUnit(unsigned int x, unsigned int y);
    glm::vec3 getClickWorldPosition(unsigned int x, unsigned int y);
    
private:
    bool m_scanGenerated;
    
    GameObject* m_cameraHolder;
    std::vector<GameObject*> m_objects;
    int m_selectedUnit;
    HeightMapData* m_heightMapData;
    
    GUI_DynamicLabel* m_guiUnitId;
    int m_selectedUnitId;
    std::vector<Unit*> m_selectedUnits;
    unsigned int m_currentState;
    glm::vec2 m_clicPositionStart;
    glm::vec2 m_clicPositionEnd;
};

#endif	/* GAMESTATESTR_H */

