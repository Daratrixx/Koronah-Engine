
#include "GameEngine.h"

void GameEngine::unitToUnitCollision(Unit* u1, Unit* u2) {
    glm::vec2 oPosition = u2->getPositionXY();
    float radius = u1->m_collisionRadius + u2->getRadius();

    glm::vec2 direction = oPosition - u1->m_position;
    float distance = glm::length(direction);
    if (distance < radius) {
        direction = direction * (radius - distance) / radius;
        if (u1->m_behavior == UNIT_BEHAVIOR_HOLD && u2->m_behavior == UNIT_BEHAVIOR_HOLD) {
            direction /= 2;
            u1->push(-direction.x, -direction.y);
            u2->push(direction.x, direction.y);
        } else {
            if (u1->m_behavior != UNIT_BEHAVIOR_HOLD)
                u1->push(-direction.x, -direction.y);
            if (u2->m_behavior != UNIT_BEHAVIOR_HOLD)
                u2->push(direction.x, direction.y);
        }
    }
}

void GameEngine::buildingToUnitCollision(Unit* b, Unit* u) {
    glm::vec2 oPosition = u->getPositionXY();
    float radius = b->m_collisionRadius + u->getRadius();

    glm::vec2 direction = oPosition - b->m_position;
    float distance = glm::length(direction);
    if (distance < radius) {
        direction = direction * (radius - distance) / radius;
        u->push(direction.x, direction.y);
    }
}

void GameEngine::unitToBuildingCollision(Unit* u, Unit* b) {
    buildingToUnitCollision(b, u);
}
