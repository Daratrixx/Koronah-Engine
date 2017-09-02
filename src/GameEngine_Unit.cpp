
#include "GameEngine.h"

bool GameEngine::unitUpdate(Unit* u) {
    if (u->isAlive()) {
        if (u->m_attackCooldown > 0)
            u->m_attackCooldown -= m_tickDuration;
        switch (u->m_behavior) {
            case UNIT_BEHAVIOR_PUSHED:
                if (u->m_lastCollisionHit > 1.5f)
                    u->orderAttackMove(u->m_destination);
                else
                    u->m_lastCollisionHit += m_tickDuration;
                break;
            case UNIT_BEHAVIOR_IDLE:
                if (u->m_target == null || !u->m_target->isAlive()) {
                    u->m_target = unitGetEnemyTarget(u);
                }
                if (u->m_target != null) {
                    unitDoMoveTo(u, u->m_target->getPositionXY());
                    unitDoAttackOn(u, (Unit*) u->m_target);
                } else u->orderMove(u->m_destination);
                break;
            case UNIT_BEHAVIOR_HOLD:
                if (u->m_target == null || !u->m_target->isAlive()) {
                    u->m_target = unitGetEnemyTarget(u);
                }
                if (u->m_target != null) {
                    if (!unitDoAttackOn(u, (Unit*) u->m_target))
                        u->m_target = null;
                }
                break;
            case UNIT_BEHAVIOR_BUILDING:
                if (unitDoStartBuilding(u, null))
                    u->orderStop();
                break;
            case UNIT_BEHAVIOR_MOVING:
                if (unitDoMoveTo(u, u->m_destination))
                    u->orderStop();
                break;
            case UNIT_BEHAVIOR_FOLLOWING:
                if (u->m_target != null && u->m_target->isAlive()) {
                    unitDoMoveTo(u, u->m_target->getPositionXY());
                } else u->orderStop();
                break;
            case UNIT_BEHAVIOR_PATROLING:
                if (u->m_target == null) {
                    u->m_target = unitGetEnemyTarget(u);
                }
                if (u->m_target != null) {
                    if (!unitDoAttackOn(u, (Unit*) u->m_target))
                        unitDoMoveTo(u, u->m_target->getPositionXY());
                } else unitDoMoveTo(u, u->m_destination);
                break;
            case UNIT_BEHAVIOR_ATTACK_MOVING:
                if (u->m_target == null || !u->m_target->isAlive()) {
                    u->m_target = unitGetEnemyTarget(u);
                }
                if (u->m_target != null) {
                    if (!unitDoAttackOn(u, (Unit*) u->m_target))
                        unitDoMoveTo(u, u->m_target->getPositionXY());
                } else unitDoMoveTo(u, u->m_destination);
                break;
            case UNIT_BEHAVIOR_ATTACKING:
                if (u->m_target == null || !u->m_target->isAlive()) {
                    u->m_target = unitGetEnemyTarget(u);
                }
                if (u->m_target != null) {
                    if (!unitDoAttackOn(u, (Unit*) u->m_target))
                        unitDoMoveTo(u, u->m_target->getPositionXY());
                } else u->orderStop();
                break;
            default:
                break;
        }
        if (u->m_doCollision)
            unitDoCollision(u);
        return false;
    }
    return true; // should remove
}

Unit* GameEngine::unitGetAllyTarget(Unit* u) {
    return null;
}

void GameEngine::unitDamageUnit(Unit* u, Unit* target) {
    float damage = u->getDamage();
    unitDealsDamage(u, target, damage);
    unitTakesDamage(target, u, damage);
    target->damage(damage);
    if (target->isDead()) {
        unitKills(u, target);
        unitDies(target, u);
        killUnit(target);
    }
}

Unit* GameEngine::unitGetEnemyTarget(Unit* u) {
    Unit* closest = null;
    float distance = 0;
    for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
        if ((*it)->isAlive() && (*it)->isUnit() && unitIsEnemy(u, (Unit*) * it)) {
            Unit* u2 = (Unit*) * it;
            float dist = glm::length(u2->m_position - u->m_position);
            if (closest != null) {
                if (dist < distance && dist < u->m_attackAggressionRange) {
                    closest = u2;
                    distance = dist;
                }
            } else if (dist < u->m_attackAggressionRange) {
                closest = u2;
                distance = dist;
            }
        }
    }
    return closest;
}

bool GameEngine::unitDoMoveTo(Unit* u, const glm::vec2 & destination) {
    float radius, distance, speed;
    speed = u->m_movingSpeed * m_tickDuration;
    radius = u->m_collisionRadius;
    if (u->m_target != null) {
        if (u->m_behavior == UNIT_BEHAVIOR_FOLLOWING) {
            radius += u->m_target->getRadius();
        }
        if (u->m_behavior == UNIT_BEHAVIOR_ATTACKING) {
            radius += u->m_target->getRadius() + u->m_attackRange;
        }
    }
    glm::vec2 direction = destination - u->m_position;
    distance = glm::length(direction);

    if (distance - radius > speed) {
        u->m_position += glm::normalize(direction) * speed;
        updateAngle(u, direction);
        return false; // still moving
    }
    return true; // got to destination
}

bool GameEngine::unitDoAttackOn(Unit* u, Unit* target) {
    if (u->m_attackRange + u->m_collisionRadius + target->m_collisionRadius < glm::length(target->m_position - u->m_position))
        return false; // not in range, get closer
    if (u->m_attackCooldown <= 0) {
        if (u->m_missileType != null && u->m_missileType->isMissile()) { // missile attack
            Missile* m = new Missile((Missile*) u->m_missileType);
            m->m_target = target;
            m->m_missileOwner = u;
            m->m_damage = u->m_attackDamage;
            m->m_position = u->m_position;
            addMissileToGame(m);
        } else { // instant attack
            unitDamageUnit(u, target);
        }
        u->m_attackCooldown = u->m_attackReloadTime;
    }
    return true;
}

void GameEngine::unitDoCollision(Unit* u) {
    for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
        Entity* e = *it;
        if (e != u && e->isUnit() && e->m_doCollision && e->isAlive()) {
            if (!((Unit*) e)->isBuilding())
                unitToUnitCollision(u, (Unit*) e);
            else
                unitToBuildingCollision(u, (Unit*) e);
        }
    }
}

bool GameEngine::unitIsAlly(Unit* u1, Unit* u2) {
    if (m_players[u1->m_ownerId] == m_players[u2->m_ownerId]) return true;
    return playerIsAlly(m_players[u1->m_ownerId], m_players[u2->m_ownerId]);
}

bool GameEngine::unitIsEnemy(Unit* u1, Unit* u2) {
    if (m_players[u1->m_ownerId] == m_players[u2->m_ownerId]) return false;
    return playerIsEnemy(m_players[u1->m_ownerId], m_players[u2->m_ownerId]);
}

void GameEngine::unitDoRightClick(Unit* u, const glm::vec2 & position) {
    u->orderMove(position);
}

void GameEngine::unitDoRightClick(Unit* u, Unit* target) {
    if (unitIsAlly(u, target))
        u->orderFollow(target);
    else
        u->orderAttack(target);
}

bool GameEngine::unitDoStartBuilding(Unit* u, Unit* b) {
    if (glm::length(u->m_destination - u->m_position) < u->m_collisionRadius) {

        return true;
    }
    return false;
}