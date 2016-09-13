
#include "Input.h"

InputEngine::InputEngine() {
    MOUSE_POSITION_X = 0;
    MOUSE_POSITION_Y = 0;
    MOUSE_POSITION_DELTA_X = 0;
    MOUSE_POSITION_DELTA_Y = 0;
    // Initialisation du tableau touches[]
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        KEYBOARD_DOWN[i] = false;
        KEYBOARD_PUSH[i] = false;
        KEYBOARD_RELEASE[i] = false;
    }
    // Initialisation du tableau boutonsSouris[]
    for (int i = 0; i < 8; i++) {
        MOUSE_DOWN[i] = false;
        MOUSE_PUCH[i] = false;
        MOUSE_RELEASE[i] = false;
    }
}

void InputEngine::updateEvents() {
    // Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives
    MOUSE_POSITION_DELTA_X = 0;
    MOUSE_POSITION_DELTA_Y = 0;
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        KEYBOARD_PUSH[i] = false;
        KEYBOARD_RELEASE[i] = false;
    }
    for (int i = 0; i < 8; i++) {
        MOUSE_PUCH[i] = false;
        MOUSE_RELEASE[i] = false;
    }
    // Boucle d'évènements
    while (SDL_PollEvent(&EVENT_QUEUE)) {
        // Switch sur le type d'évènement
        switch (EVENT_QUEUE.type) {
                // Cas d'une touche enfoncée
            case SDL_KEYDOWN:
                if (!KEYBOARD_DOWN[EVENT_QUEUE.key.keysym.scancode])
                    KEYBOARD_PUSH[EVENT_QUEUE.key.keysym.scancode] = true;
                KEYBOARD_DOWN[EVENT_QUEUE.key.keysym.scancode] = true;
                break;
                // Cas d'une touche relâchée
            case SDL_KEYUP:
                if (KEYBOARD_DOWN[EVENT_QUEUE.key.keysym.scancode])
                    KEYBOARD_RELEASE[EVENT_QUEUE.key.keysym.scancode] = true;
                KEYBOARD_DOWN[EVENT_QUEUE.key.keysym.scancode] = false;
                break;
                // Cas de pression sur un bouton de la souris
            case SDL_MOUSEBUTTONDOWN:
                if (!MOUSE_DOWN[EVENT_QUEUE.button.button])
                    MOUSE_PUCH[EVENT_QUEUE.button.button] = true;
                MOUSE_DOWN[EVENT_QUEUE.button.button] = true;
                break;
                // Cas du relâchement d'un bouton de la souris
            case SDL_MOUSEBUTTONUP:
                if (MOUSE_DOWN[EVENT_QUEUE.button.button])
                    MOUSE_RELEASE[EVENT_QUEUE.button.button] = true;
                MOUSE_DOWN[EVENT_QUEUE.button.button] = false;
                break;
                // Cas d'un mouvement de souris
            case SDL_MOUSEMOTION:
                MOUSE_POSITION_X = EVENT_QUEUE.motion.x;
                MOUSE_POSITION_Y = 600-EVENT_QUEUE.motion.y;

                MOUSE_POSITION_DELTA_X = EVENT_QUEUE.motion.xrel;
                MOUSE_POSITION_DELTA_Y = EVENT_QUEUE.motion.yrel;
                break;
                // Cas de la fermeture de la fenêtre
            case SDL_WINDOWEVENT:
                if (EVENT_QUEUE.window.event == SDL_WINDOWEVENT_CLOSE);
                //terminer = true;
                break;
            default:
                break;
        }
    }
}

void InputEngine::setCursorVisible(bool value) {
    if (value)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void InputEngine::setCursorLock(bool value) {
    if (value)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
// Getters

bool InputEngine::getKeyboardDown(const SDL_Scancode key) {
    return KEYBOARD_DOWN[key];
}

bool InputEngine::getKeyboardPushed(const SDL_Scancode key) {
    return KEYBOARD_PUSH[key];
}

bool InputEngine::getKeyboardReleased(const SDL_Scancode key) {
    return KEYBOARD_RELEASE[key];
}

bool InputEngine::getMouseDown(const Uint8 button) {
    return MOUSE_DOWN[button];
}

bool InputEngine::getMousePushed(const Uint8 button) {
    return MOUSE_PUCH[button];
}

bool InputEngine::getMouseReleased(const Uint8 button) {
    return MOUSE_RELEASE[button];
}

bool InputEngine::getMouseMoved() {
    if (MOUSE_POSITION_DELTA_X == 0 && MOUSE_POSITION_DELTA_Y == 0)
        return false;
    else
        return true;
}
// Getters concernant la position du curseur

int InputEngine::getMousePositionX() {
    return MOUSE_POSITION_X;
}

int InputEngine::getMousePositionY() {
    return MOUSE_POSITION_Y;
}

int InputEngine::getMousePositionDeltaX() {
    return MOUSE_POSITION_DELTA_X;
}

int InputEngine::getMousePositionDeltaY() {
    return MOUSE_POSITION_DELTA_Y;
}
