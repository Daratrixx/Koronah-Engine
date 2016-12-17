#include "Entity.h"

Entity::Entity() : GameObject() {
    m_doCollision = true;
    m_lastCollisionHit = 0;
    m_movingSpeed = 25;
    m_radius = 1;
    m_target = null;
}

Entity::Entity(Entity* e) : GameObject(e) {
    m_doCollision = e->m_doCollision;
    m_lastCollisionHit = 0;
    m_movingSpeed = e->m_movingSpeed;
    m_radius = e->m_radius;
    m_target = null;
}

Entity::~Entity() {
    std::cout << "Deleted Entity with ID " << m_objectId << std::endl;
}

void Entity::setRadius(float radius) {
    m_radius = radius;
}

float Entity::getRadius() const {
    return m_radius;
}

void Entity::push(float x, float y) {
    m_position.x += x;
    m_position.y += y;
}

Entity* Entity::getTarget() const {
    return m_target;
}

bool Entity::isTarget(Entity* e) const {
    return m_target == e;
}

void Entity::setTarget(Entity* target) {
    m_target = target;
}

float Entity::getMovingSpeed() {
    return m_movingSpeed;
}

void Entity::setMovingSpeed(float movingSpeed) {
    m_movingSpeed = movingSpeed;
}

bool Entity::isAlive() const {
    return false;
}

bool Entity::isUnit() const {
    return false;
}

bool Entity::isMissile() const {
    return false;
}
