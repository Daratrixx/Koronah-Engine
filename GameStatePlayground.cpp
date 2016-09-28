
#include "GameStatePlayground.h"

GameStatePlayground::GameStatePlayground() : GameState() {
    m_player = createDrakkarim("Daratrix", 10);
    m_player->setPosition(0, 15, 0);
    Particle = null;
    Light = null;
    m_guiPlayerStatMenu = null;
    m_guiActiveInterface = null;
}

GameStatePlayground::~GameStatePlayground() {
    delete m_player;
    delete m_heightMapData;
    for (unsigned int i = 0; i < m_objects.size(); i++)
        delete m_objects[i];
}

void GameStatePlayground::load() {
    m_guiRoot = new GUI();
    m_guiRoot->setPosition(0, 0);
    m_guiRoot->setSize(800, 600);
    m_guiRoot->setDisplayColor(false);
    GUI* g = new GUI();
    g->setPosition(10, 10);
    g->setSize(200, 200);
    g->setColor(1, 1, 1, 1);
    g->setTextureID(loadTexture("data/gui/posBar.png"));
    m_guiRoot->addChild(g);
    // stat
    GUI_DynamicLabel* gdl = new GUI_DynamicLabel();
    gdl->setPosition(0, 560);
    gdl->setTextureID(loadTexture("data/gui/lifeBar.png"));
    gdl->setSize(150, 30);
    gdl->setFontSize(0.5f);
    gdl->setSource((void*) m_player);
    gdl->setColor(1, 1, 1, 1);
    gdl->setGetText(GDL_getHealth);
    gdl->setGetTextColor(GDL_getHPColor);
    m_guiRoot->addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(0, 520);
    gdl->setTextureID(loadTexture("data/gui/energyBar.png"));
    gdl->setSize(150, 30);
    gdl->setFontSize(0.5f);
    gdl->setSource((void*) m_player);
    gdl->setColor(1, 1, 1, 1);
    gdl->setGetText(GDL_getConcentration);
    gdl->setGetTextColor(GDL_getENColor);
    m_guiRoot->addChild(gdl);
    // fps
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(650, 560);
    gdl->setTextureID(loadTexture("data/gui/fpsBar.png"));
    gdl->setSize(150, 30);
    gdl->setColor(1, 1, 1, 1);
    gdl->setFontSize(0.5f);
    gdl->setSource((void*) Time);
    gdl->setTextColor(0.75f, 0, 0);
    gdl->setGetText(GDL_getFPS);
    m_guiRoot->addChild(gdl);

    m_guiPlayerStatMenu = new GUI_PlayerStatMenu(m_player);
    m_guiPlayerStatMenu->setVisible(false);
    m_guiRoot->addChild(m_guiPlayerStatMenu);

    m_heightMapData = new HeightMapData("data/heightmap/Sc2wB.bmp");
    m_heightMapData->setModelId(Graphic->createHeightMapModel(m_heightMapData));
    m_heightMapData->setTextureId(1);
    m_heightMapData->setHaloMapId(10);
    m_heightMapData->setPosition(0, 0, 0);
    m_heightMapData->setAngle(0, 0, 0);

    Entity* object;

    object = new Entity();
    object->setPosition(0, 0, 0);
    object->setModelId(3);
    object->setTextureId(6);
    object->setHaloMapId(10);
    m_objects.push_back(object);

    object = new Entity();
    object->setPosition(7, 0, 7);
    object->setAngle(0, 135, 0);
    object->setModelId(4);
    object->setTextureId(7);
    object->setHaloMapId(10);
    m_objects.push_back(object);

    object = new Entity();
    object->setPosition(-7, 0, -7);
    object->setAngle(0, 45, 0);
    object->setModelId(4);
    object->setTextureId(7);
    object->setHaloMapId(10);
    m_objects.push_back(object);

    object = new Entity();
    object->setPosition(70, 0, 15);
    object->setModelId(5);
    object->setTextureId(8);
    object->setHaloMapId(11);
    m_objects.push_back(object);
    object = new Entity();
    object->setPosition(73, 0, 8);
    object->setScale(1.15f, 1.3f, 1.15f);
    object->setModelId(5);
    object->setTextureId(8);
    object->setHaloMapId(11);
    m_objects.push_back(object);
    object = new Entity();
    object->setPosition(77, 0, 11);
    object->setScale(1.5f, 2, 1.5f);
    object->setModelId(5);
    object->setTextureId(8);
    object->setHaloMapId(11);
    m_objects.push_back(object);


    object = new Entity();
    object->setPosition(60, 0, 10);
    object->setScale(3, 3, 3);
    object->setModelId(7);
    object->setTextureId(12);
    object->setHaloMapId(13);
    m_objects.push_back(object);


    object = new Entity();
    object->setPosition(20, 0, 10);
    object->setScale(3, 3, 3);
    object->setModelId(7);
    object->setTextureId(12);
    object->setHaloMapId(14);
    m_objects.push_back(object);


    object = new Entity();
    object->setPosition(50, 0, 50);
    object->setScale(0.2f, 0.2f, 0.2f);
    object->setModelId(6);
    object->setTextureId(9);
    object->setHaloMapId(10);
    m_objects.push_back(object);
}

void GameStatePlayground::onEnter() {
    Input->setCursorLock(true);
    Input->setCursorVisible(false);
}

void GameStatePlayground::onLeave() {
    if (m_guiActiveInterface != null) {
        m_guiActiveInterface->setVisible(false);
        m_guiActiveInterface = null;
    }
}

int GameStatePlayground::mainFunction(float time) {
    Graphic->startRender();
    setLoopTime(time);
    int order = inputManagement();
    update();
    render();
    Graphic->renderPlayGround();
    //Particle->mainFunction(time);
    m_guiRoot->render(Graphic);
    Graphic->endRender();
    return order;
}

int GameStatePlayground::inputManagement() {
    if (Input->getKeyboardPushed(SDL_SCANCODE_TAB))
        return ORDER_TO_MENU;
    if (m_guiActiveInterface == null) {
        if (Input->getKeyboardDown(SDL_SCANCODE_UP) || Input->getKeyboardDown(SDL_SCANCODE_W))
            m_player->moveForward(25 * m_elapsedTime);
        if (Input->getKeyboardDown(SDL_SCANCODE_DOWN) || Input->getKeyboardDown(SDL_SCANCODE_S))
            m_player->moveBack(25 * m_elapsedTime);
        if (Input->getKeyboardDown(SDL_SCANCODE_LEFT) || Input->getKeyboardDown(SDL_SCANCODE_A))
            m_player->moveLeft(25 * m_elapsedTime);
        if (Input->getKeyboardDown(SDL_SCANCODE_RIGHT) || Input->getKeyboardDown(SDL_SCANCODE_D))
            m_player->moveRight(25 * m_elapsedTime);
        if (Input->getKeyboardDown(SDL_SCANCODE_SPACE)) {
            m_player->addSpeed(0, 100 * m_elapsedTime, 0);
            m_player->consume(5 * m_elapsedTime);
        } else m_player->recover(1);
        if (Input->getKeyboardDown(SDL_SCANCODE_Z))
            m_player->moveDown(25 * m_elapsedTime);
        if (Input->getMouseMoved())
            m_player->addAngle(Input->getMousePositionDeltaY()*-0.35f, Input->getMousePositionDeltaX()*-0.35f, 0);
    }

    if (Input->getKeyboardPushed(SDL_SCANCODE_P)) {
        if (m_guiPlayerStatMenu->getVisible()) { // must close and hide cursor
            m_guiPlayerStatMenu->setVisible(false);
            Input->setCursorLock(true);
            Input->setCursorVisible(false);
            m_guiActiveInterface = null;
        } else { // must open and show cursor
            m_guiPlayerStatMenu->setVisible(true);
            Input->setCursorLock(false);
            Input->setCursorVisible(true);
            m_guiActiveInterface = m_guiPlayerStatMenu;
        }
    } else {
        if (Input->getMouseMoved())
            m_guiRoot->tryHover(Input->getMousePositionX(), Input->getMousePositionY());
    }
    if (m_guiActiveInterface != null && Input->getMouseReleased(SDL_BUTTON_LEFT)) {
        GUI* clicked = m_guiRoot->tryClick(Input->getMousePositionX(), Input->getMousePositionY());
        if (m_guiActiveInterface->isCloseButton(clicked)) { // must close and hide cursor
            m_guiActiveInterface->setVisible(false);
            Input->setCursorLock(true);
            Input->setCursorVisible(false);
            m_guiActiveInterface = null;
        }
    }
    return ORDER_CONTINUE;
}

void GameStatePlayground::update() {
    physic(m_player);
    Particle->createParticle(m_objects[0]->getPosition());
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        physic((Entity*) m_objects[i]);
    }
    m_objects[m_objects.size() - 3]->addAngle(0, 90 * m_elapsedTime, 0);
    m_objects[m_objects.size() - 2]->addAngle(0, -90 * m_elapsedTime, 0);
    if (glm::length(m_objects[m_objects.size() - 3]->getPosition() - m_player->getPosition()) < 10)
        m_player->addExperience((int) (m_elapsedTime * 1000));
    if (glm::length(m_objects[m_objects.size() - 2]->getPosition() - m_player->getPosition()) < 10)
        m_player->heal(1);
    m_guiRoot->update(m_elapsedTime);
}

void GameStatePlayground::render() {
    Graphic->moveCamera(m_player);
    Graphic->addToRender(m_heightMapData);
    for (unsigned int i = 0; i < m_objects.size(); i++)
        Graphic->addToRender(m_objects[i]);
}

void GameStatePlayground::physic(Entity* e) {
    e->addSpeed(0, -9.8f * m_gravityTime, 0);
    e->addPosition(e->getSpeed() * m_elapsedTime);
    e->slowMovement(0.75 * (1 - m_elapsedTime));

    float Y = m_heightMapData->collision(e->getPosition());
    if (Y > e->getPosition().y) {
        e->setPositionY(Y);
        e->setSpeedY(0);
    }
}
