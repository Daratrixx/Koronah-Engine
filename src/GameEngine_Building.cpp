
#include "GameEngine.h"

bool GameEngine::buildingUpdate(Unit* b) {
    if (b->isAlive()) {
        if (b->isBuildingDone()) {
            if (b->m_attackCooldown > 0)
                b->m_attackCooldown -= m_tickDuration;
            switch (b->m_behavior) {
                case UNIT_BEHAVIOR_IDLE:
                    if (b->m_target == null || !b->m_target->isAlive()) {
                        b->m_target = unitGetEnemyTarget(b);
                    }
                    if (b->m_target != null) {
                        if (!unitDoAttackOn(b, (Unit*) b->m_target))
                            b->orderStop();
                    }
                    break;
                case UNIT_BEHAVIOR_ATTACKING:
                    if (b->m_target == null || !b->m_target->isAlive()) {
                        b->orderStop();
                    } else unitDoAttackOn(b, (Unit*) b->m_target);
                    break;
                case UNIT_BEHAVIOR_TRAINING:
                    if (b->m_rallyTarget != null && !b->m_rallyTarget->isAlive()) {
                        b->m_rallyTarget = null;
                        b->m_rallyDestination = b->m_position + glm::vec2(0, b->m_collisionRadius);
                    }
                    if (buildingDoTraining(b)) {
                        buildingDoEndTraining(b);
                    }
                    break;
                default:
                    std::cout << "undefined behavior: " << b->m_behavior << std::endl;
                    break;
            }
        } else if (buildingDoBuilding(b)) {
            buildingDoEndBuilding(b);
        }
        if(b->m_doCollision)
            buildingDoCollision(b);
        return false;
    }
    return true; // should remove
}

bool GameEngine::buildingDoBuilding(Unit* b) {
    b->build(m_tickDuration);
    return b->isBuildingDone();
}

void GameEngine::buildingDoEndBuilding(Unit* b) {
    //b->orderStop();
    b->m_rallyDestination = b->m_position + glm::vec2(0, b->m_collisionRadius);
}

bool GameEngine::buildingDoTraining(Unit* b) {
    b->train(m_tickDuration);
    return b->isTrainingDone();
}

void GameEngine::buildingDoEndTraining(Unit* b) {
    Unit* u = b->m_trainingUnit;
    addUnitToGame(u);
    u->m_teamColor = b->m_teamColor;
    u->m_ownerId = b->m_ownerId;
    if (b->m_rallyTarget != null) {
        u->m_position = positionAlongLine(b->m_position, b->m_rallyTarget->m_position, b->m_collisionRadius + u->m_collisionRadius);
        unitDoRightClick(u, b->m_rallyTarget);
        std::cout << "rally on unit" << std::endl;
    } else {
        u->m_position = positionAlongLine(b->m_position, b->m_rallyDestination, b->m_collisionRadius + u->m_collisionRadius);
        u->orderAttackMove(b->m_rallyDestination);
        std::cout << "rally on " << b->m_rallyDestination.x << "," << b->m_rallyDestination.y <<std::endl;
    }
    std::cout << "train done" << std::endl;
    b->orderTrain(u);
}

void GameEngine::buildingDoCollision(Unit* b) {
    for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
        Entity* e = *it;
        if (e != b && e->isUnit() && e->m_doCollision && !((Unit*) e)->isBuilding() && e->isAlive()) {
            buildingToUnitCollision(b, (Unit*) e);
        }
    }
}

void GameEngine::buildingDoRightClick(Unit* b, const glm::vec2 & position) {
    b->orderRally(position);
}

void GameEngine::buildingDoRightClick(Unit* b, Unit* target) {
    if (unitIsAlly(b, target))
        b->orderRally(target);
    else
        b->orderAttack(target);
}