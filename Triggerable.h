/* 
 * File:   Triggerable.h
 * Author: ANTOINE
 *
 * Created on 2 septembre 2016, 14:18
 */

#ifndef TRIGGERABLE_H
#define	TRIGGERABLE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

class Triggerable {
public:
    Triggerable();
    virtual ~Triggerable();

    virtual void onAttacking(Unit* owner, int &damage); // triggers when attacking
    virtual void onAttackHiting(Unit* owner, Unit* target, int &damage); // triggers when attack hits something
    virtual void onAttackHited(Unit* owner, Unit* origin, int &damage); // triggers when being hit by an attack
    virtual void onSpelling(Unit* owner, Triggerable* spell); // triggers when casting a spell
    virtual void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell); // triggers when spell hit something
    virtual void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell); // triggers when being hit by a spell
    virtual void onTimer(Unit* owner); // triggers every x secondes

    void setId(unsigned int id);
    unsigned int getId();
    void setTriggeringDelay(float delay);
    float getTriggeringDelay();

    unsigned int m_id;
    float m_triggeringDelay;
};

class TriggerableInstance {
    friend class Triggerable;
    Triggerable* m_triggerableModel;
};

#endif	/* TRIGGERABLE_H */
