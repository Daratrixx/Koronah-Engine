/* 
 * File:   Missile.h
 * Author: ANTOINE
 *
 * Created on 6 octobre 2016, 17:07
 */

#ifndef MISSILE_H
#define MISSILE_H

#include "Types.h"
#include "Entity.h"
#include "Unit.h"

class Missile : public Entity {
public:
    Missile();
    Missile(Missile* m);
    virtual ~Missile();
    virtual bool writeInFile(std::ofstream & fout);
    virtual bool readFromFile(std::ifstream & fin);

    virtual bool isMissile() const;
    float getDamage();
    
    float m_damage;
    Unit* m_missileOwner;
};

#endif /* MISSILE_H */

