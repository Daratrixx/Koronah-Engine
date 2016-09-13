#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

class Entity : public GameObject {
public:
    Entity();
    ~Entity();
    
    void addSpeed(float x, float y, float z);
    void addSpeed(glm::vec3 speed);
    void setSpeed(float x, float y, float z);
    void setSpeed(glm::vec3 speed);
    void setSpeedX(float x);
    void setSpeedY(float y);
    void setSpeedZ(float z);
    glm::vec3 getSpeed();
    void scaleSpeed(float factor);
    void slowMovement(float factor);
    void slowFall(float factor);
    void move();
    void moveToward(glm::vec3 target);
    void moveAway(glm::vec3 target);
    
    bool collision(Entity* e);
    int getCollision(Entity* e);
    bool adjust(Entity* e);
protected:
    glm::vec3 m_speed; // mouvement dans chaque direction
};

#endif
