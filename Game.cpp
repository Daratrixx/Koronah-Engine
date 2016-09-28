
#include "Game.h"

Game::Game() {
    Graphic = null;
    Input = null;
    Time = null;
    Particle = null;
    Light = null;
    m_currentState = null;
}

int Game::init() {
    std::ofstream LOG_FILE;
    LOG_FILE.open("log.txt");
    LOG_FILE.close();
    std::cout << "log file cleaned." << std::endl;

    std::string title = "Koronah Engine";
    Graphic = new GraphicEngine(title, 800, 600);
    if (Graphic == 0)
        return -1;
    std::cout << "GraphicEngine creation successful." << std::endl;
    
    if (!Graphic->initWindow(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        return -1;
    std::cout << "SDL initialisation successful." << std::endl;
    
    if (!Graphic->initGL())
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

    Time = new TimeEngine();
    if (Time == 0)
        return -1;

    Input = new InputEngine();
    if (Input == 0)
        return -1;

    //Graphic->setLightData(Light->getLightData());
    //Graphic->setResolution(1280,720);
    Graphic->loadGraphicDatas();

    return 0; // no problem
}

void Game::loop() {
    GameStateSTR* playground = new GameStateSTR();
    std::cout << "GameStateSTR creation successful." << std::endl;
    playground->Graphic = Graphic;
    playground->Input = Input;
    //playground->Light = Light;
    //playground->Particle = Particle;
    playground->Time = Time;
    playground->load();
    GameStateMenu* menu = new GameStateMenu();
    menu->Graphic = Graphic;
    menu->Input = Input;
    menu->Time = Time;
    menu->load();
    std::cout << "start of loop." << std::endl;
    m_currentState = menu;
    bool close = false;
    while (!close) {
        Time->updateTime();
        float time = Time->getDeltaTime();
        Input->updateEvents();
        if (Input->getKeyboardPushed(SDL_SCANCODE_ESCAPE))
            close = true;
        switch (m_currentState->mainFunction(time)) {
            case ORDER_EXIT:
                close = true;
                break;
            case ORDER_CONTINUE:
                break;
            case ORDER_TO_PLAYGROUND:
                switchTo(playground);
                break;
            case ORDER_TO_MENU:
                switchTo(menu);
                break;
            default:break;
        }
        Time->waitSeconds(0.010f);
    }
    delete playground;
    std::cout << "GameStateSTR deleted." << std::endl;
    delete menu;
    std::cout << "GameStateMenu deleted." << std::endl;
}

void Game::switchTo(GameState* state) {
    if(m_currentState != null)
        m_currentState->onLeave();
    m_currentState = state;
    m_currentState->onEnter();
}

void Game::close() {
    delete Input;
    std::cout << "InputEngine deleted." << std::endl;
    delete Time;
    std::cout << "TimeEngine deleted." << std::endl;
    //delete Light;
    //std::cout << "LightEngine deleted." << std::endl;
    //delete Particle;
    //std::cout << "ParticleEngine deleted." << std::endl;
    delete Graphic;
    std::cout << "GraphicEngine deleted." << std::endl;
    std::cout << "Settings_RESOLUTION deleted." << std::endl;
    std::cout << "Leaving program without error." << std::endl;
    exit(0);
}