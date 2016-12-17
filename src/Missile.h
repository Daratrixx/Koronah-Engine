/* 
 * File:   Missile.h
 * Author: ANTOINE
 *
 * Created on 6 octobre 2016, 17:07
 */

#ifndef MISSILE_H
#define	MISSILE_H

#include "Types.h"
#include "Entity.h"

class Missile : public Entity {
public:
    Missile();
    Missile(Missile* m);
    virtual ~Missile();

    virtual bool isMissile() const;

    float m_damage;
    Entity* m_missileOwner;

};

#endif	/* MISSILE_H */

