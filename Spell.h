
/* 
 * File:   Spell.h
 * Author: ANTOINE
 *
 * Created on 22 novembre 2016, 14:03
 */

#ifndef SPELL_H
#define SPELL_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

#ifndef TRIGGERABLE_H
#include "Triggerable.h"
#endif

class Spell : public Triggerable {
public:
    Spell();
    ~Spell();

    virtual void onAttacking(Unit* owner, int &damage); // trigger when attacking
    virtual void onAttackHiting(Unit* owner, Unit* target, int &damage); // trigger when attack hits something
    virtual void onAttackHited(Unit* owner, Unit* origin, int &damage); // trigger when being hit by an attack
    virtual void onSpelling(Unit* owner, Triggerable* spell); // trigger when casting a spell
    virtual void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell); // trigger when spell hit something
    virtual void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell); // trigger when being hit by a spell
    virtual void onTimer(Unit* owner); // every x secondes
    virtual void onCast(Unit* owner); // when owner uses spell without channeling time
    virtual void onCastStart(Unit* owner); // when owner starts chanelling
    virtual void onCastEnd(Unit* owner); // when owner ends chanelling
    
    
    bool m_hasCastTime;
    float m_castDuration;
    float m_cooldownDuration;
};

class SpellInstance {
    friend class Spell;
public:
    SpellInstance();
    SpellInstance(Spell* spellModel);
    
    bool isCooldownOver();
    bool isCastTimeOver();
    void startCooldown();
    void startCastTime();
    float getRemainingCooldown();
    float getPercentRemainingCooldown();
    float getRemainingCastTime();
    float getPercentRemainingCastTime();

    void onAttacking(Unit* owner, int &damage); // trigger when attacking
    void onAttackHiting(Unit* owner, Unit* target, int &damage); // trigger when attack hits something
    void onAttackHited(Unit* owner, Unit* origin, int &damage); // trigger when being hit by an attack
    void onSpelling(Unit* owner, Triggerable* spell); // trigger when casting a spell
    void onSpellHiting(Unit* owner, Unit* target, Triggerable* spell); // trigger when spell hit something
    void onSpellHited(Unit* owner, Unit* origin, Triggerable* spell); // trigger when being hit by a spell
    void onTimer(Unit* owner); // every x secondes
    void onCast(Unit* owner); // when owner uses spell without channeling time
    void onCastStart(Unit* owner); // when owner starts chanelling
    void onCastEnd(Unit* owner); // when owner ends chanelling
    
private:
    Spell* m_spellModel;
    float m_remainingCastTime;
    float m_remainingCooldown;
};

#endif /* SPELL_H */

