
#include "GameEngine.h"

GameEngine::GameEngine() {
    for (unsigned int i = 0; i < PLAYER_COUNT; i++)
        m_players[i] = null;
    m_currentPlayerId = PLAYER_1;
    initPlayers();
    loadGame();
}

GameEngine::~GameEngine() {
    clearGame();
}

void GameEngine::clearGame() {
    while (!m_entities.empty())
        removeEntityFromGame(m_entities.back());
    for (unsigned int i = 0; i < PLAYER_COUNT; i++)
        delete m_players[i];
}

void GameEngine::loadGame() {
    std::cout << "start loading str" << std::endl;
    Missile* m = new Missile();
    m->m_movingSpeed = 50;
    m->setScale(1, 1, 1);
    m->setModelId(1);
    m->setTextureId(4);
    m->setHaloMapId(5);
    m->m_teamColor = COLOR_WHITE;
    m_missileType.push_back(m);

    Unit* u = new Unit();
    u->setName("soldat");
    u->setScale(1.5f, 1.5f, 1.5f);
    u->setModelId(0);
    u->setTextureId(2);
    u->setHaloMapId(3);
    u->setMovingSpeed(25);
    u->setRadius(2);
    u->m_missileType = m_missileType.front();
    m_unitType.push_back(u);
    /*for (unsigned int i = 0; i < 50; i++) {
        int playerId = rand() % PLAYER_COUNT;
        u = m_unitType.front()->clone();
        u->setPositionXYZ(-25 + i * 3, 5 + 3 * playerId, 0);
        u->setOwnerId(playerId);
        u->setTeamColor(m_players[playerId]->m_color);
        u->orderStop();
        u->m_trainingProgress = 1;
        u->m_buildingProgress = 1;
        addUnitToGame(u);
    }*/
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 2; j++) {
            u = new Unit(m_unitType.front());
            u->m_ownerId = j;
            u->m_teamColor = m_players[j]->m_teamColor;
            u->setPositionXY(25 - (j * 50), 50 - i);
            u->m_trainingProgress = 1;
            u->m_buildingProgress = 1;
            u->orderAttackMove(glm::vec2(0, 0));
            addUnitToGame(u);
        }
    }
    /*u = new Unit();
    u->setName("caserne");
    u->setPositionXYZ(50, 0, 0);
    u->setScale(1.5f, 1.5f, 1.5f);
    u->m_radius *= 3;
    u->setModelId(5);
    u->setTextureId(8);
    u->setHaloMapId(11);
    u->setOwnerId(m_currentPlayerId);
    u->setTeamColor(m_players[m_currentPlayerId]->m_color);
    u->m_isBuilding = true;
    object->m_buildingProgress = 1;
    buildingDoRightClick(u, glm::vec2(-50, 0));
    u->m_rallyDestination = glm::vec2(-50, 0);
    u->orderTrain(m_unitType.front());
    addUnitToGame(u);

    u = new Unit(u);
    u->setPositionXYZ(-50, 0, 0);
    u->setOwnerId(m_currentPlayerId + 1);
    u->setTeamColor(m_players[m_currentPlayerId + 1]->m_color);
    u->m_buildingProgress = 1;
    buildingDoRightClick(u, glm::vec2(50, 0));
    u->m_rallyDestination = glm::vec2(50, 0);
    u->orderTrain(m_unitType.front());
    addUnitToGame(u);*/
}

void GameEngine::gameTick(float time) {
    m_tickDuration = time;
    m_gameTime += time;

    std::list<Unit*>::iterator prevU;

    for (std::list<Unit*>::iterator it = m_unitsAlive.begin(); it != m_unitsAlive.end(); it++) {
        if (!(*it)->isBuilding()) {
            if (unitUpdate(*it)) {
                if (it == m_unitsAlive.begin()) {
                    removeUnitFromGame(*it);
                    it = m_unitsAlive.begin();
                } else {
                    removeUnitFromGame(*it);
                    it = prevU;
                }
            }
        } else if (buildingUpdate(*it)) {
            if (it == m_unitsAlive.begin()) {
                removeUnitFromGame(*it);
                it = m_unitsAlive.begin();
            } else {
                removeUnitFromGame(*it);
                it = prevU;
            }
        }
        prevU = it;
    }

    std::list<Missile*>::iterator prevM;

    for (std::list<Missile*>::iterator it = m_missiles.begin(); it != m_missiles.end(); it++) {
        if (missileUpdate(*it)) {
            if (it == m_missiles.begin()) {
                removeMissileFromGame(*it);
                it = m_missiles.begin();
            } else {
                removeMissileFromGame(*it);
                it = prevM;
            }
        }
        prevM = it;
    }

}

void GameEngine::addEntityToGame(Entity* e) {
    m_entities.push_back(e);
}

void GameEngine::removeEntityFromGame(Entity* e) {
    m_entities.remove(e);
    delete e;
}

void GameEngine::addUnitToGame(Unit* u) {
    m_unitsAlive.push_back(u);
    addEntityToGame(u);
}

Unit* GameEngine::getUnit(unsigned int id) {
    if (id < m_unitsAlive.size()) {
        unsigned int current = 0;
        for (std::list<Unit*>::iterator it = m_unitsAlive.begin(); it != m_unitsAlive.end(); it++) {
            if (current == id)
                return *it;
            current++;
        }
    }
    return null;
}

void GameEngine::removeUnitFromGame(Unit* u) {
    m_unitsAlive.remove(u);
    for (std::list<Unit*>::iterator it = m_unitsAlive.begin(); it != m_unitsAlive.end(); it++) {
        Unit* unit = *it;
        if (unit->m_target == u)
            unit->m_target = null;
    }
    for (std::list<Missile*>::iterator it = m_missiles.begin(); it != m_missiles.end(); it++) {
        Missile* m = *it;
        if (m->m_target == u)
            m->m_target = null;
        if (m->m_missileOwner == u)
            m->m_missileOwner = null;
    }
    removeEntityFromGame(u);
}

void GameEngine::addMissileToGame(Missile* m) {
    m_missiles.push_back(m);
    addEntityToGame(m);
}

void GameEngine::removeMissileFromGame(Missile* m) {
    m_missiles.remove(m);
    removeEntityFromGame(m);
}

void GameEngine::doRightClick(Unit* u, glm::vec2 position) {
    if (u->isBuilding())
        buildingDoRightClick(u, position);
    else
        unitDoRightClick(u, position);

}

void GameEngine::doRightClick(Unit* u, Unit* target) {
    if (u->isBuilding())
        buildingDoRightClick(u, target);
    else
        unitDoRightClick(u, target);
}

void GameEngine::updateAngle(Entity* e, glm::vec2 direction) {
    direction = glm::normalize(direction);
    float angle = glm::asin(direction.y) * 180 / PI;
    if (direction.x < 0)
        angle += 90;
    if (direction.y < 0)
        angle *= -1;
    e->m_angle.z = angle;
}
