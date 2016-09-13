/* 
 * File:   Triggerable.hpp
 * Author: ANTOINE
 *
 * Created on 2 septembre 2016, 14:18
 */

#ifndef TRIGGERABLE_HPP
#define	TRIGGERABLE_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

class Triggerable {
public:
    Triggerable() {
        m_triggeringDelay = 0;
        m_id = 0;
    }

    virtual ~Triggerable() {
    }

    virtual void onAttacking(Unit* owner, int &damage); // trigger when attacking
    virtual void onAttackHiting(Unit* owner, Unit* target, int &damage); // trigger when attack hits something
    virtual void onAttackHited(Unit* owner, Unit* origin, int &damage); // trigger when being hit by an attack
    virtual void onSpelling(Unit* owner, Triggerable* spell); // trigger when casting a spell
    virtual void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell); // trigger when spell hit something
    virtual void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell); //trigger when being hit by a spell
    virtual void onTimer(Unit* owner); // every x secondes

    void setId(unsigned int id) {
        m_id = id;
    }

    unsigned int getId() {
        return m_id;
    }

    void setTriggeringDelay(float delay) {
        m_triggeringDelay = delay;
    }

    float getTriggeringDelay() {
        return m_triggeringDelay;
    }

protected:
    unsigned int m_id;
    float m_triggeringDelay;
};

class Spell : public Triggerable {
public:

    Spell() : Triggerable() {
    }

    ~Spell() {
    }

    virtual void onAttacking(Unit* owner, int &damage) { // trigger when attacking
    }

    virtual void onAttackHiting(Unit* owner, Unit* target, int &damage) { // trigger when attack hits something
    }

    virtual void onAttackHited(Unit* owner, Unit* origin, int &damage) { // trigger when being hit by an attack
    }

    virtual void onSpelling(Unit* owner, Triggerable* spell) { // trigger when casting a spell
    }

    virtual void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell) { // trigger when spell hit something
    }

    virtual void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell) { //trigger when being hit by a spell
    }

    virtual void onTimer(Unit* owner) { // every x secondes
    }

    virtual void onCast(Unit* owner) { // when owner uses spell without channeling time
    }

    virtual void onCastStart(Unit* owner) { // when owner starts chanelling
    }

    virtual void onCastEnd(Unit* owner) { // when owner ends chanelling
    }
protected:
    bool m_hasCastTime;
    float m_castDuration;
    float m_cooldown;
};

Unit** unitList;


#endif	/* TRIGGERABLE_HPP */

