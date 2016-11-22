
#include "Missile.h"

Missile::Missile() : Entity() {
    m_damage = 5;
    m_doCollision = false;
    m_missileOwner = null;
    m_radius = 1;
}

Missile::Missile(Missile* m) : Entity(m) {
    m_damage = m->m_damage;
    m_missileOwner = null;
}

Missile::~Missile() {

}

bool Missile::isMissile() const {
    return true;
}
