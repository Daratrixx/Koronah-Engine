/* 
 * File:   Unit.h
 * Author: ANTOINE
 *
 * Created on 27 juin 2016, 19:58
 */
#pragma once

#ifndef UNIT_H
#define	UNIT_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef ENTITY_H
#include "Entity.h"
#endif

#ifndef GEOMETRY_H
#include "Geometry.h"
#endif

#include <list>

class Unit : public Entity {
public:
    Unit();
    Unit(Unit *u);
    virtual ~Unit();
    virtual bool writeInFile(std::ofstream & fout);
    virtual bool readFromFile(std::ifstream & fin);
    
    void kill();
    
    virtual void push(const float & x, const float & y);
    // global
    virtual bool isAlive() const;
    virtual bool isDead() const;
    virtual bool isUnit() const;
    virtual bool isBuilding() const;
    virtual bool isBuildingDone() const;
    virtual bool isTrainingDone() const;
    
    std::string getName() const;
    void setName(const std::string & name);
    UShort getOwnerId() const;
    void setOwnerId(const UShort & id);
    
    UInt getLevel() const;
    void setLevel(const UInt & level);
    void addLevel(const UInt & level);

    UInt getExperience() const;
    void setExperience(const UInt & experience);
    void addExperience(const UInt & experience);

    std::string m_name;
    UShort m_ownerId;
    float m_constructionTime; // both for building construction and unit training total duration

    UInt m_level;
    UInt m_experience;

    bool m_isAlive;
    bool m_isBuilding;
    UShort m_behavior;

    std::list<Spell*> m_speelList;
    
    // orders
    void orderStop();
    void orderHold();
    void orderMove(const glm::vec2 & dest);
    void orderRally(const glm::vec2 & dest);
    void orderRally(Unit* target);
    void orderFollow(Unit* target);
    void orderPatrol(const glm::vec2 & dest);
    void orderAttackMove(const glm::vec2 & dest);
    void orderAttack(Unit* target);
    void orderBuild(Unit* buildingType, const glm::vec2 & destination);
    void orderCancelBuild();
    void orderTrain(Unit* unitType);
    void orderCancelTrain();
    
    glm::vec2 getDestination();
    void setDestination(const glm::vec2 & destination);
    
    glm::vec2 m_destination;

    // units
    Unit* m_constructingBuilding;
    glm::vec2 m_buildDestination;
    
    // building
    void setBuildingSize(const float & x, const float & y);
    void setBuildingSize(const glm::vec2 & size);
    glm::vec2 getBuildingSize() const;
    glm::vec2 m_buildingSize;
    
    void build(const float & time);
    float m_buildingProgress;
    void train(const float & time);
    float getDamage();
    Unit* m_trainingUnit;
    float m_trainingProgress;
    glm::vec2 m_rallyDestination;
    Unit* m_rallyTarget;
    
    // resources
    int m_costEnergy;
    int m_costMaterials;
    int m_costSupply;
    
    
    // fight
    float m_healthMax;
    float m_healthRegenerationRate;
    float m_healthPercent;
    
    void damage(const float & damage);
    void heal(const float & heal);

    float m_attackDamage;
    float m_attackRange;
    float m_attackReloadTime;
    float m_attackCooldown;
    float m_attackAggressionRange;
    
    Entity* m_missileType;
    
    int m_unitId;
};

#endif	/* UNIT_H */

