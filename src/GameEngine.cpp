
#include <stdlib.h>

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
    while (!m_entities.empty()) {
        delete m_entities.front();
        m_entities.pop_front();
    }
    m_unitsAll.clear();
    m_unitsAlive.clear();
    m_unitsDead.clear();
    m_buildings.clear();
    m_missiles.clear();
    for (unsigned int i = 0; i < PLAYER_COUNT; i++) {
        m_unitsPlayer[i].clear();
        delete m_players[i];
    }
}

void GameEngine::loadGame() {
    std::cout << "start loading str" << std::endl;
    Missile* m = new Missile();
    m->m_movingSpeed = 50;
    m->setScale(1, 1, 1);
    m->setModelId(1);
    m->setTextureId(3);
    m->setHaloMapId(5);
    m->m_teamColor = COLOR_WHITE;
    m_missileType.push_back(m);

    Unit* u = new Unit();
    u->setName("soldat");
    u->setScale(1.5f, 1.5f, 1.5f);
    u->setModelId(0);
    u->setTextureId(3);
    u->setHaloMapId(0);
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
    for (int j = 0; j < 2; j++) {
        int r = 50;
        if(j == 0)
            r = 100;
        for (int i = 0; i < r; i++) {
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

    for (std::list<Unit*>::iterator it = m_unitsAll.begin(); it != m_unitsAll.end(); it++) {
        if ((*it)->isAlive()) {
            if (!(*it)->isBuilding()) {
                if (unitUpdate(*it)) {
                    if (it == m_unitsAll.begin()) {
                        //removeUnitFromGame(*it);
                        killUnit(*it);
                        //it = m_unitsAll.begin();
                    } else {
                        //removeUnitFromGame(*it);
                        killUnit(*it);
                        //it = prevU;
                    }
                }
            } else if (buildingUpdate(*it)) {
                if (it == m_unitsAll.begin()) {
                    //removeUnitFromGame(*it);
                    killUnit(*it);
                    //it = m_unitsAll.begin();
                } else {
                    //removeUnitFromGame(*it);
                    killUnit(*it);
                    //it = prevU;
                }
            }
        }
        //prevU = it;
    }

    std::list<Missile*>::iterator prevM;

    for (std::list<Missile*>::iterator it = m_missiles.begin(); it != m_missiles.end(); it++) {
        if (missileUpdate(*it)) {
            if (it == m_missiles.begin()) {
                removeMissileFromGame(*it);
                delete *it;
                it = m_missiles.begin();
            } else {
                removeMissileFromGame(*it);
                delete *it;
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
}

void GameEngine::addUnitToGame(Unit* u) {
    m_unitsAll.push_back(u);
    m_unitsAlive.push_back(u);
    if (u->m_isBuilding)
        m_buildings.push_back(u);
    m_unitsPlayer[u->getOwnerId()].push_back(u);
    addEntityToGame(u);
}

Unit* GameEngine::getUnit(unsigned int id) {
    if (id < m_unitsAll.size()) {
        unsigned int current = 0;
        for (std::list<Unit*>::iterator it = m_unitsAll.begin(); it != m_unitsAll.end(); it++) {
            if (current == id)
                return *it;
            current++;
        }
    }
    return null;
}

Unit* GameEngine::getUnitAlive(unsigned int id) {
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

Unit* GameEngine::getUnitDead(unsigned int id) {
    if (id < m_unitsDead.size()) {
        unsigned int current = 0;
        for (std::list<Unit*>::iterator it = m_unitsDead.begin(); it != m_unitsDead.end(); it++) {
            if (current == id)
                return *it;
            current++;
        }
    }
    return null;
}

void GameEngine::removeUnitFromGame(Unit* u) {
    m_unitsAll.remove(u);
    if (u->isAlive())
        m_unitsAlive.remove(u);
    else
        m_unitsDead.remove(u);
    if (u->isBuilding())
        m_buildings.remove(u);

    m_unitsPlayer[u->getOwnerId()].remove(u);

    for (std::list<Unit*>::iterator it = m_unitsAll.begin(); it != m_unitsAll.end(); it++) {
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

void GameEngine::killUnit(Unit* u) {
    if (u != null) {
        u->m_selectionCircleDisplayed = false;
        m_unitsAlive.remove(u);
        m_unitsDead.push_back(u);
    }
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
