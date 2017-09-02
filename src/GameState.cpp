
#include "GameState.h"

bool GameState::KEYBOARD_DOWN[512];
bool GameState::MOUSE_DOWN[8];
Int GameState::MOUSE_POSITION_X = 0;
Int GameState::MOUSE_POSITION_Y = 0;
Int GameState::MOUSE_POSITION_DELTA_X = 0;
Int GameState::MOUSE_POSITION_DELTA_Y = 0;

GameState::GameState() {
    resetInput();
    Graphic = null;
    Input = null;
    Time = null;
    m_elapsedTime = 0;
    m_totalElapsedTime = 0;
    m_gravityTime = 0;
    m_guiRoot = null;
    m_guiHover = null;
    m_guiActive = null;
    m_orderOut = ORDER_CONTINUE;
}

GameState::~GameState() {
    delete m_guiRoot;
}

UShort GameState::mainFunction(float time) {
    return inputManagement();
}

UShort GameState::inputManagement() {
    SDL_Event EVENT_QUEUE;
    UShort out = ORDER_CONTINUE;
    UShort in = ORDER_CONTINUE;
    while (SDL_PollEvent(&EVENT_QUEUE)) {
        // Enregistrement de l'input
        Input->updateEvents(EVENT_QUEUE);
        // Switch sur le type d'évènement
        switch (EVENT_QUEUE.type) {
                // Cas d'une touche enfoncée
            case SDL_KEYDOWN:
                in = keyboardInput(EVENT_QUEUE);
                break;
                // Cas d'une touche relâchée
            case SDL_KEYUP:
                in = keyboardInput(EVENT_QUEUE);
                break;
                // Cas de pression sur un bouton de la souris
            case SDL_MOUSEBUTTONDOWN:
                in = mouseInput(EVENT_QUEUE);
                break;
                // Cas du relâchement d'un bouton de la souris
            case SDL_MOUSEBUTTONUP:
                in = mouseInput(EVENT_QUEUE);
                break;
                // Cas d'un mouvement de souris
            case SDL_MOUSEMOTION:
                in = mouseInput(EVENT_QUEUE);
                break;
            default:
                break;
        }
        if (out == ORDER_CONTINUE)
            out = in;
    }
    return out;
}

UShort GameState::mouseInput(SDL_Event & EVENT_QUEUE) {
    return ORDER_CONTINUE;
}

UShort GameState::keyboardInput(SDL_Event & EVENT_QUEUE) {
    return ORDER_CONTINUE;
}

void GameState::setLoopTime(float time) {
    m_elapsedTime = time;
    m_totalElapsedTime += time;
    m_gravityTime = sqrt(time);
}

void GameState::resetInput() {
    for (UInt i = 0; i < 512; i++)
        KEYBOARD_DOWN[i] = false;
    for (UShort i = 0; i < 8; i++)
        MOUSE_DOWN[i] = false;
    m_guiHover = null;
    m_guiActive = null;
}

bool GameState::guiEvent(SDL_Event & e) {
    std::cout << "guiEvent" << std::endl;
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            return guiMouseDown(e);
            break;
        case SDL_MOUSEBUTTONUP:
            return guiMouseUp(e);
            break;
        case SDL_MOUSEMOTION:
            return guiMouseMotion(e);
            break;
        default: break;
    }
    return false; // event not consumed
}

bool GameState::guiMouseDown(SDL_Event & e) {
    if (m_guiActive != null) {
        return true;
    } else {
        if (e.button.button == SDL_BUTTON_LEFT) {
            glm::vec2 pos(e.button.x, 600 - e.button.y);
            GUI* g = guiTryActive(pos, m_guiRoot);
            m_guiActive = g;
            if (m_guiActive != null && m_guiActive != m_guiRoot) {
                m_guiActive->setMode(GUI_ACTIVE);
                return true;
            }
        }
    }
    return false; // event not consumed
}

bool GameState::guiMouseUp(SDL_Event & e) {
    if (e.button.button == SDL_BUTTON_LEFT) {
        if (m_guiActive != null) {
            if (m_guiActive == m_guiRoot)
                return false; // event not consumed
            glm::vec2 pos(e.button.x, 600 - e.button.y);
            m_guiActive->setMode(GUI_NORMAL);
            m_guiHover->onClick();
            m_guiActive = null;
            return true;
        }
    }
    return false; // event not consumed
}

bool GameState::guiMouseMotion(SDL_Event & e) {
    glm::vec2 pos(e.motion.x, 600 - e.motion.y);
    if (m_guiActive != null && m_guiActive != m_guiRoot) {
        // m_guiActive->mouseMotion();
        return true;
    } else {
        GUI* g = guiTryHover(pos, m_guiRoot);
        if (m_guiHover != null && m_guiHover != m_guiRoot) {
            m_guiHover->onCursorLeave();
            m_guiHover->setMode(GUI_NORMAL);
        }
        m_guiHover = g;
        if (m_guiHover != null && m_guiHover != m_guiRoot) {
            m_guiHover->onCursorEnter();
            m_guiHover->setMode(GUI_HOVER);
            // m_guiHover->mouseMotion();
            return true;
        }
    }
    return false; // event not consumed
}

GUI* GameState::guiTryHover(glm::vec2 pos, GUI* g) {
    if (g != null && g->cursorPositionIn(pos)) {
        unsigned count = g->getChildrenCount();
        GUI* child = null;
        for (UShort i = 0; i < count; i++) {
            child = guiTryHover(pos, g->getChildAt(i));
            if (child != null) {
                return child;
            }
        }
        return g;
    }
    return null;
}

GUI* GameState::guiTryActive(glm::vec2 pos, GUI* g) {
    if (g != null && g->cursorPositionIn(pos)) {
        unsigned count = g->getChildrenCount();
        GUI* child = null;
        for (UShort i = 0; i < count; i++) {
            child = guiTryActive(pos, g->getChildAt(i));
            if (child != null) {
                return child;
            }
        }
        return g;
    }
    return null;
}

GUI* GameState::guiTryClick(glm::vec2 pos, GUI* g) {
    return null;
}

UShort GameState::keyboardDown(SDL_Event & e) {
    //    SDL_Scancode scan = e.key.keysym.scancode;
    //    KEYBOARD_DOWN[scan] = true;
    //    SDL_Keycode key = e.key.keysym.sym;
    //    Uint16 mod = e.key.keysym.mod;
    //    std::string keyName(SDL_GetKeyName(key));
    return ORDER_CONTINUE;
}

UShort GameState::keyboardUp(SDL_Event & e) {
    //    SDL_Scancode scan = e.key.keysym.scancode;
    //    KEYBOARD_DOWN[scan] = false;
    //    SDL_Keycode sym = e.key.keysym.sym;
    //    Uint16 mod = e.key.keysym.mod;
    return ORDER_CONTINUE;
}

UShort GameState::mouseDown(SDL_Event & e) {
    return ORDER_CONTINUE;
}

UShort GameState::mouseUp(SDL_Event & e) {
    return ORDER_CONTINUE;
}

UShort GameState::mouseMotion(SDL_Event & e) {
    return ORDER_CONTINUE;
}