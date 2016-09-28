
#include "Settings.h"

glm::vec3* Settings_RESOLUTION() {
    static glm::vec3 resolution = glm::vec3(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 16 / 9);
    return &resolution;
}

glm::vec2 Settings_getResolution() {
    return glm::vec2(Settings_RESOLUTION()->x, Settings_RESOLUTION()->y);
}

int Settings_getScreenWidth() {
    return Settings_RESOLUTION()->x;
}

int Settings_getScreenHeight() {
    return Settings_RESOLUTION()->y;
}

float Settings_getScreenRatio() {
    return Settings_RESOLUTION()->z;
}

void Settings_setResolution(glm::vec2 resolution) {
    Settings_setResolution(resolution.x, resolution.y);
}

void Settings_setResolution(float w, float h) {
    Settings_RESOLUTION()->x = w;
    Settings_RESOLUTION()->y = h;
    Settings_RESOLUTION()->z = w / h;
}
