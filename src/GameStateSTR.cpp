
#include "GameStateSTR.h"

GameStateSTR::GameStateSTR() : GameState() {
    m_guiUnitId = null;
    m_cameraHolder = new GameObject();
    m_cameraHolder->setPositionZ(30);
    m_cameraHolder->setAngle(-75, 0, 90);
    m_selectedUnitId = -1;

    m_currentState = GAME_NO_STATE;
    m_scanGenerated = false;
}

GameStateSTR::~GameStateSTR() {
    delete m_cameraHolder;
    delete m_heightMapData;
}

void GameStateSTR::load() {
    m_guiRoot = new GUI();
    m_guiRoot->setPosition(0, 0);
    m_guiRoot->setSize(800, 600);
    m_guiRoot->setDisplayColor(false);
    // fps
    GUI_DynamicLabel* gdl = new GUI_DynamicLabel();
    gdl->setPosition(650, 560);
    gdl->setTextureID(loadTexture("data/gui/fpsBar.png"));
    gdl->setSize(150, 30);
    gdl->setFontSize(0.5f);
    gdl->setSource((void*) Time);
    gdl->setTextColor(0.75f, 0, 0);
    gdl->setGetText(GDL_getFPS);
    m_guiRoot->addChild(gdl);

    // unit selected
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(0, 560);
    gdl->setTextureID(loadTexture("data/gui/lifeBar.png"));
    gdl->setSize(150, 30);
    gdl->setFontSize(0.5f);
    gdl->setTextColor(1, 1, 1);
    gdl->setText("-1");
    m_guiUnitId = gdl;
    m_guiRoot->addChild(gdl);

    GUI_OrderPanel* orderPanel = new GUI_OrderPanel();
    m_guiRoot->addChild(orderPanel);
    m_guiAttackOrderButton = orderPanel->m_orderAttack;
    m_guiMoveOrderButton = orderPanel->m_orderMove;
    m_guiStopOrderButton = orderPanel->m_orderStop;
    m_guiHoldOrderButton = orderPanel->m_orderHold;
    m_guiPatrolOrderButton = orderPanel->m_orderPatrol;

    m_heightMapData = new HeightMapData("data/heightmap/Sc2wB.bmp");
    m_heightMapData->setModelId(Graphic->createHeightMapModel(m_heightMapData));
    m_heightMapData->setTextureId(1);
    m_heightMapData->setHaloMapId(0);
    m_heightMapData->setPositionXYZ(0, 0, 0);
    m_heightMapData->setAngle(0, 0, 0);
}

void GameStateSTR::onEnter() {
    Input->setCursorLock(false);
    Input->setCursorVisible(true);
}

void GameStateSTR::onLeave() {
}

int GameStateSTR::mainFunction(float time) {
    setLoopTime(time);
    m_scanGenerated = false;
    int order = inputManagement();
    update();
    Graphic->startRender();
    render();
    Graphic->renderPlayGround();
    m_guiRoot->render(Graphic);
    renderSelectionSquare();
    Graphic->endRender();
    return order;
}

int GameStateSTR::inputManagement() {
    if (Input->getKeyboardPushed(SDL_SCANCODE_TAB))
        return ORDER_TO_MENU;

    if (Input->getKeyboardDown(SDL_SCANCODE_LEFT))
        m_cameraHolder->addPositionXY(-50 * m_elapsedTime, 0);
    if (Input->getKeyboardDown(SDL_SCANCODE_RIGHT))
        m_cameraHolder->addPositionXY(50 * m_elapsedTime, 0);
    if (Input->getKeyboardDown(SDL_SCANCODE_UP))
        m_cameraHolder->addPositionXY(0, 50 * m_elapsedTime);
    if (Input->getKeyboardDown(SDL_SCANCODE_DOWN))
        m_cameraHolder->addPositionXY(0, -50 * m_elapsedTime);
    if (Input->getMouseMoved())
        m_guiRoot->tryHover(Input->getMousePositionX(), Input->getMousePositionY());

    GUI* active = null;
    GUI* clicked = null;
    switch (m_currentState) {
        case GAME_NO_STATE:
            if (Input->getMouseReleased(SDL_BUTTON_LEFT))
                clicked = m_guiRoot->tryClick(Input->getMousePositionX(), Input->getMousePositionY());
            if (clicked == m_guiMoveOrderButton || Input->getKeyboardPushed(SDL_SCANCODE_Q)) {
                m_currentState = GAME_LEFT_WAIT_ORDER_MOVE;
                break;
            }
            if (clicked == m_guiAttackOrderButton || Input->getKeyboardPushed(SDL_SCANCODE_W)) {
                m_currentState = GAME_LEFT_WAIT_ORDER_ATTACK;
                break;
            }

            if (clicked == m_guiStopOrderButton || Input->getKeyboardPushed(SDL_SCANCODE_E)) {
                for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                    Unit* su = m_selectedUnits[i];
                    if (su->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                        su->orderStop();
                    }
                }
                break;
            }
            if (clicked == m_guiHoldOrderButton || Input->getKeyboardPushed(SDL_SCANCODE_R)) {
                for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                    Unit* su = m_selectedUnits[i];
                    if (su->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                        su->orderHold();
                    }
                }
                break;
            }
            if (clicked == m_guiPatrolOrderButton || Input->getKeyboardPushed(SDL_SCANCODE_T)) {
                m_currentState = GAME_LEFT_WAIT_ORDER_PATROL;
                break;
            }
            if (Input->getMousePushed(SDL_BUTTON_LEFT)) {
                active = m_guiRoot->tryActive(Input->getMousePositionX(), Input->getMousePositionY());
                if (active == null || active == m_guiRoot)
                    m_currentState = GAME_LEFT_DOWN;
            }
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_selectedUnitId = getUnitId(Input->getMousePositionX(), Input->getMousePositionY());
                m_guiUnitId->setText(toString(m_selectedUnitId));
                if (m_selectedUnitId > -1) {
                    Unit* u = m_gameEngine.getUnit(m_selectedUnitId);
                    if (u != null) {
                        for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                            Unit* su = m_selectedUnits[i];
                            m_gameEngine.doRightClick(su, u);
                        }
                    }
                } else {
                    glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(getGraphicSetting()->screenHeight - 1.f, (float) Input->getMousePositionY()));
                    for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                        if (m_selectedUnits[i]->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                            Unit* su = m_selectedUnits[i];
                            m_gameEngine.doRightClick(su, glm::vec2(targetPosition.x, targetPosition.y));
                        }
                    }
                }
            }
            break;
        case GAME_LEFT_DOWN:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseMoved()) {
                m_clicPositionStart = glm::vec2(Input->getMousePositionX(), Input->getMousePositionY());
                m_clicPositionEnd = m_clicPositionStart;
                m_currentState = GAME_LEFT_SQUARING;
                break;
            }
            if (Input->getMouseReleased(SDL_BUTTON_LEFT)) {
                if (!Input->getKeyboardDown(SDL_SCANCODE_LSHIFT))
                    clearSelection();
                m_selectedUnitId = getUnitId(Input->getMousePositionX(), Input->getMousePositionY());
                m_guiUnitId->setText(toString(m_selectedUnitId));
                if (m_selectedUnitId > -1) {
                    Unit* u = m_gameEngine.getUnit(m_selectedUnitId);
                    if (u != null) {
                        if (m_gameEngine.m_currentPlayerId == u->m_ownerId) {
                            u->m_selectionCircleColor = glm::vec3(0, 1, 0);
                            u->m_selectionCircleDisplayed = true;
                        } else if (m_gameEngine.playerIsAlly(m_gameEngine.m_currentPlayerId, u->m_ownerId)) {
                            u->m_selectionCircleColor = glm::vec3(0.75f, 0.75f, 0);
                            u->m_selectionCircleDisplayed = true;
                        } else {
                            u->m_selectionCircleColor = glm::vec3(1, 0, 0);
                            u->m_selectionCircleDisplayed = true;
                        }
                        m_selectedUnits.push_back(u);
                    }
                }
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
        case GAME_LEFT_SQUARING:
            if (Input->getMousePushed(SDL_BUTTON_LEFT)) {
                m_currentState = GAME_LEFT_DOWN;
                break;
            }
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseMoved())
                m_clicPositionEnd = glm::vec2(Input->getMousePositionX(), Input->getMousePositionY());
            if (Input->getMouseReleased(SDL_BUTTON_LEFT)) {
                if (!Input->getKeyboardDown(SDL_SCANCODE_LSHIFT))
                    clearSelection();
                doSquareSelection();
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
        case GAME_LEFT_WAIT_UNIT_TARGET:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) { // cancel input
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseDown(SDL_BUTTON_LEFT)) { // get target
                m_selectedUnitId = getUnitId(Input->getMousePositionX(), Input->getMousePositionY());
                m_guiUnitId->setText(toString(m_selectedUnitId));
                m_currentState = GAME_NO_STATE;
                break;
            }

            break;
        case GAME_LEFT_WAIT_MAP_TARGET:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseDown(SDL_BUTTON_LEFT)) {
                //glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(Settings_getScreenHeight() - 1.f, (float) Input->getMousePositionY()));
                m_currentState = GAME_NO_STATE;
                break;
            }
        case GAME_LEFT_WAIT_ORDER_ATTACK:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseDown(SDL_BUTTON_LEFT)) {
                m_selectedUnitId = getUnitId(Input->getMousePositionX(), Input->getMousePositionY());
                if (m_selectedUnitId > -1) {
                    Unit* u = m_gameEngine.getUnit(m_selectedUnitId);
                    if (u != null) {
                        for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                            Unit* su = m_selectedUnits[i];
                            if (su->getOwnerId() == m_gameEngine.m_currentPlayerId)
                                su->orderAttack(u);
                        }
                    }
                } else {
                    glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(getGraphicSetting()->screenHeight - 1.f, (float) Input->getMousePositionY()));
                    for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                        if (m_selectedUnits[i]->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                            Unit* su = m_selectedUnits[i];
                            su->orderAttackMove(glm::vec2(targetPosition.x, targetPosition.y));
                        }
                    }
                }
                m_currentState = GAME_NO_STATE;
                break;
            }
        case GAME_LEFT_WAIT_ORDER_MOVE:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseDown(SDL_BUTTON_LEFT)) {
                m_selectedUnitId = getUnitId(Input->getMousePositionX(), Input->getMousePositionY());
                if (m_selectedUnitId > -1) {
                    Unit* u = m_gameEngine.getUnit(m_selectedUnitId);
                    if (u != null) {
                        for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                            Unit* su = m_selectedUnits[i];
                            if (su->getOwnerId() == m_gameEngine.m_currentPlayerId)
                                su->orderFollow(u);
                        }
                    }
                } else {
                    glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(getGraphicSetting()->screenHeight - 1.f, (float) Input->getMousePositionY()));
                    for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                        if (m_selectedUnits[i]->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                            Unit* su = m_selectedUnits[i];
                            su->orderMove(glm::vec2(targetPosition.x, targetPosition.y));
                        }
                    }
                }
                m_currentState = GAME_NO_STATE;
                break;
            }
        case GAME_LEFT_WAIT_ORDER_PATROL:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseDown(SDL_BUTTON_LEFT)) {
                glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(getGraphicSetting()->screenHeight - 1.f, (float) Input->getMousePositionY()));
                for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
                    if (m_selectedUnits[i]->getOwnerId() == m_gameEngine.m_currentPlayerId) {
                        Unit* su = m_selectedUnits[i];
                        su->orderAttackMove(glm::vec2(targetPosition.x, targetPosition.y));
                    }
                }
                m_currentState = GAME_NO_STATE;
                break;
            }
        default: break;
    }

    return ORDER_CONTINUE;
}

void GameStateSTR::clearSelection() {
    for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
        Unit* u = m_selectedUnits[i];
        u->m_selectionCircleDisplayed = false;
    }
    m_selectedUnits.clear();
}

void GameStateSTR::doSquareSelection() {
    glm::vec4 correctScreenSquare;
    correctScreenSquare.x = std::min(m_clicPositionStart.x, m_clicPositionEnd.x);
    correctScreenSquare.y = std::min(getGraphicSetting()->screenHeight - 1.f, std::max(m_clicPositionStart.y, m_clicPositionEnd.y));
    correctScreenSquare.z = std::max(m_clicPositionStart.x, m_clicPositionEnd.x);
    correctScreenSquare.w = std::min(m_clicPositionStart.y, m_clicPositionEnd.y);
    glm::vec3 targetOrigin1 = getClickWorldPosition(correctScreenSquare.x, correctScreenSquare.y);
    glm::vec3 targetOrigin2 = getClickWorldPosition(correctScreenSquare.z, correctScreenSquare.y);
    glm::vec3 targetPosition1 = getClickWorldPosition(correctScreenSquare.z, correctScreenSquare.w);
    glm::vec3 targetPosition2 = getClickWorldPosition(correctScreenSquare.x, correctScreenSquare.w);
    glm::vec2 squarePositions[4];
    squarePositions[3] = glm::vec2(targetOrigin1.x, targetOrigin1.y);
    squarePositions[2] = glm::vec2(targetOrigin2.x, targetOrigin2.y);
    squarePositions[1] = glm::vec2(targetPosition1.x, targetPosition1.y);
    squarePositions[0] = glm::vec2(targetPosition2.x, targetPosition2.y);
    glm::vec4 square;
    square.x = std::min(std::min(targetOrigin1.x, targetOrigin2.x), std::min(targetPosition1.x, targetPosition2.x));
    square.y = std::min(std::min(targetOrigin1.y, targetOrigin2.y), std::min(targetPosition1.y, targetPosition2.y));
    square.z = std::max(std::max(targetOrigin1.x, targetOrigin2.x), std::max(targetPosition1.x, targetPosition2.x));
    square.w = std::max(std::max(targetOrigin1.y, targetOrigin2.y), std::max(targetPosition1.y, targetPosition2.y));
    // m_clicPosition
    for (std::list<Unit*>::iterator it = m_gameEngine.m_unitsAll.begin(); it != m_gameEngine.m_unitsAll.end(); it++) {
        Unit* u = *it;
        //if (u->getOwnerId() == m_gameEngine.m_currentPlayerId && u->isAlive()) {
        glm::vec2 unitPosition = u->getPositionXY();
        if (unitPosition.x > square.x && unitPosition.x < square.z
                && unitPosition.y > square.y && unitPosition.y < square.w) {
            if (isPointInPolygon(squarePositions, 4, unitPosition)) {
                if (m_gameEngine.m_currentPlayerId == u->m_ownerId) {
                    u->m_selectionCircleColor = glm::vec3(0, 1, 0);
                    u->m_selectionCircleDisplayed = true;
                } else if (m_gameEngine.playerIsAlly(m_gameEngine.m_currentPlayerId, u->m_ownerId)) {
                    u->m_selectionCircleColor = glm::vec3(0.75f, 0.75f, 0);
                    u->m_selectionCircleDisplayed = true;
                } else {
                    u->m_selectionCircleColor = glm::vec3(1, 0, 0);
                    u->m_selectionCircleDisplayed = true;
                }
                m_selectedUnits.push_back(u);
            }
        }
        //}
    }
}

void GameStateSTR::update() {
    m_guiRoot->update(m_elapsedTime);
    m_gameEngine.gameTick(m_elapsedTime);
}

void GameStateSTR::render() {
    Graphic->moveCamera(m_cameraHolder);
    Graphic->addToRender(m_heightMapData);

    for (std::list<Unit*>::iterator it = m_gameEngine.m_unitsAll.begin(); it != m_gameEngine.m_unitsAll.end(); it++) {
        Unit* u = *it;
        if (u->isAlive())
            Graphic->addToRender(u);
    }
    for (std::list<Missile*>::iterator it = m_gameEngine.m_missiles.begin(); it != m_gameEngine.m_missiles.end(); it++) {
        Missile* m = *it;
        Graphic->addToRender(m);
    }
}

int GameStateSTR::getUnitId(unsigned int x, unsigned int y) {
    if (!m_scanGenerated) {
        Graphic->renderScanStart();
        m_scanGenerated = true;
    }
    int unitId = 0;
    Graphic->renderObjectScan(m_heightMapData, -1);
    for (std::list<Unit*>::iterator it = m_gameEngine.m_unitsAll.begin(); it != m_gameEngine.m_unitsAll.end(); it++) {
        Unit* u = *it;
        if (u->isAlive())
            Graphic->renderObjectScan(u, unitId);
        unitId++;
    }
    unitId = Graphic->getScanId(x, y);

    return unitId;
}

glm::vec3 GameStateSTR::getClickWorldPosition(unsigned int x, unsigned int y) {
    if (!m_scanGenerated) {
        Graphic->renderScanStart();
        Graphic->renderObjectScan(m_heightMapData, -1);
        m_scanGenerated = true;
    }
    // render unselectable stuff
    return Graphic->getUnprojectedPosition(x, y);
}

void GameStateSTR::renderSelectionSquare() {
    if (m_currentState == GAME_LEFT_SQUARING)
        Graphic->renderSquare(m_clicPositionStart, m_clicPositionEnd);
}

