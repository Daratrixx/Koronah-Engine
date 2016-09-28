
#include "GameStateSTR.h"

GameStateSTR::GameStateSTR() : GameState() {
    m_guiUnitId = null;
    m_cameraHolder = new GameObject();
    m_cameraHolder->setPositionY(30);
    m_cameraHolder->setAngle(-65, 0, 0);
    m_selectedUnitId = -1;

    m_currentState = GAME_NO_STATE;
    m_scanGenerated = false;
}

GameStateSTR::~GameStateSTR() {
    delete m_cameraHolder;
    delete m_heightMapData;
    for (unsigned int i = 0; i < m_objects.size(); i++)
        delete m_objects[i];
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
    gdl->setColor(1, 1, 1, 1);
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
    gdl->setColor(1, 1, 1, 1);
    gdl->setFontSize(0.5f);
    gdl->setTextColor(1, 1, 1);
    gdl->setText("-1");
    m_guiUnitId = gdl;
    m_guiRoot->addChild(gdl);

    m_heightMapData = new HeightMapData("data/heightmap/Sc2wB.bmp");
    m_heightMapData->setModelId(Graphic->createHeightMapModel(m_heightMapData));
    m_heightMapData->setTextureId(1);
    m_heightMapData->setHaloMapId(10);
    m_heightMapData->setPosition(0, 0, 0);
    m_heightMapData->setAngle(0, 0, 0);

    Unit* object;

    for (unsigned int i = 0; i < 10; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            object = new Unit();
            object->setPosition(i * 5, 0, j * 5);
            object->setScale(0.5f, 0.5f, 0.5f);
            //object->setColor(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            object->setDestination(object->getPosition());
            object->setModelId(5);
            object->setTextureId(8);
            object->setHaloMapId(11);
            object->setMovingSpeed(25);
            m_objects.push_back(object);
        }
    }

    object = new Unit();
    object->setPosition(0, 0, 0);
    object->setScale(3, 3, 3);
    object->setColor(0, 0, 0);
    object->setDestination(object->getPosition());
    object->setBehavior(UNIT_BEHAVIOR_HOLD);
    object->setRadius(10);
    object->setModelId(5);
    object->setTextureId(8);
    object->setHaloMapId(11);
    object->setMovingSpeed(0);
    m_objects.push_back(object);

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
    renderSquare();
    Graphic->endRender();
    return order;
}

int GameStateSTR::inputManagement() {
    if (Input->getKeyboardPushed(SDL_SCANCODE_TAB))
        return ORDER_TO_MENU;

    if (Input->getKeyboardDown(SDL_SCANCODE_H)) {
        for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
            m_selectedUnits[i]->setDestination(m_selectedUnits[i]->getPosition());
            m_selectedUnits[i]->setBehavior(UNIT_BEHAVIOR_HOLD);
            m_selectedUnits[i]->setColor(1, 0, 0);
        }
    }

    if (Input->getKeyboardDown(SDL_SCANCODE_LEFT))
        m_cameraHolder->addPosition(50 * m_elapsedTime, 0, 0);
    if (Input->getKeyboardDown(SDL_SCANCODE_RIGHT))
        m_cameraHolder->addPosition(-50 * m_elapsedTime, 0, 0);
    if (Input->getKeyboardDown(SDL_SCANCODE_UP))
        m_cameraHolder->addPosition(0, 0, 50 * m_elapsedTime);
    if (Input->getKeyboardDown(SDL_SCANCODE_DOWN))
        m_cameraHolder->addPosition(0, 0, -50 * m_elapsedTime);
    if (Input->getMouseMoved())
        m_guiRoot->tryHover(Input->getMousePositionX(), Input->getMousePositionY());

    switch (m_currentState) {
        case GAME_NO_STATE:
            if (Input->getMousePushed(SDL_BUTTON_LEFT)) {
                m_currentState = GAME_LEFT_DOWN;
            }
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                glm::vec3 targetPosition = getClickWorldPosition(Input->getMousePositionX(), std::min(Settings_getScreenHeight() - 1.f, (float) Input->getMousePositionY()));
                for (unsigned int i = 0; i < m_selectedUnits.size(); i++)
                    m_selectedUnits[i]->setDestination(targetPosition);
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
                clearSelection();
                m_currentState = GAME_LEFT_SQUARING;
                break;
            }
            if (Input->getMouseReleased(SDL_BUTTON_LEFT)) {
                clearSelection();
                m_selectedUnitId = selectUnit(Input->getMousePositionX(), Input->getMousePositionY());
                m_guiUnitId->setText(toString(m_selectedUnitId));
                if (m_selectedUnitId > -1) {
                    m_selectedUnits.push_back((Unit*) m_objects[m_selectedUnitId]);
                    m_selectedUnits[0]->setColor(0, 1, 0);
                }
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
        case GAME_LEFT_SQUARING:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            if (Input->getMouseMoved())
                m_clicPositionEnd = glm::vec2(Input->getMousePositionX(), Input->getMousePositionY());
            if (Input->getMouseReleased(SDL_BUTTON_LEFT)) {
                doSquareSelection();
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
        case GAME_LEFT_WAIT_UNIT_TARGET:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
        case GAME_LEFT_WAIT_MAP_TARGET:
            if (Input->getMousePushed(SDL_BUTTON_RIGHT)) {
                m_currentState = GAME_NO_STATE;
                break;
            }
            break;
    }

    return ORDER_CONTINUE;
}

void GameStateSTR::clearSelection() {
    for (unsigned int i = 0; i < m_selectedUnits.size(); i++) {
        Unit* u = m_selectedUnits[i];
        u->setColor(1, 1, 1);
    }
    m_selectedUnits.clear();
}

void GameStateSTR::doSquareSelection() {
    glm::vec4 correctScreenSquare;
    correctScreenSquare.x = std::min(m_clicPositionStart.x, m_clicPositionEnd.x);
    correctScreenSquare.y = std::min(Settings_getScreenHeight() - 1.f, std::max(m_clicPositionStart.y, m_clicPositionEnd.y));
    correctScreenSquare.z = std::max(m_clicPositionStart.x, m_clicPositionEnd.x);
    correctScreenSquare.w = std::min(m_clicPositionStart.y, m_clicPositionEnd.y);
    glm::vec3 targetOrigin1 = getClickWorldPosition(correctScreenSquare.x, correctScreenSquare.y);
    glm::vec3 targetOrigin2 = getClickWorldPosition(correctScreenSquare.z, correctScreenSquare.y);
    glm::vec3 targetPosition1 = getClickWorldPosition(correctScreenSquare.z, correctScreenSquare.w);
    glm::vec3 targetPosition2 = getClickWorldPosition(correctScreenSquare.x, correctScreenSquare.w);
    glm::vec2 squarePositions[4];
    squarePositions[0] = glm::vec2(targetOrigin1.x, targetOrigin1.z);
    squarePositions[1] = glm::vec2(targetOrigin2.x, targetOrigin2.z);
    squarePositions[2] = glm::vec2(targetPosition1.x, targetPosition1.z);
    squarePositions[3] = glm::vec2(targetPosition2.x, targetPosition2.z);
    glm::vec4 square;
    square.x = std::min(std::min(targetOrigin1.x, targetOrigin2.x), std::min(targetPosition1.x, targetPosition2.x));
    square.y = std::min(std::min(targetOrigin1.z, targetOrigin2.z), std::min(targetPosition1.z, targetPosition2.z));
    square.z = std::max(std::max(targetOrigin1.x, targetOrigin2.x), std::max(targetPosition1.x, targetPosition2.x));
    square.w = std::max(std::max(targetOrigin1.z, targetOrigin2.z), std::max(targetPosition1.z, targetPosition2.z));
    // m_clicPosition
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        Unit* u = (Unit*) m_objects[i];
        glm::vec2 unitPosition = glm::vec2(u->getPositionX(), u->getPositionZ());
        if (u->getPositionX() > square.x && u->getPositionX() < square.z
                && u->getPositionZ() > square.y && u->getPositionZ() < square.w)
            if (isPointInPolygon(squarePositions, 4, unitPosition)) {
                m_selectedUnits.push_back(u);
                u->setColor(0, 1, 0);
            }
    }
}

void GameStateSTR::update() {
    m_guiRoot->update(m_elapsedTime);
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update(m_elapsedTime, m_objects);
        Graphic->addToRender(m_objects[i]);
    }
}

void GameStateSTR::render() {
    Graphic->moveCamera(m_cameraHolder);
    Graphic->addToRender(m_heightMapData);
    for (unsigned int i = 0; i < m_objects.size(); i++)
        Graphic->addToRender(m_objects[i]);
}

int GameStateSTR::selectUnit(unsigned int x, unsigned int y) {
    if (!m_scanGenerated) {
        Graphic->renderScanStart();
        m_scanGenerated = true;
    }
    int unitId;
    Graphic->renderScanStart();
    // render unselectable stuff
    Graphic->renderObjectScan(m_heightMapData, -1);
    // render selectable stuff
    for (unsigned int i = 0; i < m_objects.size(); i++)
        Graphic->renderObjectScan(m_objects[i], i);
    unitId = Graphic->getScanId(x, y);
    //Graphic->renderScanEnd();
    return unitId;
}

glm::vec3 GameStateSTR::getClickWorldPosition(unsigned int x, unsigned int y) {
    if (!m_scanGenerated) {
        Graphic->renderScanStart();
        m_scanGenerated = true;
    }
    // render unselectable stuff
    Graphic->renderObjectScan(m_heightMapData, -1);
    glm::vec3 pos = Graphic->getUnprojectedPosition(x, y);
    return pos;
}

void GameStateSTR::renderSquare() {
    if (m_currentState == GAME_LEFT_SQUARING) {
        Graphic->renderSquare(m_clicPositionStart, m_clicPositionEnd);
    }
}
