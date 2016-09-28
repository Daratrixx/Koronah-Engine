#include "Entity.h"

Entity::Entity() : GameObject() {
    setSpeed(0, 0, 0);
    m_radius = 2;
    m_lastCollisionHit = 0;
    m_behavior = UNIT_BEHAVIOR_IDLE;
}

Entity::~Entity() {
    std::cout << "Deleted Entity with ID " << m_objectId << std::endl;
}

void Entity::addSpeed(float x, float y, float z) {
    m_speed.x += x;
    m_speed.y += y;
    m_speed.z += z;
}

void Entity::addSpeed(glm::vec3 speed) {
    m_speed += speed;
}

void Entity::setSpeed(glm::vec3 speed) {
    m_speed = speed;
}

void Entity::setSpeed(float x, float y, float z) {
    m_speed.x = x;
    m_speed.y = y;
    m_speed.z = z;
}

void Entity::setSpeedX(float x) {
    m_speed.x = x;
}

void Entity::setSpeedY(float y) {
    m_speed.y = y;
}

void Entity::setSpeedZ(float z) {
    m_speed.z = z;
}

void Entity::setRadius(float radius) {
    m_radius = radius;
}

float Entity::getRadius() const {
    return m_radius;
}

glm::vec3 Entity::getSpeed() {
    return m_speed;
}

void Entity::scaleSpeed(float factor) {
    m_speed.x = factor * m_speed.x;
    m_speed.y = factor * m_speed.y;
    m_speed.z = factor * m_speed.z;
}

void Entity::slowMovement(float factor) {
    m_speed.x = factor * m_speed.x;
    m_speed.z = factor * m_speed.z;
}

void Entity::slowFall(float factor) {
    m_speed.y = factor * m_speed.y;
}

void Entity::move() {
}

void Entity::moveToward(glm::vec3 target) {
    float distX = m_position.x - target.x;
    float distY = m_position.y - target.y;
    float product = abs(distX) / (abs(distX) + abs(distY));

    float speedX = product * 0.1f;
    float speedY = (1 - product)*0.1f;
    if (abs(distX) > 0.05f) {
        if (speedX > m_speed.x && distX > 0)
            m_speed.x -= speedX * 0.2f;
        if (-speedX < m_speed.x && distX < 0)
            m_speed.x += speedX * 0.2f;
    }
    if (abs(distY) > 0.05f) {
        if (speedY > m_speed.y && distY > 0)
            m_speed.y -= speedY * 0.2f;
        if (-speedY < m_speed.y && distY < 0)
            m_speed.y += speedY * 0.2f;
    }
}

void Entity::moveAway(glm::vec3 target) {
    float distX = m_position.x - target.x;
    float distY = m_position.y - target.y;
    float product = abs(distX) / (abs(distX) + abs(distY));

    float speedX = product * 0.1f;
    float speedY = (1 - product)*0.1f;
    if (abs(distX) > 0.05f) {
        if (speedX > m_speed.x && distX > 0)
            m_speed.x += speedX * 0.2f;
        if (-speedX < m_speed.x && distX < 0)
            m_speed.x -= speedX * 0.2f;
    }
    if (abs(distY) > 0.05f) {
        if (speedY > m_speed.y && distY > 0)
            m_speed.y += speedY * 0.2f;
        if (-speedY < m_speed.y && distY < 0)
            m_speed.y -= speedY * 0.2f;
    }
}

void Entity::push(float x, float z) {
    m_position.x += x;
    m_position.z += z;
    if (m_behavior == UNIT_BEHAVIOR_IDLE) {
        m_lastCollisionHit = 0;
        m_behavior = UNIT_BEHAVIOR_PUSHED;
    }
}

void Entity::update(float time, std::vector<GameObject*> objects) {
    m_lastCollisionHit += time;
    if (m_lastCollisionHit > 1.5f && m_behavior == UNIT_BEHAVIOR_PUSHED)
        m_behavior = UNIT_BEHAVIOR_MOVING;
}

bool Entity::collision(Entity* e) {
    glm::vec3 size = e->getScale();
    glm::vec3 pos = e->getPosition();
    if ((pos.x - (size.x + 0.2f) / 2 >= m_position.x + (m_scale.x + 0.2f) / 2) // trop à droite
            || (pos.x + (size.x + 0.2f) / 2 <= m_position.x - (m_scale.z + 0.2f) / 2) // trop à gauche
            || (pos.y - (size.y + 0.2f) / 2 >= m_position.y + (m_scale.y + 0.2f) / 2) // trop en bas
            || (pos.y + (size.y + 0.2f) / 2 <= m_position.y - (m_scale.z + 0.2f) / 2) // trop en haut	
            || (pos.z - (size.z + 0.2f) / 2 >= m_position.z + (m_scale.z + 0.2f) / 2) // trop derrière
            || (pos.z + (size.z + 0.2f) / 2 <= m_position.z - (m_scale.z + 0.2f) / 2))// trop devant
        return false;
    else
        return true;
}

bool Entity::adjust(Entity* e) {
    glm::vec3 size = e->getScale();
    glm::vec3 pos = e->getPosition();

    glm::vec3 inter = (m_position - pos);
    inter.x = inter.x / ((m_scale.x + size.x) / 2);
    inter.y = inter.y / ((m_scale.y + size.y) / 2);
    inter.z = inter.z / ((m_scale.z + size.z) / 2);
    if (abs(inter.x) < 1 && abs(inter.x) > abs(inter.y) && abs(inter.x) > abs(inter.z)) {
        if (inter.x > 0)
            m_position.x = pos.x + (m_scale.x + size.x + 0.1f) / 2.;
        else
            m_position.x = pos.x - (m_scale.x + size.x + 0.1f) / 2;
        m_speed.x = 0;
    }
    if (!collision(e))
        return false;

    pos = e->getPosition();
    inter = (m_position - pos);
    inter.x = inter.x / ((m_scale.x + size.x) / 2);
    inter.y = inter.y / ((m_scale.y + size.y) / 2);
    inter.z = inter.z / ((m_scale.z + size.z) / 2);
    if (abs(inter.y) < 1 && abs(inter.y) > abs(inter.x) && abs(inter.y) > abs(inter.z)) {
        if (inter.y > 0)
            m_position.y = pos.y + (m_scale.y + size.y + 0.1f) / 2;
        else
            m_position.y = pos.y - (m_scale.y + size.y + 0.1f) / 2;
        m_speed.y = 0;
    }
    if (!collision(e))
        return false;

    pos = e->getPosition();
    inter = (m_position - pos);
    inter.x = inter.x / ((m_scale.x + size.x) / 2);
    inter.y = inter.y / ((m_scale.y + size.y) / 2);
    inter.z = inter.z / ((m_scale.z + size.z) / 2);
    if (abs(inter.z) < 1 && abs(inter.z) > abs(inter.x) && abs(inter.z) > abs(inter.y)) {
        if (inter.z > 0)
            m_position.z = pos.z + (m_scale.z + size.z + 0.1f) / 2;
        else
            m_position.z = pos.z - (m_scale.z + size.z + 0.1f) / 2;
        m_speed.z = 0;
        if (inter.z > 0)
            return true;
    }

    return false;
}

void Entity::setBehavior(unsigned int behavior) {
    m_behavior = behavior;
}

unsigned int Entity::getBehavior() const {
    return m_behavior;
}

