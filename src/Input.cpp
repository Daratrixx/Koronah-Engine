
#include "Input.h"

InputMapping::InputMapping() {
    key[COMMAND_NONE] = SDL_SCANCODE_UNKNOWN;
    mod[COMMAND_NONE] = KMOD_NONE;
    button[COMMAND_NONE] = 0;
    command[COMMAND_SELECT] = "Select";
    command[COMMAND_TARGET] = "Target";
    command[COMMAND_GENERIC_ORDER] = "Generic order";
    command[COMMAND_LEFT] = "Left";
    command[COMMAND_RIGHT] = "Right";
    command[COMMAND_UP] = "Up";
    command[COMMAND_DOWN] = "Down";
    command[COMMAND_CHAT] = "Open chat/send message";
    command[COMMAND_GRID_00] = "Grid button column 1, row 1";
    command[COMMAND_GRID_10] = "Grid button column 2, row 1";
    command[COMMAND_GRID_20] = "Grid button column 3, row 1";
    command[COMMAND_GRID_30] = "Grid button column 4, row 1";
    command[COMMAND_GRID_40] = "Grid button column 5, row 1";
    command[COMMAND_GRID_01] = "Grid button column 1, row 2";
    command[COMMAND_GRID_11] = "Grid button column 2, row 2";
    command[COMMAND_GRID_21] = "Grid button column 3, row 2";
    command[COMMAND_GRID_31] = "Grid button column 4, row 2";
    command[COMMAND_GRID_41] = "Grid button column 5, row 2";
    command[COMMAND_GRID_02] = "Grid button column 1, row 3";
    command[COMMAND_GRID_12] = "Grid button column 2, row 3";
    command[COMMAND_GRID_22] = "Grid button column 3, row 3";
    command[COMMAND_GRID_32] = "Grid button column 4, row 3";
    command[COMMAND_GRID_42] = "Grid button column 5, row 3";
    command[COMMAND_CREATE_GROUP_0] = "Create control group #1";
    command[COMMAND_CREATE_GROUP_1] = "Create control group #2";
    command[COMMAND_CREATE_GROUP_2] = "Create control group #3";
    command[COMMAND_CREATE_GROUP_3] = "Create control group #4";
    command[COMMAND_CREATE_GROUP_4] = "Create control group #5";
    command[COMMAND_CREATE_GROUP_5] = "Create control group #6";
    command[COMMAND_CREATE_GROUP_6] = "Create control group #7";
    command[COMMAND_CREATE_GROUP_7] = "Create control group #8";
    command[COMMAND_CREATE_GROUP_8] = "Create control group #9";
    command[COMMAND_CREATE_GROUP_9] = "Create control group #10";
    command[COMMAND_SELECT_GROUP_0] = "Select control group #1";
    command[COMMAND_SELECT_GROUP_1] = "Select control group #2";
    command[COMMAND_SELECT_GROUP_2] = "Select control group #3";
    command[COMMAND_SELECT_GROUP_3] = "Select control group #4";
    command[COMMAND_SELECT_GROUP_4] = "Select control group #5";
    command[COMMAND_SELECT_GROUP_5] = "Select control group #6";
    command[COMMAND_SELECT_GROUP_6] = "Select control group #7";
    command[COMMAND_SELECT_GROUP_7] = "Select control group #8";
    command[COMMAND_SELECT_GROUP_8] = "Select control group #9";
    command[COMMAND_SELECT_GROUP_9] = "Select control group #10";
}

bool InputMapping::load() { // "input.set"
    std::ifstream file("input.set");
    if (!file.is_open() || file.bad()) // error, probably file not found
        return false;
    int c;
    int button;
    int key;
    int mod;
    while (!file.eof()) {
        file >> c;
        file >> button;
        if ((Uint8) button != 0) {
            remap((Command) c, (Uint8) button);
        } else {
            file >> key;
            file >> mod;
            remap((Command) c, (SDL_Scancode) key, (SDL_Keymod) mod);
        }
    }
    return true;
}

bool InputMapping::save() {
    std::ofstream file("input.set", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open() || file.bad())
        return false;
    int button;
    int key;
    int mod;
    for (int c = 0; c < COMMAND_KEY_COUNT; c++) {
        button = (int) this->button[c];
        key = (int) this->key[c];
        mod = (int) this->mod[c];
        file << c << " ";
        file << button << " ";
        if (button == 0) {
            file << key << " ";
            file << mod << " ";
        }
    }
    file.close();
    return true;
}

void InputMapping::reset() {
    // essential commands
    remap(COMMAND_SELECT, SDL_BUTTON_LEFT);
    remap(COMMAND_TARGET, SDL_BUTTON_LEFT);
    remap(COMMAND_GENERIC_ORDER, SDL_BUTTON_RIGHT);

    // direction commands
    remap(COMMAND_LEFT, SDL_SCANCODE_LEFT, KMOD_NONE);
    remap(COMMAND_RIGHT, SDL_SCANCODE_RIGHT, KMOD_NONE);
    remap(COMMAND_UP, SDL_SCANCODE_UP, KMOD_NONE);
    remap(COMMAND_DOWN, SDL_SCANCODE_DOWN, KMOD_NONE);

    // other commands
    remap(COMMAND_CHAT, SDL_SCANCODE_RETURN, KMOD_NONE);

    // grid commands
    remap(COMMAND_GRID_00, SDL_SCANCODE_Q, KMOD_NONE);
    remap(COMMAND_GRID_10, SDL_SCANCODE_W, KMOD_NONE);
    remap(COMMAND_GRID_20, SDL_SCANCODE_E, KMOD_NONE);
    remap(COMMAND_GRID_30, SDL_SCANCODE_R, KMOD_NONE);
    remap(COMMAND_GRID_40, SDL_SCANCODE_T, KMOD_NONE);
    remap(COMMAND_GRID_01, SDL_SCANCODE_A, KMOD_NONE);
    remap(COMMAND_GRID_11, SDL_SCANCODE_S, KMOD_NONE);
    remap(COMMAND_GRID_21, SDL_SCANCODE_D, KMOD_NONE);
    remap(COMMAND_GRID_31, SDL_SCANCODE_F, KMOD_NONE);
    remap(COMMAND_GRID_41, SDL_SCANCODE_G, KMOD_NONE);
    remap(COMMAND_GRID_02, SDL_SCANCODE_Z, KMOD_NONE);
    remap(COMMAND_GRID_12, SDL_SCANCODE_X, KMOD_NONE);
    remap(COMMAND_GRID_22, SDL_SCANCODE_C, KMOD_NONE);
    remap(COMMAND_GRID_32, SDL_SCANCODE_V, KMOD_NONE);
    remap(COMMAND_GRID_42, SDL_SCANCODE_B, KMOD_NONE);

    // control group commands
    remap(COMMAND_CREATE_GROUP_0, SDL_SCANCODE_1, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_1, SDL_SCANCODE_2, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_2, SDL_SCANCODE_3, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_3, SDL_SCANCODE_4, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_4, SDL_SCANCODE_5, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_5, SDL_SCANCODE_6, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_6, SDL_SCANCODE_7, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_7, SDL_SCANCODE_8, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_8, SDL_SCANCODE_9, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_CREATE_GROUP_9, SDL_SCANCODE_0, (SDL_Keymod) KMOD_CTRL);
    remap(COMMAND_SELECT_GROUP_0, SDL_SCANCODE_1, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_1, SDL_SCANCODE_2, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_2, SDL_SCANCODE_3, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_3, SDL_SCANCODE_4, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_4, SDL_SCANCODE_5, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_5, SDL_SCANCODE_6, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_6, SDL_SCANCODE_7, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_7, SDL_SCANCODE_8, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_8, SDL_SCANCODE_9, KMOD_NONE);
    remap(COMMAND_SELECT_GROUP_9, SDL_SCANCODE_0, KMOD_NONE);
}

bool InputMapping::remap(const Command & c, const SDL_Scancode & key, const SDL_Keymod & mod) { // remap with keyboard
    if (key == SDL_SCANCODE_ESCAPE) // can't map ESCAPE, used to cancel maping
        return true;
    this->key[c] = key;
    this->mod[c] = mod;
    this->button[c] = 0;
    name[c] = "";
    if (mod & KMOD_LCTRL || mod & KMOD_RCTRL)
        name[c] += "CTRL + ";
    if (mod & KMOD_LALT || mod & KMOD_RALT)
        name[c] += "ALT + ";
    if (mod & KMOD_LSHIFT || mod & KMOD_RSHIFT)
        name[c] += "SHIFT + ";
    name[c] += SDL_GetKeyName(SDL_GetKeyFromScancode(key));
    return true;
}

bool InputMapping::remap(const Command & c, const Uint8 & button) { // remap with mouse
    this->key[c] = SDL_SCANCODE_UNKNOWN;
    this->mod[c] = KMOD_NONE;
    this->button[c] = button;
    switch (button) {
        case SDL_BUTTON_LEFT:
            name[c] = "Left mouse button";
            break;
        case SDL_BUTTON_RIGHT:
            name[c] = "Right mouse button";
            break;
        case SDL_BUTTON_MIDDLE:
            name[c] = "Middle mouse button";
            break;
        case SDL_BUTTON_X1:
            name[c] = "X1 mouse button";
            break;
        case SDL_BUTTON_X2:
            name[c] = "X2 mouse button";
            break;
        default:
            name[c] = "/!\\ UNSUPPORTED MOUSE BUTTON";
            break;
    }
    return true;
}

bool InputMapping::remap(const Command & c, const SDL_Event & e) {
    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
        return remap(c, e.key.keysym.scancode, mod[c] = (SDL_Keymod) e.key.keysym.mod);
    } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        return remap(c, e.button.button);
    }
    return false;
}

bool InputMapping::commandTriggered(const Command & c, const SDL_Event & e) const {
    if (key[c] != SDL_SCANCODE_UNKNOWN) {
        if (e.type != SDL_KEYDOWN && e.type != SDL_KEYUP)
            return false; // not the good event type for this command
        if (key[c] == e.key.keysym.scancode && mod[c] == e.key.keysym.mod)
            return true; // key matching
        return false; // not the good key
    } else if (button[c] != 0) {
        if (e.type != SDL_MOUSEBUTTONDOWN && e.type != SDL_MOUSEBUTTONUP)
            return false; // not the good event type for this command
        if (button[c] == e.button.button)
            return true; // button matching
        return false; // not the good button
    }
    return false;
}

InputEngine::InputEngine() {
    MOUSE_POSITION_X = 0;
    MOUSE_POSITION_Y = 0;
    MOUSE_POSITION_DELTA_X = 0;
    MOUSE_POSITION_DELTA_Y = 0;
    // Initialisation du tableau touches[]
    for (UInt i = 0; i < SDL_NUM_SCANCODES; i++) {
        KEYBOARD_DOWN[i] = false;
        KEYBOARD_PUSH[i] = false;
        KEYBOARD_RELEASE[i] = false;
    }
    // Initialisation du tableau boutonsSouris[]
    for (UShort i = 0; i < 8; i++) {
        MOUSE_DOWN[i] = false;
        MOUSE_PUCH[i] = false;
        MOUSE_RELEASE[i] = false;
    }
}

void InputEngine::resetEvents() {
    // Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives
    MOUSE_POSITION_DELTA_X = 0;
    MOUSE_POSITION_DELTA_Y = 0;
    // Correction touches clavier
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        KEYBOARD_PUSH[i] = false;
        KEYBOARD_RELEASE[i] = false;
    }
    // Correction boutons souris
    for (int i = 0; i < 8; i++) {
        MOUSE_PUCH[i] = false;
        MOUSE_RELEASE[i] = false;
    }
}

void InputEngine::updateEvents(SDL_Event & EVENT_QUEUE) {
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
            MOUSE_POSITION_Y = 600 - EVENT_QUEUE.motion.y;

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

void InputEngine::setCursorVisible(const bool & value) {
    if (value)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void InputEngine::setCursorLock(const bool & value) {
    if (value)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
// Getters

bool InputEngine::getKeyboardDown(const SDL_Scancode & key) const {
    return KEYBOARD_DOWN[key];
}

bool InputEngine::getKeyboardPushed(const SDL_Scancode & key) const {
    return KEYBOARD_PUSH[key];
}

bool InputEngine::getKeyboardReleased(const SDL_Scancode & key) const {
    return KEYBOARD_RELEASE[key];
}

bool InputEngine::getMouseDown(const Uint8 & button) const {
    return MOUSE_DOWN[button];
}

bool InputEngine::getMousePushed(const Uint8 & button) const {
    return MOUSE_PUCH[button];
}

bool InputEngine::getMouseReleased(const Uint8 & button) const {
    return MOUSE_RELEASE[button];
}

bool InputEngine::getMouseMoved() const {
    if (MOUSE_POSITION_DELTA_X == 0 && MOUSE_POSITION_DELTA_Y == 0)
        return false;
    else
        return true;
}
// Getters concernant la position du curseur

Int InputEngine::getMousePositionX() const {
    return MOUSE_POSITION_X;
}

Int InputEngine::getMousePositionY() const {
    return MOUSE_POSITION_Y;
}

Int InputEngine::getMousePositionDeltaX() const {
    return MOUSE_POSITION_DELTA_X;
}

Int InputEngine::getMousePositionDeltaY() const {
    return MOUSE_POSITION_DELTA_Y;
}
