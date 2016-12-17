
#include "Spell.h"

SpellInstance::SpellInstance() {
    m_spellModel = null;
    m_remainingCastTime = 0;
    m_remainingCooldown = 0;
}

SpellInstance::SpellInstance(Spell* spellModel) {
    m_spellModel = m_spellModel;
    m_remainingCastTime = 0;
    m_remainingCooldown = 0;
}

bool SpellInstance::isCooldownOver() {
    if (m_spellModel != null) {
        return m_remainingCooldown < 0;
    }
    return false;
}

bool SpellInstance::isCastTimeOver() {
    if (m_spellModel != null) {
        if(m_spellModel->m_hasCastTime)
            return m_remainingCastTime < 0;
        return true;
    }
    return false;
}

void SpellInstance::startCooldown() {
    if (m_spellModel != null) {
        m_remainingCooldown = m_spellModel->m_cooldownDuration;
    }
}

void SpellInstance::startCastTime() {
    if (m_spellModel != null) {
        m_remainingCooldown = m_spellModel->m_cooldownDuration;
    }
}
float SpellInstance::getRemainingCooldown() {
    return m_remainingCooldown;
}

float SpellInstance::getPercentRemainingCooldown() {
    if (m_spellModel != null) {
        m_remainingCooldown = m_spellModel->m_cooldownDuration;
    }
    return 0;
}
float SpellInstance::getRemainingCastTime() {
    return m_remainingCastTime;
}

float SpellInstance::getPercentRemainingCastTime() {
    if (m_spellModel != null) {
        m_remainingCooldown = m_spellModel->m_cooldownDuration;
    }
    return 0;
}

void SpellInstance::onAttacking(Unit* owner, int &damage) { // trigger when attacking
    if (m_spellModel != null) {
        m_spellModel->onAttacking(owner, damage);
    }
}

void SpellInstance::onAttackHiting(Unit* owner, Unit* target, int &damage) { // trigger when attack hits something
    if (m_spellModel != null) {
        m_spellModel->onAttackHiting(owner, target, damage);
    }
}

void SpellInstance::onAttackHited(Unit* owner, Unit* origin, int &damage) { // trigger when being hit by an attack
    if (m_spellModel != null) {
        m_spellModel->onAttackHited(owner, origin, damage);
    }
}

void SpellInstance::onSpelling(Unit* owner, Triggerable* spell) { // trigger when casting a spell
    if (m_spellModel != null) {
        m_spellModel->onSpelling(owner, spell);
    }
}

void SpellInstance::onSpellHiting(Unit* owner, Unit* target, Triggerable* spell) { // trigger when spell hit something
    if (m_spellModel != null) {
        m_spellModel->onSpellHiting(owner, target, spell);
    }
}

void SpellInstance::onSpellHited(Unit* owner, Unit* origin, Triggerable* spell) { // trigger when being hit by a spell
    if (m_spellModel != null) {
        m_spellModel->onSpellHited(owner, origin, spell);
    }
}

void SpellInstance::onTimer(Unit* owner) { // every x secondes
    if (m_spellModel != null) {
        m_spellModel->onTimer(owner);
    }
}

void SpellInstance::onCast(Unit* owner) { // when owner uses spell without channeling time
    if (m_spellModel != null) {
        m_spellModel->onCast(owner);
    }
}

void SpellInstance::onCastStart(Unit* owner) { // when owner starts chanelling
    if (m_spellModel != null) {
        m_spellModel->onCast(owner);
    }
}

void SpellInstance::onCastEnd(Unit* owner) { // when owner ends chanelling
    if (m_spellModel != null) {
        m_spellModel->onCastEnd(owner);
    }
}
