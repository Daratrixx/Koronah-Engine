#include "Entity.h"

Entity::Entity() : GameObject() {
    m_doCollision = true;
    m_lastCollisionHit = 0;
    m_movingSpeed = 25;
    m_collisionRadius = 1;
    m_target = null;
}

Entity::Entity(Entity* e) : GameObject(e) {
    m_doCollision = e->m_doCollision;
    m_lastCollisionHit = 0;
    m_movingSpeed = e->m_movingSpeed;
    m_collisionRadius = e->m_collisionRadius;
    m_target = null;
}

Entity::~Entity() {
}

bool Entity::writeInFile(std::ofstream & fout) {
    /*unsigned addr = (unsigned)this;
    unsigned size = sizeof(this);
    fout.write((char*) &addr, sizeof(unsigned));
    fout.write((char*) &size, sizeof(unsigned));
    fout.write((char*) this, size);*/
    return true;
}

bool Entity::readFromFile(std::ifstream & fin) {
    fin.read((char*) this, sizeof(this));
    return true;
}

void Entity::setRadius(const float & radius) {
    m_collisionRadius = radius;
}

float Entity::getRadius() const {
    return m_collisionRadius;
}

void Entity::push(const float & x, const float & y) {
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

void Entity::setMovingSpeed(const float & movingSpeed) {
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
