/* 
 * File:   Unit.h
 * Author: ANTOINE
 *
 * Created on 27 juin 2016, 19:58
 */
#pragma once

#ifndef UNIT_H
#define	UNIT_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef ENTITY_H
#include "Entity.h"
#endif

#ifndef GEOMETRY_H
#include "Geometry.h"
#endif

class Unit : public Entity {
public:
    Unit();
    ~Unit();

    void moveForward(float speed);
    void moveBack(float speed);
    void moveRight(float speed);
    void moveLeft(float speed);
    void moveUp(float speed);
    void moveDown(float speed);

    float getHPCurrent() const;
    float getHPMax() const;
    float getHPPercent() const;
    
    void damage(float damage);
    void heal(float heal);

    float getENCurrent() const;
    float getENMax() const;
    float getENPercent() const;
    
    void consume(float consume);
    void recover(float recover);
    
private:
    float m_hpPercent;
    float m_hpMax;
    float m_enPercent;
    float m_enMax;
};

#endif	/* UNIT_H */

