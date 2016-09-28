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

#ifndef ITEM_H
#include "Item.h"
#endif

class Unit : public Entity {
public:
    Unit();
    virtual ~Unit();

    void moveForward(float speed);
    void moveBack(float speed);
    void moveRight(float speed);
    void moveLeft(float speed);
    void moveUp(float speed);
    void moveDown(float speed);
    
    void damage(float damage);
    void heal(float heal);
    
    void consume(float consume);
    void recover(float recover);
    
    void setName(std::string name);
    std::string getName() const;
    
    // dark star
    virtual void update(float time, std::vector<GameObject*> objects);
    void doMovement(float time);
    void doCollision(std::vector<GameObject*> objects);
    void setDestination(glm::vec3 destination);
    void setMovingSpeed(float movingSpeed);
    
    // stats
    int getBase(unsigned int type) const;
    float getGrowth(unsigned int type) const;
    int getBonus(unsigned int type) const;
    int getTotal(unsigned int type) const;
    void setBase(unsigned int type, int value);
    void setGrowth(unsigned int type, float value);
    void setBonus(unsigned int type, int value);
    void addBase(unsigned int type, int value);
    void addGrowth(unsigned int type, float value);
    void addBonus(unsigned int type, int value);
    // ressources
    int getMaxHealth() const;
    int getMaxConcentration() const;
    int getMaxFavor() const;
    int getCurrentHealth() const;
    int getCurrentConcentration() const;
    int getCurrentFavor() const;
    void setCurrentHealth(int health);
    void setCurrentConcentration(int concentration);
    void setCurrentFavor(int favor);
    void addHealth(int health);
    void addConcentration(int concentration);
    void addFavor(int favor);
    void removeHealth(int health);
    void removeConcentration(int concentration);
    void removeFavor(int favor);
    
    int getLevel() const;
    void setLevel(int level);
    void addLevel(int level);
    
    int getExperience() const;
    void setExperience(int experience);
    void addExperience(int experience);
    
protected:
    std::string m_name;
    
    // dark star
    glm::vec3 m_destination;
    float m_movingSpeed;
    
    // stats
    unsigned int m_base[5];
    float m_growth[5];
    int m_bonus[5];
    int m_total[5];
    //ressources
    int m_currentHealth;
    int m_currentConcentration;
    int m_currentFavor;
    
    unsigned int m_level;
    unsigned int m_experience;
    unsigned int m_bonusPoint;
    
    int m_alterationCold;
    int m_alterationBurn;
    int m_alterationExaust;
    int m_alterationPoison;
    int m_alterationBleending;
    
    Armor* m_armor[6];
    Weapon* m_weapon[2];
};

Unit* createHuman(std::string name, int level);
Unit* createElven(std::string name, int level);
Unit* createDwarf(std::string name, int level);
Unit* createOrc(std::string name, int level);
Unit* createDrakkarim(std::string name, int level);

#endif	/* UNIT_H */

