
#include "GameStateMenu.h"

void buttonCallBack() {
    std::cout << "I am a call back!" << std::endl;
}

GameStateMenu::GameStateMenu() : GameState() {
    m_buttonSwitchToPlayGround = null;
    m_buttonSwitchToSettings = null;
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
    m_buttonSwitchToPlayGround->setFontSize(1.25f);
    m_buttonSwitchToPlayGround->setFontSize(1, GUI_ACTIVE);
    m_buttonSwitchToPlayGround->setBlinkSpeed(10, GUI_HOVER);
    m_buttonSwitchToPlayGround->setBlinkText(true, GUI_HOVER);
    m_buttonSwitchToPlayGround->setTextColor(0, 0.5f, 0.5f);
    m_buttonSwitchToPlayGround->setTextColor(0, 1, 1, GUI_HOVER);
    m_guiRoot->addChild(m_buttonSwitchToPlayGround);

    m_buttonSwitchToSettings = new GUI_Button();
    m_buttonSwitchToSettings->setPosition(200, 200);
    m_buttonSwitchToSettings->setSize(400, 50);
    m_buttonSwitchToSettings->setColor(0, 0, 0.25f, 1);
    m_buttonSwitchToSettings->setText("Settings");
    m_buttonSwitchToSettings->setFontSize(1.25f);
    m_buttonSwitchToSettings->setFontSize(1, GUI_ACTIVE);
    m_buttonSwitchToSettings->setBlinkSpeed(10, GUI_HOVER);
    m_buttonSwitchToSettings->setBlinkText(true, GUI_HOVER);
    m_buttonSwitchToSettings->setTextColor(0, 0.5f, 0.5f);
    m_buttonSwitchToSettings->setTextColor(0, 1, 1, GUI_HOVER);
    m_guiRoot->addChild(m_buttonSwitchToSettings);

    m_buttonExit = new GUI_Button();
    m_buttonExit->setPosition(200, 100);
    m_buttonExit->setSize(400, 50);
    m_buttonExit->setColor(0, 0, 0.25f, 1);
    m_buttonExit->setText("Exit");
    m_buttonExit->setFontSize(1.25f);
    m_buttonExit->setFontSize(1, GUI_ACTIVE);
    m_buttonExit->setBlinkSpeed(10, GUI_HOVER);
    m_buttonExit->setBlinkText(true, GUI_HOVER);
    m_buttonExit->setTextColor(0, 0.5f, 0.5f);
    m_buttonExit->setTextColor(0, 1, 1, GUI_HOVER);
    m_guiRoot->addChild(m_buttonExit);

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
}

void GameStateMenu::onEnter() {
    Input->setCursorLock(false);
    Input->setCursorVisible(true);
    resetInput();
    m_orderOut = ORDER_CONTINUE;
    m_guiActive = null;
    m_guiHover = null;
}

void GameStateMenu::onLeave() {

}

UShort GameStateMenu::mainFunction(float time) {
    Graphic->startRender();
    setLoopTime(time);
    UShort order = inputManagement();
    update();
    render();
    Graphic->endRender();
    return order;
}

void GameStateMenu::update() {
    m_guiRoot->update(m_elapsedTime);
}

UShort GameStateMenu::inputManagement() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        // Enregistrement de l'input
        Input->updateEvents(e);
        if (!guiEvent(e)) {
            // Switch sur le type d'évènement
            switch (e.type) {
                    // Cas d'une touche enfoncée
                case SDL_KEYDOWN:
                    m_orderOut = keyboardInput(e);
                    break;
                    // Cas d'une touche relâchée
                case SDL_KEYUP:
                    m_orderOut = keyboardInput(e);
                    break;
                    // Cas de pression sur un bouton de la souris
                case SDL_MOUSEBUTTONDOWN:
                    m_orderOut = mouseInput(e);
                    break;
                    // Cas du relâchement d'un bouton de la souris
                case SDL_MOUSEBUTTONUP:
                    m_orderOut = mouseInput(e);
                    break;
                    // Cas d'un mouvement de souris
                case SDL_MOUSEMOTION:
                    m_orderOut = mouseInput(e);
                    break;
                default:
                    break;
            }
        }
        if (m_orderOut != ORDER_CONTINUE)
            return m_orderOut;
    }
    return ORDER_CONTINUE;
}

UShort GameStateMenu::mouseInput(SDL_Event & EVENT_QUEUE) {
    return ORDER_CONTINUE;
}

bool GameStateMenu::guiMouseUp(SDL_Event & e) {
    if (e.button.button == SDL_BUTTON_LEFT) {
        if (m_guiActive != null) {
            if (m_guiActive == m_guiRoot)
                return false; // event not consumed
            glm::vec2 pos(e.button.x, 600 - e.button.y);
            m_guiActive->setMode(GUI_NORMAL);
            m_guiActive->onClick();
            if (m_guiActive->cursorPositionIn(pos)) {
                if (m_guiActive == m_buttonSwitchToPlayGround) {
                    m_orderOut = ORDER_TO_PLAYGROUND;
                }
                if (m_guiActive == m_buttonSwitchToSettings) {
                    m_orderOut = ORDER_TO_SETTINGS;
                }
                if (m_guiActive == m_buttonExit) {
                    m_orderOut = ORDER_EXIT;
                }
            }
            m_guiActive = null;
            return true;
        }
    }
    return false; // event not consumed
}

UShort GameStateMenu::keyboardInput(SDL_Event & EVENT_QUEUE) {
    if (EVENT_QUEUE.type == SDL_KEYDOWN) {
        if (EVENT_QUEUE.key.keysym.scancode == SDL_SCANCODE_TAB)
            return ORDER_TO_PLAYGROUND;
    }
    return ORDER_CONTINUE;
}

void GameStateMenu::render() {
    m_guiRoot->render(Graphic);
}