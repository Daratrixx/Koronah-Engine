/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Triggerable.h"

Triggerable::Triggerable() {
    m_triggeringDelay = 0;
    m_id = 0;
}

Triggerable::~Triggerable() {
}

void Triggerable::onAttacking(Unit* owner, UInt & damage) { // triggers when attacking
}

void Triggerable::onAttackHiting(Unit* owner, Unit* target, UInt & damage) { // triggers when attack hits something
}

void Triggerable::onAttackHited(Unit* owner, Unit* origin, UInt & damage) { // triggers when being hit by an attack
}

void Triggerable::onSpelling(Unit* owner, Triggerable* spell) { // triggers when casting a spell
}

void Triggerable::onSpellHiting(Unit* owner, Unit* target, Triggerable* spell) { // triggers when spell hit something
}

void Triggerable::onSpellHited(Unit* owner, Unit* origin, Triggerable* spell) { // triggers when being hit by a spell
}

void Triggerable::onTimer(Unit* owner) { // triggers every x secondes
}

void Triggerable::setId(const UInt & id) {
    m_id = id;
}

UInt Triggerable::getId() const{
    return m_id;
}

void Triggerable::setTriggeringDelay(const float & delay) {
    m_triggeringDelay = delay;
}

float Triggerable::getTriggeringDelay() const {
    return m_triggeringDelay;
}
