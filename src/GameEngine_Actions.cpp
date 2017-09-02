#include "GameEngine.h"

void GameEngine::unitCreate(Unit* unitType, Player* owner, const glm::vec2 & position) {
    //std::cout << "Create unit " << (unitType != null ? unitType->m_name : "NULL_VALUE") << " for player " << (owner != null ? toString(owner->m_playerId) : "NULL_VALUE") << " at " << position.x << "," << position.y << std::endl;
    if (unitType != null && owner != null && !m_freeUnitId.empty()) { // can still create units
        Unit* u = new Unit(unitType);
        u->m_ownerId = owner->m_playerId;
        u->m_teamColor = owner->m_teamColor;
        u->setPositionXY(position);
        u->m_trainingProgress = 1;
        u->m_buildingProgress = 1;
        u->m_unitId = m_freeUnitId.top();
        m_freeUnitId.pop();
        addUnitToGame(u);
    }
}

void GameEngine::unitMove(Unit* u, const glm::vec2 & position) {
    if (u != null)
        u->setPositionXY(position);
}

void GameEngine::unitKill(Unit* u) {
    if (u != null)
        killUnit(u);
}