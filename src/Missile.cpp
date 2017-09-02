
#include "Missile.h"

Missile::Missile() : Entity() {
    m_damage = 5;
    m_doCollision = false;
    m_missileOwner = null;
    m_collisionRadius = 1;
}

Missile::Missile(Missile* m) : Entity(m) {
    m_damage = m->getDamage();
    m_missileOwner = null;
}

Missile::~Missile() {

}

bool Missile::writeInFile(std::ofstream & fout) {
    /*unsigned addr = (unsigned)this;
    unsigned size = sizeof(this);
    fout.write((char*) &addr, sizeof(unsigned));
    fout.write((char*) &size, sizeof(unsigned));
    fout.write((char*) this, size);*/
    return true;
}

bool Missile::readFromFile(std::ifstream & fin) {
    fin.read((char*) this, sizeof(this));
    return true;
}

bool Missile::isMissile() const {
    return true;
}

float Missile::getDamage() {
    return m_missileOwner != null ? m_missileOwner->getDamage() : m_damage;
}
