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
    Entity(Entity* e);
    virtual ~Entity();
    
    void setRadius(float radius);
    float getRadius() const;
    
    virtual void push(float x, float y);
    
    Entity* getTarget() const;
    bool isTarget(Entity* e) const;
    void setTarget(Entity* target);
    
    float getMovingSpeed();
    void setMovingSpeed(float movingSpeed);
    
    virtual bool isAlive() const;
    virtual bool isUnit() const;
    virtual bool isMissile() const;
    
    bool m_doCollision;
    float m_lastCollisionHit;
    float m_movingSpeed;
    float m_radius;
    Entity* m_target;
};

#endif
