
#include "Time.h"

TimeEngine::TimeEngine() {
    CURRENT_TIME = 0;
    DELTA_TIME = 0;
    UPDATE_CUMULATOR = 0;
    UPDATE_COUNT = 0;
    LAST_UPDATE_COUNT = 0;
}

float TimeEngine::getDeltaTime() const {
    return DELTA_TIME;
}

float TimeEngine::getCurrentTime() const {
    return CURRENT_TIME;
}

float TimeEngine::getCurrentTick() const {
    return (float) SDL_GetTicks() / 1000.f;
}

void TimeEngine::updateTime() { // only once par game tick!!!
    DELTA_TIME = getCurrentTick() - CURRENT_TIME; // new delta time
    CURRENT_TIME += DELTA_TIME; // new current time
    UPDATE_CUMULATOR += DELTA_TIME;
    UPDATE_COUNT++;
    if (UPDATE_CUMULATOR > 1) {
        UPDATE_CUMULATOR -= 1;
        LAST_UPDATE_COUNT = UPDATE_COUNT;
        UPDATE_COUNT = 0;
        //std::cout << "FPS : " << LAST_UPDATE_COUNT << std::endl;
    }
    FPS_APPROX = (UShort) (1.f / DELTA_TIME);
}

void TimeEngine::waitSeconds(float seconds) const {
    if (seconds > 0)
        SDL_Delay((UInt) (seconds * 1000));
}

UShort TimeEngine::getFPS() const {
    return FPS_APPROX;
}