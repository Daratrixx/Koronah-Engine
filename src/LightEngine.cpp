
#include "LightEngine.h"

LightEngine::LightEngine() {
    m_lightData = new float[LIGHT_COUNT * 6];
    for (unsigned int i = 0; i < LIGHT_COUNT * 6; i++) {
        *(m_lightData + i) = 0;
    }
    m_lightArray = new Light*[LIGHT_COUNT];
    for (unsigned int i = 0; i < LIGHT_COUNT; i++) {
        Light* temp = new Light();
        temp->setData(m_lightData + i * 6);
        temp->setColor(1, 1, 1);
        temp->setEnergy(0);
        m_lightArray[i] = temp;
    }
    Light* temp;
    temp = m_lightArray[0];
    temp->setPosition(0, 100, 0);
    temp->setColor(0.25f, 0.5f, 1);
    temp->setEnergy(-.1f);

    temp = m_lightArray[1];
    temp->setPosition(0, 3, 0);
    temp->setColor(1, 0.5f, 0.25f);
    temp->setEnergy(25);
}

LightEngine::~LightEngine() {
    if (m_lightData != null)
        delete m_lightData;
    for (unsigned int i = 0; i < LIGHT_COUNT; i++) {
        delete m_lightArray[i];
    }
    delete[] m_lightArray;
}

Light* LightEngine::getLight(unsigned int index) {
    if (index < LIGHT_COUNT)
        return m_lightArray[LIGHT_COUNT];
    return null;
}

float* LightEngine::getLightData() const {
    return m_lightData;
}
