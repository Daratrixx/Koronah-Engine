
#include "GameState.h"

GameState::GameState() {
    Graphic = null;
    Input = null;
    Time = null;
    m_elapsedTime=0;
    m_totalElapsedTime=0;
    m_gravityTime=0;
    m_guiRoot = null;
}

GameState::~GameState() {
    delete m_guiRoot;
}
void GameState::load() {
    
}

void GameState::onEnter() {
}
void GameState::onLeave() {
}
int GameState::mainFunction(float time) {
    return inputManagement();
}
void GameState::update() {
}
int GameState::inputManagement() {
    return 0;
}
void GameState::render() {
}
void GameState::setLoopTime(float time) {
    m_elapsedTime=time;
    m_totalElapsedTime+=time;
    m_gravityTime=sqrt(time);
}