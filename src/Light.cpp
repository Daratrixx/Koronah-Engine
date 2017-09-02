
#include "Light.h"

Light::Light() {
    m_data = null;
    m_energy = 1;
}

Light::~Light() {
    m_data = null;
}

void Light::setData(float* dataOrigin) {
    m_data = dataOrigin;
}

glm::vec3 Light::getPosition() const {
    return glm::vec3(*(m_data), *(m_data + 1), *(m_data + 2));
}

void Light::setPosition(const float & x, const float & y, const float & z) {
    *(m_data) = x;
    *(m_data + 1) = y;
    *(m_data + 2) = z;
}

void Light::setPosition(const glm::vec3 & position) {
    *(m_data) = position.x;
    *(m_data + 1) = position.y;
    *(m_data + 2) = position.z;
}

glm::vec3 Light::getColor() const {
    return m_color;
}

void Light::setColor(const float & r, const float & g, const float & b) {
    m_color.x = r;
    m_color.y = g;
    m_color.z = b;
    UpdateColor();
}

void Light::setColor(const glm::vec3 & color) {
    m_color = color;
    UpdateColor();
}

float Light::getEnergy() const {
    return m_energy;
}

void Light::setEnergy(const float & energy) {
    m_energy = energy;
    UpdateColor();
}

void Light::UpdateColor() {
    *(m_data + 3) = m_color.x * m_energy;
    *(m_data + 4) = m_color.y * m_energy;
    *(m_data + 5) = m_color.z * m_energy;
}
