
#include "GameStateSettings.h"

GameStateSettings::GameStateSettings() : GameState() {
    m_frameGraphic = null;
    m_frameInput = null;
    m_buttonInput = null;
    m_buttonSave = null;
    m_buttonClose = null;
    m_buttonInputDefault = null;
    m_filterMask = null;
    m_filterLabel = null;
}

GameStateSettings::~GameStateSettings() {
}

void GameStateSettings::load() {
    m_guiRoot = new GUI();
    m_guiRoot->setPosition(0, 0);
    m_guiRoot->setSize(800, 600);
    m_guiRoot->setColor(0.25f, 0.25f, 0.25f, 0.5f);
    GUI_Button* b;
    GUI_Label* l;
    GUI* g;

    b = new GUI_Button();
    b->setText("Close");
    b->setPosition(25, 25);
    b->setSize(200, 40);
    b->setColor(0, 0, 0.25f, 1);
    b->setFontSize(1.25f);
    b->setFontSize(1, GUI_ACTIVE);
    b->setBlinkSpeed(10, GUI_HOVER);
    b->setBlinkText(true, GUI_HOVER);
    b->setTextColor(0, 0.5f, 0.5f);
    b->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonClose = b;
    m_guiRoot->addChild(m_buttonClose);

    b = new GUI_Button();
    b->setText("Save");
    b->setPosition(25, 90);
    b->setSize(200, 40);
    b->setColor(0, 0, 0.25f, 1);
    b->setFontSize(1.25f);
    b->setFontSize(1, GUI_ACTIVE);
    b->setBlinkSpeed(10, GUI_HOVER);
    b->setBlinkText(true, GUI_HOVER);
    b->setTextColor(0, 0.5f, 0.5f);
    b->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonSave = b;
    m_guiRoot->addChild(m_buttonSave);

    b = new GUI_Button();
    b->setText("Graphic");
    b->setPosition(25, 525);
    b->setSize(200, 50);
    b->setColor(0, 0, 0.25f, 1);
    b->setFontSize(1.25f);
    b->setFontSize(1, GUI_ACTIVE);
    b->setBlinkSpeed(10, GUI_HOVER);
    b->setBlinkText(true, GUI_HOVER);
    b->setTextColor(0, 0.5f, 0.5f);
    b->setTextColor(0.25f, 0.75f, 0.75f, GUI_NORMAL);
    b->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonGraphic = b;
    m_guiRoot->addChild(m_buttonGraphic);

    b = new GUI_Button();
    b->setText("Input");
    b->setPosition(25, 450);
    b->setSize(200, 50);
    b->setColor(0, 0, 0.25f, 1);
    b->setFontSize(1.25f);
    b->setFontSize(1, GUI_ACTIVE);
    b->setBlinkSpeed(10, GUI_HOVER);
    b->setBlinkText(true, GUI_HOVER);
    b->setTextColor(0, 0.5f, 0.5f);
    b->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonInput = b;
    m_guiRoot->addChild(m_buttonInput);

    m_frameInput = new GUI_InputSettingsPannel();
    m_frameInput->setInputSettingsSource(InputSetting);
    m_frameInput->setVisible(false);
    m_buttonInputDefault = m_frameInput->m_buttonReset;
    m_guiRoot->addChild(m_frameInput);

    g = new GUI();
    g->setPosition(250, 25);
    g->setSize(550, 550);
    g->setColor(0.25f, 0.25f, 0.25f, 0.5f);
    m_frameGraphic = g;
    m_guiRoot->addChild(m_frameGraphic);

    l = new GUI_Label();
    l->setText("Graphic frame");
    l->setPosition(300, 500);
    l->setSize(200, 50);
    l->setColor(0, 0, 0, 0);
    l->setFontSize(1);
    l->setTextColor(1, 1, 1);
    l->setTextAlignement(TEXT_ALIGN_LEFT);
    m_frameGraphic->addChild(l);

    m_filterMask = new GUI();
    m_filterMask->setPosition(0, 0);
    m_filterMask->setSize(800, 600);
    m_filterMask->setColor(0, 0, 0.5f, 0.5f);
    m_filterMask->setVisible(false);
    m_guiRoot->addChild(m_filterMask);
    m_filterLabel = new GUI_Label();
    m_filterLabel->setText("Press combinaison to remap the command - ESCAPE TO CANCEL");
    m_filterLabel->setPosition(0, 500);
    m_filterLabel->setSize(800, 50);
    m_filterLabel->setDisplayColor(false);
    m_filterLabel->setFontSize(0.5f);
    m_filterLabel->setBlinkSpeed(10);
    m_filterLabel->setBlinkText(true);
    m_filterLabel->setTextColor(1, 1, 1);
    m_filterLabel->setTextAlignement(TEXT_ALIGN_CENTER);
    m_filterMask->addChild(m_filterLabel);
}

void GameStateSettings::onEnter() {
    m_currentState = SETTING_NO_STATE;
    m_currentCommand = COMMAND_NONE;
    m_currentSlider = null;
}

void GameStateSettings::onLeave() {
}

void GameStateSettings::update() {
}

void GameStateSettings::render() {
}

UShort GameStateSettings::mainFunction(float time) {
    setLoopTime(time);
    UShort order = inputManagement();
    update();
    Graphic->startRender();
    render();
    Graphic->renderPlayGround();
    m_guiRoot->render(Graphic);
    Graphic->endRender();
    return order;
}

UShort GameStateSettings::inputManagement() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        // Enregistrement de l'input
        Input->updateEvents(e);
        // Analyse de l'input
        if (m_currentState == SETTING_MAPPING) {
            if (m_currentCommand == COMMAND_NONE) {
                m_currentState = SETTING_NO_STATE;
                m_filterMask->setVisible(false);
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode != SDL_SCANCODE_LCTRL
                        && e.key.keysym.scancode != SDL_SCANCODE_RCTRL
                        && e.key.keysym.scancode != SDL_SCANCODE_LALT
                        && e.key.keysym.scancode != SDL_SCANCODE_RALT
                        && e.key.keysym.scancode != SDL_SCANCODE_LSHIFT
                        && e.key.keysym.scancode != SDL_SCANCODE_RSHIFT) {
                    if (InputSetting->remap(m_currentCommand, e)) {
                        std::cout << "remap (" << InputSetting->name[m_currentCommand]
                                << ") " << InputSetting->command[m_currentCommand] << std::endl;
                        m_frameInput->setInputSettingsSource(InputSetting);
                        m_currentState = SETTING_NO_STATE;
                        m_filterMask->setVisible(false);
                    }
                }
            } else if (InputSetting->remap(m_currentCommand, e)) {
                std::cout << "remap (" << InputSetting->name[m_currentCommand]
                        << ") " << InputSetting->command[m_currentCommand] << std::endl;
                m_frameInput->setInputSettingsSource(InputSetting);
                m_currentState = SETTING_NO_STATE;
                m_filterMask->setVisible(false);
                std::cout << "remap done" << std::endl;
            }
        } else if (m_currentState == SETTING_SLIDING) {
            m_currentState = SETTING_NO_STATE;
        } else {
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
            if (m_orderOut != ORDER_CONTINUE)
                return m_orderOut;
        }
    }
    return ORDER_CONTINUE;
}

UShort GameStateSettings::mouseInput(SDL_Event & e) {
    if (e.type == SDL_MOUSEMOTION) {
        return mouseMotion(e);
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        return mouseDown(e);
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        return mouseUp(e);
    }
    return ORDER_CONTINUE;
}

UShort GameStateSettings::keyboardInput(SDL_Event & e) {
    if (e.type == SDL_KEYDOWN) {
        return keyboardDown(e);
    } else if (e.type == SDL_KEYUP) {
        return keyboardUp(e);
    }
    return ORDER_CONTINUE;
}

void GameStateSettings::setLoopTime(float time) {
    m_elapsedTime = time;
    m_totalElapsedTime += time;
    m_gravityTime = sqrt(time);
}

UShort GameStateSettings::keyboardDown(SDL_Event & e) {
    //    SDL_Scancode scan = e.key.keysym.scancode;
    //    KEYBOARD_DOWN[scan] = true;
    //    SDL_Keycode key = e.key.keysym.sym;
    //    Uint16 mod = e.key.keysym.mod;
    //    std::string keyName(SDL_GetKeyName(key));
    return ORDER_CONTINUE;
}

UShort GameStateSettings::keyboardUp(SDL_Event & e) {
    //    SDL_Scancode scan = e.key.keysym.scancode;
    //    KEYBOARD_DOWN[scan] = false;
    //    SDL_Keycode sym = e.key.keysym.sym;
    //    Uint16 mod = e.key.keysym.mod;
    return ORDER_CONTINUE;
}

UShort GameStateSettings::mouseDown(SDL_Event & e) {
    if (e.button.button == SDL_BUTTON_LEFT) {
        if (m_guiHover != null)
            m_guiActive = m_guiHover->tryActive(e.button.x, 600 - e.button.y);
        else
            m_guiActive = m_guiRoot->tryActive(e.button.x, 600 - e.button.y);
    }
    return ORDER_CONTINUE;
}

UShort GameStateSettings::mouseUp(SDL_Event & e) {
    if (e.button.button == SDL_BUTTON_LEFT) {
        GUI* clicked;
        if (m_guiActive != null)
            clicked = m_guiActive->tryClick(e.button.x, 600 - e.button.y);
        else
            clicked = m_guiRoot->tryClick(e.button.x, 600 - e.button.y);
        if (clicked == m_buttonClose) {
            InputSetting->load();
            m_frameInput->setInputSettingsSource(InputSetting);
            return ORDER_TO_MENU;
        } else if (clicked == m_buttonGraphic) {
            m_buttonGraphic->setTextColor(0.25f, 0.75f, 0.75f, GUI_NORMAL);
            m_buttonInput->setTextColor(0, 0.5f, 0.5f, GUI_NORMAL);
            m_frameGraphic->setVisible(true);
            m_frameInput->setVisible(false);
        } else if (clicked == m_buttonInput) {
            m_buttonGraphic->setTextColor(0, 0.5f, 0.5f, GUI_NORMAL);
            m_buttonInput->setTextColor(0.25f, 0.75f, 0.75f, GUI_NORMAL);
            m_frameGraphic->setVisible(false);
            m_frameInput->setVisible(true);
        } else if (clicked == m_frameInput) {
            Command c = m_frameInput->getCommand(e.button.x, 600 - e.button.y);
            std::cout << "(" << c << ") " << InputSetting->command[c] << std::endl;
            m_currentCommand = c;
            if (m_currentCommand != COMMAND_NONE) {
                m_currentState = SETTING_MAPPING;
                m_filterMask->setVisible(true);
            }
        } else if (clicked == m_buttonInputDefault) {
            InputSetting->reset();
            m_frameInput->setInputSettingsSource(InputSetting);
        } else if (clicked == m_buttonSave) {
            InputSetting->save();
            m_frameInput->setInputSettingsSource(InputSetting);
        }
        m_guiActive = null;
    }
    return ORDER_CONTINUE;
}

UShort GameStateSettings::mouseMotion(SDL_Event & e) {
    m_guiRoot->tryHover(e.button.x, 600 - e.button.y);
    return ORDER_CONTINUE;
}