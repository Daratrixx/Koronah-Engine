
#include "Settings.h"

// Setting

Setting::Setting() {
    if (!load())
        reset();
}

Setting::~Setting() {
    save();
}

bool Setting::load() {
    return false;
};

void Setting::reset() {
};

bool Setting::save() {
    return false;
};

// GraphicSetting

GraphicSetting::GraphicSetting() : Setting() {
}

GraphicSetting::~GraphicSetting() {
}

bool GraphicSetting::load() {
    std::ifstream file("graphic.set");
    if (file.bad()) // error, probably file not found
        return false;
    std::string valueIdentifier;
    while (!file.eof()) {
        file >> valueIdentifier;
        if (!file.bad()) {
            if (valueIdentifier == "screenWidth")
                file >> screenWidth;
            if (valueIdentifier == "screenHeight")
                file >> screenHeight;
            if (valueIdentifier == "scanDivisor")
                file >> scanDivisor;
            if (valueIdentifier == "fullScreen")
                file >> fullScreen;
        }
    }
    file.close();
    return true;
}

void GraphicSetting::reset() {
    screenWidth = 800;
    screenHeight = 600;
    scanDivisor = 2;
    fullScreen = false;
}

bool GraphicSetting::save() {
    std::ofstream file("graphic.set", std::ofstream::out | std::ofstream::trunc);
    if (file.bad()) {
        std::cout << "error saving graphic.set" << std::endl;
        return false;
    }
    file << "screenWidth" << " " << screenWidth << std::endl;
    file << "screenHeight" << " " << screenHeight << std::endl;
    file << "scanDivisor" << " " << scanDivisor << std::endl;
    file << "fullScreen" << " " << fullScreen << std::endl;
    file.close();
    std::cout << "saving graphic.set successful" << std::endl;
    return true;
}

// InputSetting

//InputSetting::InputSetting() : Setting() {
//}
//
//InputSetting::~InputSetting() {
//}
//
//bool InputSetting::load() {
//    std::ifstream file("input.set", std::ofstream::in);
//    if (file.bad()) // error, probably file not found
//        return false;
//    std::string valueIdentifier;
//    while (!file.eof()) {
//        file >> valueIdentifier;
//        if (!file.bad()) {
//            if (valueIdentifier == "mouseSensibility")
//                file >> mouseSensibility;
//            if (valueIdentifier == "keyboardSensibility")
//                file >> keyboardSensibility;
//        }
//    }
//    file.close();
//    return true;
//}
//
//void InputSetting::reset() {
//    mouseSensibility = 1;
//    keyboardSensibility = 1;
//}
//
//bool InputSetting::save() {
//    std::ofstream file("input.set", std::ofstream::out | std::ofstream::trunc);
//    if (file.bad()) {
//        std::cout << "error saving input.set" << std::endl;
//        return false;
//    }
//    file << "mouseSensibility" << " " << mouseSensibility << std::endl;
//    file << "keyboardSensibility" << " " << keyboardSensibility << std::endl;
//    file.close();
//    std::cout << "saving input.set successful" << std::endl;
//    return true;
//}
//
// other

GraphicSetting* getGraphicSetting() {
    static GraphicSetting setting;
    return &setting;
}

//InputSetting* getInputSetting() {
//    static InputSetting setting;
//    return &setting;
//}

void loadSettings() {
    if (!getGraphicSetting()->load())
        getGraphicSetting()->reset();
//    if (!getInputSetting()->load())
//        getInputSetting()->reset();
}

void saveSettings() {
    getGraphicSetting()->save();
//    getInputSetting()->save();
}
