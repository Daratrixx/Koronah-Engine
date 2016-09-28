/* 
 * File:   Item.h
 * Author: ANTOINE
 *
 * Created on 19 septembre 2016, 23:12
 */

#ifndef ITEM_H
#define	ITEM_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Item {
public:
    Item();
    ~Item();
protected:
    std::string m_name;
    int m_goldValue;
    int m_weight;
    bool m_sellable;
};

class Consumable : public Item {
public:
    Consumable();
    ~Consumable();
protected:
    
};

class Equipement : public Item {
public:
    Equipement();
    ~Equipement();
protected:
    unsigned int m_equipementMaterial; // cloth, leather, steel...
    unsigned int m_equipementWeight; // cloth, light, heavy
    unsigned int m_equipementSlot;
    bool m_isArmor;
    bool m_isWeapon;
    
    void* m_upgrade;
};

class Armor : public Equipement {
public:
    Armor();
    ~Armor();
protected:
    unsigned int m_armorSlot;
};

class Weapon : public Equipement {
public:
    Weapon();
    ~Weapon();
protected:
    bool m_twoHanded;
    bool m_left;
    bool m_right;
};

#endif	/* ITEM_H */

