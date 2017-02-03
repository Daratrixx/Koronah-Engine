/* 
 * File:   GameEnigine.h
 * Author: ANTOINE
 *
 * Created on 24 septembre 2016, 15:42
 */

#ifndef GAMEENIGINE_H
#define GAMEENIGINE_H


#include "Types.h"
#include "Unit.h"
#include "Entity.h"
#include "Player.h"
#include "Missile.h"
#include "Script.h"
#include "ScriptInstance.h"
#include <queue>

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
    Unit* getUnitAlive(unsigned int id);
    Unit* getUnitDead(unsigned int id);
    void removeUnitFromGame(Unit* u);
    void addMissileToGame(Missile* m);
    void removeMissileFromGame(Missile* m);
    void killUnit(Unit* u);
    void doRightClick(Unit* u, glm::vec2 position);
    void doRightClick(Unit* u, Unit* target);
    void updateAngle(Entity* e, glm::vec2 direction);

    // players
    void initPlayers();
    bool playerIsAlly(Player* p1, Player* p2);
    bool playerIsAlly(unsigned p1, unsigned p2);
    void playerSetAlly(Player* p1, Player* p2);
    void playerSetAlly(unsigned p1, unsigned p2);
    bool playerIsEnemy(Player* p1, Player* p2);
    bool playerIsEnemy(unsigned p1, unsigned p2);
    void playerSetEnemy(Player* p1, Player* p2);
    void playerSetEnemy(unsigned p1, unsigned p2);

    // units
    bool unitUpdate(Unit* u);
    Unit* unitGetAllyTarget(Unit* u);
    Unit* unitGetEnemyTarget(Unit* u);
    void unitDamageUnit(Unit* u, Unit* target);
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

    // scripts
    void scriptMain();
    bool checkConditions(ScriptInstance *si);
    void runScript(ScriptInstance *si);
    bool parseCondition(ScriptInstance *si, const std::string & condition);
    void parseAction(ScriptInstance *si, std::string action);
    std::vector<std::string> scriptArguments(const std::string & function);
    bool scriptStartsWith(const std::string & script, const std::string & start);
    Unit* scriptToUnit(ScriptInstance* si, const std::string & script);
    Player* scriptToPlayer(ScriptInstance* si, const std::string & script);
    unsigned scriptToPlayerId(ScriptInstance* si, const std::string & script);
    glm::vec2 scriptToPosition(ScriptInstance* si, const std::string & script);
    glm::vec4 scriptToArea(ScriptInstance* si, const std::string & script);
    
    // events
    void unitEntersGame(Unit* unit);
    void unitDealsDamage(Unit* damaging, Unit* damaged, const float & damage) ;
    void unitTakesDamage(Unit* damaged, Unit* damager, const float & damage);
    void unitKills(Unit* killer, Unit* dead);
    void unitDies(Unit* dead, Unit* killer);
    void unitEntersArea(Unit* unit, glm::vec4 area);
    void unitLeavesArea(Unit* unit, glm::vec4 area);
    
    // actions
    void unitCreate(Unit* unitType, unsigned ownerId, glm::vec2 position);
    void unitMove(Unit* u, glm::vec2 position);
    void unitKill(Unit* u);
    
    // fields
    std::vector<Script*> m_scriptList;
    std::queue<ScriptInstance*> m_scriptInstanceQueue;
    
    unsigned int m_currentPlayerId;
    unsigned int m_playerRelation[PLAYER_COUNT][PLAYER_COUNT];
    float m_tickDuration;
    Player* m_players[PLAYER_COUNT];
    std::list<Unit*> m_unitType;
    std::list<Missile*> m_missileType;
    std::list<Entity*> m_entities; // all entites (missiles + units)
    std::list<Missile*> m_missiles; // all missiles
    std::list<Unit*> m_unitsAll; // all units + buildings
    std::list<Unit*> m_unitsAlive; // all units that are alive (units + buildings)
    std::list<Unit*> m_unitsDead; // all units that are dead (units + buildings)
    std::list<Unit*> m_buildings; // all units that are buildings (dead + alive)
    std::list<Unit*> m_unitsPlayer[PLAYER_COUNT]; // units separated by player owner
    //Upgrade m_techTree[8];
    unsigned char** m_collisionMap;
    float m_gameTime;
    float m_dayTime;
};

#endif /* GAMEENIGINE_H */

