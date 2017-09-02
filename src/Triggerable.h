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

    virtual void onAttacking(Unit* owner, UInt & damage); // triggers when attacking
    virtual void onAttackHiting(Unit* owner, Unit* target, UInt & damage); // triggers when attack hits something
    virtual void onAttackHited(Unit* owner, Unit* origin, UInt & damage); // triggers when being hit by an attack
    virtual void onSpelling(Unit* owner, Triggerable* spell); // triggers when casting a spell
    virtual void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell); // triggers when spell hit something
    virtual void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell); // triggers when being hit by a spell
    virtual void onTimer(Unit* owner); // triggers every x secondes

    void setId(const UInt & id);
    UInt getId() const;
    void setTriggeringDelay(const float & delay);
    float getTriggeringDelay() const;

    UInt m_id;
    float m_triggeringDelay;
};

class TriggerableInstance {
    friend class Triggerable;
    Triggerable* m_triggerableModel;
};

#endif	/* TRIGGERABLE_H */
