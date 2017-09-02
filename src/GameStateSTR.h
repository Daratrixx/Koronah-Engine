/* 
 * File:   GameStateSTR.h
 * Author: ANTOINE
 *
 * Created on 25 septembre 2016, 11:29
 */

#pragma once

#ifndef GAMESTATESTR_H
#define GAMESTATESTR_H


#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMESTATE_H
#include "GameState.h"
#endif

#ifndef GAMEENGINE_H
#include "GameEngine.h"
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
    virtual UShort mainFunction(float time);
    virtual void update();
    virtual UShort inputManagement();
    virtual UShort mouseInput(SDL_Event & EVENT_QUEUE);
    virtual UShort keyboardInput(SDL_Event & EVENT_QUEUE);
    void inputMoveOrder();
    void inputAttackOrder();
    void inputStopOrder();
    void inputHoldPositionOrder();
    void inputPatrolOrder();
    void inputCancel();
    void clearSelection();
    void doSquareSelection();
    virtual void render();
    void renderSelectionSquare();
    Int getUnitId(UInt x, UInt y);
    glm::vec3 getClickWorldPosition(UInt x, UInt y);

private:
    GUI* m_guiAttackOrderButton;
    GUI* m_guiMoveOrderButton;
    GUI* m_guiStopOrderButton;
    GUI* m_guiHoldOrderButton;
    GUI* m_guiPatrolOrderButton;
    GameObject* m_cameraHolder;
    HeightMapData* m_heightMapData;
    GameEngine m_gameEngine;

    GUI_DynamicLabel* m_guiUnitId;
    Int m_selectedUnitId;
    std::vector<Unit*> m_selectedUnits;
    unsigned int m_currentState;
    glm::vec2 m_clicPositionStart;
    glm::vec2 m_clicPositionEnd;
    bool m_scanGenerated;
};

#endif /* GAMESTATESTR_H */

