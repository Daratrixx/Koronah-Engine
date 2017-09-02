
#include "Game.h"

Game::Game() {
    m_currentState = null;
    std::cout << "game created." << std::endl;
}

Short Game::init() {
    std::ofstream LOG_FILE;
    LOG_FILE.open("log.txt");
    LOG_FILE.close();
    std::cout << "log file cleaned." << std::endl;

    loadSettings();
    std::cout << "settings loaded" << std::endl;

    std::string title = "Koronah Engine";
    //Graphic.init(title);
    getGraphicEngine()->init(title);
    std::cout << "GraphicEngine creation successful." << std::endl;

    //if (!Graphic.initWindow(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    //    return -1;
    if (!getGraphicEngine()->initWindow(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        return -1;
    std::cout << "SDL initialisation successful." << std::endl;

    //if (!Graphic.initGL())
    //    return -1;
    if (!getGraphicEngine()->initGL())
        return -1;
    std::cout << "GL initialisation successful." << std::endl;

    //Particle = new ParticleEngine();
    //if (Particle == 0)
    //    return -1;
    //std::cout << "ParticleEngine creation successful." << std::endl;
    //Particle->m_graphicEngine = Graphic;

    //Light = new LightEngine();
    //if (Light == 0)
    //    return -1;
    //std::cout << "LightEngine creation successful." << std::endl;

    //Graphic->setLightData(Light->getLightData());
    //Graphic->setResolution(1280,720);
    //Graphic.loadGraphicDatas();
    getGraphicEngine()->loadGraphicDatas();
    std::cout << "loadGraphicDatas successful." << std::endl;
    Mapping.reset();
    Mapping.load();
    std::cout << "mapping loaded successful." << std::endl;
    return 0; // no problem
}

void Game::loop() {
    GameStateSTR playground;
    GameStateMenu menu;
    GameStateSettings settings;
    std::cout << "GameStateSTR creation successful." << std::endl;
    playground.Graphic = getGraphicEngine();
    playground.Input = &Input;
    playground.InputSetting = &Mapping;
    playground.Time = &Time;
    playground.load();
    menu.Graphic = getGraphicEngine();
    menu.Input = &Input;
    menu.InputSetting = &Mapping;
    menu.Time = &Time;
    menu.load();
    settings.Graphic = getGraphicEngine();
    settings.Input = &Input;
    settings.InputSetting = &Mapping;
    settings.Time = &Time;
    settings.load();
    std::cout << "start of loop." << std::endl;
    m_currentState = &menu;
    bool close = false;
    while (!close) {
        Time.updateTime();
        float time = Time.getDeltaTime();
        Input.resetEvents();
        switch (m_currentState->mainFunction(time)) {
            case ORDER_EXIT:
                close = true;
                break;
            case ORDER_CONTINUE:
                break;
            case ORDER_TO_PLAYGROUND:
                switchTo(&playground);
                break;
            case ORDER_TO_SETTINGS:
                switchTo(&settings);
                break;
            case ORDER_TO_MENU:
                switchTo(&menu);
                break;
            default:break;
        }
        if (Input.getKeyboardPushed(SDL_SCANCODE_ESCAPE))
            close = true;
        Time.waitSeconds(0.010f);
    }
}

void Game::switchTo(GameState* state) {
    if (m_currentState != null)
        m_currentState->onLeave();
    m_currentState = state;
    m_currentState->onEnter();
}

void Game::close() {
    saveSettings();
    std::cout << "settings saved" << std::endl;

    std::cout << "Leaving program without error." << std::endl;
}