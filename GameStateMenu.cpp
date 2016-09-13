
#include "GameStateMenu.h"

void buttonCallBack() {
    std::cout << "I am a call back!" << std::endl;
}

GameStateMenu::GameStateMenu() : GameState() {
    m_buttonSwitchToPlayGround = null;
}

GameStateMenu::~GameStateMenu() {
}

void GameStateMenu::load() {
    m_guiRoot = new GUI();
    m_guiRoot->setPosition(200, 0);
    m_guiRoot->setSize(400, 600);
    m_guiRoot->setColor(0.25f, 0.25f, 0.25f, 0.5f);
    GUI* g = new GUI_Label();
    g->setPosition(200, 450);
    g->setSize(400, 0);
    ((GUI_Label*) g)->setText("Menu");
    ((GUI_Label*) g)->setFontSize(2);
    ((GUI_Label*) g)->setBlinkSpeed(5);
    ((GUI_Label*) g)->setBlinkText(true);
    m_guiRoot->addChild(g);

    m_buttonSwitchToPlayGround = new GUI_Button();
    m_buttonSwitchToPlayGround->setPosition(200, 300);
    m_buttonSwitchToPlayGround->setSize(400, 50);
    m_buttonSwitchToPlayGround->setColor(0, 0, 0.25f, 1);
    m_buttonSwitchToPlayGround->setText("PlayGround");
    m_buttonSwitchToPlayGround->setFontSize(1.5f);
    m_buttonSwitchToPlayGround->setBlinkSpeed(10, GUI_HOVER);
    m_buttonSwitchToPlayGround->setBlinkText(true, GUI_HOVER);
    m_buttonSwitchToPlayGround->setTextColor(0, 0.5f, 0.5f);
    m_buttonSwitchToPlayGround->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonSwitchToPlayGround->setOnClickCallBack(&buttonCallBack);
    m_guiRoot->addChild(m_buttonSwitchToPlayGround);
    
    m_buttonExit = new GUI_Button();
    m_buttonExit->setPosition(200, 200);
    m_buttonExit->setSize(400, 50);
    m_buttonExit->setColor(0, 0, 0.25f, 1);
    m_buttonExit->setText("Exit");
    m_buttonExit->setFontSize(1.5f);
    m_buttonExit->setBlinkSpeed(10, GUI_HOVER);
    m_buttonExit->setBlinkText(true, GUI_HOVER);
    m_buttonExit->setTextColor(0, 0.5f, 0.5f);
    m_buttonExit->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonExit->setOnClickCallBack(&buttonCallBack);
    m_guiRoot->addChild(m_buttonExit);
}

void GameStateMenu::onEnter() {
    Input->setCursorLock(false);
    Input->setCursorVisible(true);
}

void GameStateMenu::onLeave() {

}

int GameStateMenu::mainFunction(float time) {
    Graphic->startRender();
    setLoopTime(time);
    int order = inputManagement();
    update();
    render();
    Graphic->endRender();
    return order;
}

void GameStateMenu::update() {
    m_guiRoot->update(m_elapsedTime);
}

int GameStateMenu::inputManagement() {
    if (Input->getKeyboardPushed(SDL_SCANCODE_TAB))
        return ORDER_TO_PLAYGROUND;
    if (Input->getMouseReleased(SDL_BUTTON_LEFT)) {
        GUI* clicked = m_guiRoot->tryClick(Input->getMousePositionX(), Input->getMousePositionY());
        if (clicked == m_buttonSwitchToPlayGround)
            return ORDER_TO_PLAYGROUND;
        if (clicked == m_buttonExit) {
            return ORDER_EXIT;
        }
    }
    if (Input->getMouseMoved()) {
        m_guiRoot->tryHover(Input->getMousePositionX(), Input->getMousePositionY());
    }
    return ORDER_CONTINUE;
}

void GameStateMenu::render() {
    Graphic->writeLine("FPS " + toString(Time->getFPS()), 10.0f, 575.0f, 1.0f, glm::vec3(0.75, 0, 0));
    m_guiRoot->render(Graphic);
}