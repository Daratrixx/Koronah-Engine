/* 
 * File:   GameEnigine.h
 * Author: ANTOINE
 *
 * Created on 24 septembre 2016, 15:42
 */

#ifndef GAMEENIGINE_H
#define	GAMEENIGINE_H


#include "Types.h"
#include "Unit.h"
#include "Entity.h"
#include "Player.h"
#include "Missile.h"

class GameEngine {
public:
    // general
    GameEngine();
    ~GameEngine();
    void clearGame();
    void loadGame();
    void gameTick(float time);

    void addEntityToGame(Entity* e);
    void removeEntityFromGame(Entity* e);
    void addUnitToGame(Unit* u);
    Unit* getUnit(unsigned int id);
    void removeUnitFromGame(Unit* u);
    void addMissileToGame(Missile* m);
    void removeMissileFromGame(Missile* m);
    void doRightClick(Unit* u, glm::vec2 position);
    void doRightClick(Unit* u, Unit* target);
    void updateAngle(Entity* e, glm::vec2 direction);
    
    // players
    void initPlayers();
    bool playerIsAlly(Player* p1, Player* p2);
    void playerSetAlly(Player* p1, Player* p2);
    bool playerIsEnemy(Player* p1, Player* p2);
    void playerSetEnemy(Player* p1, Player* p2);

    // units
    bool unitUpdate(Unit* u);
    Unit* unitGetAllyTarget(Unit* u);
    Unit* unitGetEnemyTarget(Unit* u);
    bool unitDoMoveTo(Unit* u, glm::vec2 destination);
    bool unitDoAttackOn(Unit* u, Unit* target);
    void unitDoCollision(Unit* u);
    bool unitIsAlly(Unit* u1, Unit* u2);
    bool unitIsEnemy(Unit* u1, Unit* u2);
    void unitDoRightClick(Unit* u, glm::vec2 position);
    void unitDoRightClick(Unit* u, Unit* target);
    bool unitDoStartBuilding(Unit* u, Unit* b);

    // buildings
    bool buildingUpdate(Unit* b);
    bool buildingDoBuilding(Unit* b);
    void buildingDoEndBuilding(Unit* b);
    bool buildingDoTraining(Unit* b);
    void buildingDoEndTraining(Unit* b);
    void buildingDoCollision(Unit* b);
    void buildingDoRightClick(Unit* b, glm::vec2 position);
    void buildingDoRightClick(Unit* b, Unit* target);

    // collision
    void unitToUnitCollision(Unit* u1, Unit* u2);
    void buildingToUnitCollision(Unit* b, Unit* u);
    void unitToBuildingCollision(Unit* u, Unit* b);

    // missile
    bool missileUpdate(Missile* m);
    bool missileHit(Missile* m, Unit* target);
    bool missileMoveTo(Missile* m, glm::vec2 destination);
    
    // fields

    unsigned int m_currentPlayerId;
    unsigned int m_playerRelation[PLAYER_COUNT][PLAYER_COUNT];
    float m_tickDuration;
    Player* m_players[PLAYER_COUNT];
    std::list<Unit*> m_unitType;
    std::list<Missile*> m_missileType;
    std::list<Entity*> m_entities;
    std::list<Missile*> m_missiles;
    std::list<Unit*> m_unitsAlive; // all units that are alive
    std::list<Unit*> m_unitsDead; // all units that are dead
    std::list<Unit*> m_buildings; // all unit that are buildings
    std::list<Unit*> m_unitsPlayer[PLAYER_COUNT]; // units separated by player owner
    //Upgrade m_techTree[8];
    unsigned char** m_collisionMap;
    float m_gameTime;
    float m_dayTime;
};

#endif	/* GAMEENIGINE_H */

