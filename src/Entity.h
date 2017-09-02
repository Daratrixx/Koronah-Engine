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
    virtual bool writeInFile(std::ofstream & fout);
    virtual bool readFromFile(std::ifstream & fin);
    
    void setRadius(const float & radius);
    float getRadius() const;
    
    virtual void push(const float & x, const float & y);
    
    Entity* getTarget() const;
    bool isTarget(Entity* e) const;
    void setTarget(Entity* target);
    
    float getMovingSpeed();
    void setMovingSpeed(const float & movingSpeed);
    
    virtual bool isAlive() const;
    virtual bool isUnit() const;
    virtual bool isMissile() const;
    
    bool m_doCollision;
    float m_lastCollisionHit;
    float m_movingSpeed;
    float m_collisionRadius;
    Entity* m_target;
};

#endif
