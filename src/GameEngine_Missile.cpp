
#include "GameEngine.h"

bool GameEngine::missileUpdate(Missile* m) {
    if(m->m_target == null || !m->m_target->isAlive())
        return true;
    if (missileHit(m, (Unit*) m->m_target))
        return true;
    missileMoveTo(m, m->m_target->m_position);
    return false;
}

bool GameEngine::missileHit(Missile* m, Unit* target) {
    if(m->m_radius + target->m_radius >= glm::length(target->m_position - m->m_position)) {
        unitDamageUnit((Unit*)m->m_missileOwner, target);
        return true;
    }
    return false;
}

bool GameEngine::missileMoveTo(Missile* m, glm::vec2 destination) {
    float radius, distance, speed;
    speed = m->m_movingSpeed * m_tickDuration;
    radius = m->m_radius;
    glm::vec2 direction = destination - m->m_position;
    distance = glm::length(direction);
    if (distance - radius > speed) {
        m->m_position += glm::normalize(direction) * speed;
        updateAngle(m, direction);
        return false; // still moving
    }
    return true; // got to destination
}
