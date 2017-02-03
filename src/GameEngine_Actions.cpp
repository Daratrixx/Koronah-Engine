#include "GameEngine.h"

void GameEngine::unitCreate(Unit* unitType, unsigned ownerId, glm::vec2 position) {
    std::cout << "Create unit for player " << ownerId << " at " << position.x << "," << position.y << std::endl;
    if (unitType != null && ownerId < PLAYER_COUNT) {
        Unit* u = new Unit(unitType);
        u->m_ownerId = ownerId;
        u->m_teamColor = m_players[ownerId]->m_teamColor;
        u->setPositionXY(position);
        u->m_trainingProgress = 1;
        u->m_buildingProgress = 1;
        addUnitToGame(u);
    }
}

void GameEngine::unitMove(Unit* u, glm::vec2 position) {
    if (u != null)
        u->setPositionXY(position);
}

void GameEngine::unitKill(Unit* u) {
    if (u != null)
        killUnit(u);
}