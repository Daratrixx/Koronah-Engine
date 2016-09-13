
#include "Unit.h"

Unit::Unit() : Entity() {
    m_hpPercent = 1;
    m_hpMax = 150;
    m_enPercent = 1;
    m_enMax = 50;
}

Unit::~Unit() {
    std::cout << "Deleted Unit with ID " << m_objectId << std::endl;
}

void Unit::moveForward(float speed) {
    glm::vec3 direction = getForwardVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveBack(float speed) {
    glm::vec3 direction = getBackVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveRight(float speed) {
    glm::vec3 direction = getRightVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveLeft(float speed) {
    glm::vec3 direction = getLeftVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveUp(float speed) {
    glm::vec3 direction = getUpVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveDown(float speed) {
    glm::vec3 direction = getDownVector(m_angle);
    addPosition(direction * speed);
}

float Unit::getHPCurrent() const {
    return m_hpPercent * m_hpMax;
}
float Unit::getHPMax() const {
    return m_hpMax;
}
float Unit::getHPPercent() const {
    return m_hpPercent;
}
void Unit::damage(float damage) {
    float percent = damage/m_hpMax;
    m_hpPercent -= percent;
    if(m_hpPercent<0)
        m_hpPercent = 0;
}
void Unit::heal(float heal) {
    float percent = heal/m_hpMax;
    m_hpPercent += percent;
    if(m_hpPercent>1)
        m_hpPercent = 1;
}

float Unit::getENCurrent() const {
    return m_enPercent * m_enMax;
}
float Unit::getENMax() const {
    return m_enMax;
}
float Unit::getENPercent() const {
    return m_enPercent;
}
void Unit::consume(float consume) {
    float percent = consume/m_enMax;
    m_enPercent -= percent;
    if(m_enPercent<0)
        m_enPercent = 0;
}
void Unit::recover(float recover) {
    float percent = recover/m_enMax;
    m_enPercent += percent;
    if(m_enPercent>1)
        m_enPercent = 1;
}