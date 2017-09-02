
#include "Spell.h"

Spell::Spell() : Triggerable() {

}

Spell::~Spell() {

}

void Spell::onAttacking(Unit* owner, UInt & damage) {
}

void Spell::onAttackHiting(Unit* owner, Unit* target, UInt & damage) { // trigger when attack hits something
}

void Spell::onAttackHited(Unit* owner, Unit* origin, UInt & damage) { // trigger when being hit by an attack
}

void Spell::onSpelling(Unit* owner, Triggerable* spell) { // trigger when casting a spell
}

void Spell::onSpellHiting(Unit* owner, Unit* target, Triggerable* spell) { // trigger when spell hit something
}

void Spell::onSpellHited(Unit* owner, Unit* origin, Triggerable* spell) { // trigger when being hit by a spell
}

void Spell::onTimer(Unit* owner) { // every x secondes
}

void Spell::onCast(Unit* owner) { // when owner uses spell without channeling time
}

void Spell::onCastStart(Unit* owner) { // when owner starts chanelling
}

void Spell::onCastEnd(Unit* owner) { // when owner ends chanelling
}

