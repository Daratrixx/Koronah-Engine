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
    
    void kill();
    
    virtual void push(float x, float y);
    // global
    virtual bool isAlive() const;
    virtual bool isDead() const;
    virtual bool isUnit() const;
    virtual bool isBuilding() const;
    virtual bool isBuildingDone() const;
    virtual bool isTrainingDone() const;
    
    std::string getName() const;
    void setName(std::string name);
    unsigned int getOwnerId();
    void setOwnerId(unsigned int id);
    
    int getLevel() const;
    void setLevel(int level);
    void addLevel(int level);

    int getExperience() const;
    void setExperience(int experience);
    void addExperience(int experience);

    std::string m_name;
    unsigned int m_ownerId;
    float m_constructionTime; // both for building construction and unit training total duration

    unsigned int m_level;
    unsigned int m_experience;

    bool m_isAlive;
    bool m_isBuilding;
    unsigned int m_behavior;

    std::list<Spell*> m_speelList;
    
    // orders
    void orderStop();
    void orderHold();
    void orderMove(glm::vec2 dest);
    void orderRally(glm::vec2 dest);
    void orderRally(Unit* target);
    void orderFollow(Unit* target);
    void orderPatrol(glm::vec2 dest);
    void orderAttackMove(glm::vec2 dest);
    void orderAttack(Unit* target);
    void orderBuild(Unit* buildingType, glm::vec2 destination);
    void orderCancelBuild();
    void orderTrain(Unit* unitType);
    void orderCancelTrain();
    
    glm::vec2 getDestination();
    void setDestination(glm::vec2 destination);
    
    glm::vec2 m_destination;

    // units
    Unit* m_constructingBuilding;
    glm::vec2 m_buildDestination;
    
    // building
    void setBuildingSize(float x, float y);
    void setBuildingSize(glm::vec2 size);
    glm::vec2 getBuildingSize() const;
    glm::vec2 m_buildingSize;
    
    void build(float time);
    float m_buildingProgress;
    void train(float time);
    Unit* m_trainingUnit;
    float m_trainingProgress;
    glm::vec2 m_rallyDestination;
    Unit* m_rallyTarget;
    
    // fight
    float m_maxHealth;
    float m_percentHealth;
    float m_attackAgressionRange;
    
    void damage(float damage);
    void heal(float heal);

    float m_attackDamage;
    float m_attackRange;
    float m_attackReloadTime;
    float m_attackCooldown;
    
    Entity* m_missileType;
};

#endif	/* UNIT_H */

