
#include "Unit.h"

Unit::Unit() : Entity() {
    m_attackDamage = 10;
    m_attackRange = 20;
    m_attackAgressionRange = 50;
    m_attackReloadTime = .2f;
    m_attackCooldown = 0;
    m_behavior = UNIT_BEHAVIOR_IDLE;
    m_buildDestination = glm::vec2(0, 0);
    m_buildingProgress = 0;
    m_buildingSize = glm::vec2(0, 0);
    m_constructingBuilding = null;
    m_constructionTime = 1;
    m_doCollision = true;
    m_experience = 0;
    m_isAlive = true;
    m_isBuilding = false;
    m_level = 0;
    m_maxHealth = 100;
    m_missileType = null;
    m_name = "No name";
    m_percentHealth = 1;
    m_rallyDestination = glm::vec2(0, 0);
    m_rallyTarget = null;
    m_trainingProgress = 0;
    m_trainingUnit = null;
}

Unit::Unit(Unit* u) : Entity(u) {
    m_attackAgressionRange = u->m_attackAgressionRange;
    m_attackCooldown = u->m_attackCooldown;
    m_attackDamage = u->m_attackDamage;
    m_attackRange = u->m_attackRange;
    m_attackReloadTime = u->m_attackReloadTime;
    m_behavior = UNIT_BEHAVIOR_IDLE;
    m_buildDestination = glm::vec2(0, 0);
    m_buildingSize = u->m_buildingSize;
    m_buildingProgress = 0;
    m_constructingBuilding = null;
    m_constructionTime = u->m_constructionTime;
    m_doCollision = u->m_doCollision;
    m_isAlive = true;
    m_isBuilding = u->m_isBuilding;
    m_level = u->m_level;
    m_maxHealth = u->m_maxHealth;
    m_missileType = u->m_missileType;
    m_name = u->m_name;
    m_percentHealth = 1;
    m_rallyDestination = glm::vec2(0, 0);
    m_rallyTarget = null;
    m_trainingProgress = 0;
    m_trainingUnit = null;
    std::cout << "unit cloned " << m_name << std::endl;
}

Unit::~Unit() {
    kill();
    std::cout << "Deleted Unit with ID " << m_objectId << std::endl;
}

void Unit::kill() {
    orderStop();
}

void Unit::push(float x, float y) {
    m_position.x += x;
    m_position.y += y;
    if (m_behavior == UNIT_BEHAVIOR_IDLE) {
        m_lastCollisionHit = 0;
        m_behavior = UNIT_BEHAVIOR_PUSHED;
    }
}

void Unit::orderStop() {
    if (m_behavior == UNIT_BEHAVIOR_BUILDING)
        orderCancelBuild();
    else if (m_behavior == UNIT_BEHAVIOR_TRAINING)
        orderCancelTrain();
    else if (m_behavior != UNIT_BEHAVIOR_IDLE) {
        m_target = null;
        m_trainingUnit = null;
        m_constructingBuilding = null;
        m_destination = m_position;
    }
    m_behavior = UNIT_BEHAVIOR_IDLE;
}

void Unit::orderHold() {
    m_target = null;
    m_destination = m_position;
    m_behavior = UNIT_BEHAVIOR_HOLD;
}

void Unit::orderMove(glm::vec2 dest) {
    m_target = null;
    m_destination = dest;
    m_behavior = UNIT_BEHAVIOR_MOVING;
}

void Unit::orderRally(glm::vec2 dest) {
    m_rallyDestination = dest;
    m_rallyTarget = null;
}

void Unit::orderRally(Unit* target) {
    m_rallyTarget = target;
}

void Unit::orderFollow(Unit* target) {
    m_target = target;
    m_behavior = UNIT_BEHAVIOR_FOLLOWING;
}

void Unit::orderPatrol(glm::vec2 dest) {
    m_destination = dest;
    m_target = null;
    m_behavior = UNIT_BEHAVIOR_PATROLING;
}

void Unit::orderAttackMove(glm::vec2 dest) {
    m_destination = dest;
    m_target = null;
    m_behavior = UNIT_BEHAVIOR_ATTACK_MOVING;
}

void Unit::orderAttack(Unit* target) {
    m_target = target;
    m_behavior = UNIT_BEHAVIOR_ATTACKING;
}

void Unit::orderBuild(Unit* buildingType, glm::vec2 destination) {
    if (m_behavior == UNIT_BEHAVIOR_BUILDING)
        orderCancelBuild();
    m_constructingBuilding = new Unit(buildingType);
    m_buildDestination = destination;
    m_behavior = UNIT_BEHAVIOR_BUILDING;
}

void Unit::orderCancelBuild() {
    if (m_constructingBuilding != null) {
        delete m_constructingBuilding;
    }
    orderStop();
}

void Unit::orderTrain(Unit* unitType) {
    //if (m_behavior == UNIT_BEHAVIOR_TRAINING)
    //    orderCancelTrain();
    m_trainingUnit = new Unit(unitType);
    m_trainingProgress = 0;
    m_behavior = UNIT_BEHAVIOR_TRAINING;
}

void Unit::orderCancelTrain() {
    if (m_trainingUnit != null) {
        delete m_trainingUnit;
    }
    orderStop();
}

void Unit::damage(float damage) {
    if (m_isAlive) {
        m_percentHealth -= damage / m_maxHealth;
        if (m_percentHealth <= 0) {
            m_percentHealth = 0;
            m_isAlive = false;
        }
    }
}

void Unit::heal(float heal) {
    if (m_isAlive) {
        if (m_percentHealth < 1)
            m_percentHealth += heal / m_maxHealth;
        if (m_percentHealth > 1)
            m_percentHealth = 1;
    }
}

bool Unit::isAlive()const {
    return m_isAlive;
}

bool Unit::isDead() const {
    return !m_isAlive;
}

bool Unit::isUnit()const {
    return true;
}

bool Unit::isBuilding() const {
    return m_isBuilding;
}

bool Unit::isBuildingDone() const {
    return m_buildingProgress >= 1;
}

bool Unit::isTrainingDone() const {
    return m_trainingProgress >= 1;
}

void Unit::setName(std::string name) {
    m_name = name;
}

std::string Unit::getName() const {
    return m_name;
}

void Unit::setOwnerId(unsigned int id) {
    m_ownerId = id;
}

unsigned int Unit::getOwnerId() {
    return m_ownerId;
}

glm::vec2 Unit::getDestination() {
    return m_destination;
}

void Unit::setDestination(glm::vec2 destination) {
    m_destination = destination;
}

void Unit::setBuildingSize(float x, float y) {
    m_buildingSize.x = x;
    m_buildingSize.y = y;
}

void Unit::setBuildingSize(glm::vec2 size) {
    m_buildingSize = size;
}

glm::vec2 Unit::getBuildingSize() const {
    return m_buildingSize;
}

void Unit::build(float time) {
    m_buildingProgress += time / m_constructionTime;
}

void Unit::train(float time) {
    m_trainingProgress += time / m_trainingUnit->m_constructionTime;
}

int Unit::getLevel() const {
    return m_level;
}

void Unit::setLevel(int level) {
    m_level = level;
}

void Unit::addLevel(int level) {
    m_level += level;
}

int Unit::getExperience() const {
    return m_experience;
}

void Unit::setExperience(int experience) {
    m_experience = experience;
}

void Unit::addExperience(int experience) {
    m_experience += experience;
    if (m_experience > m_level * 50) {
        m_experience = 0;
        m_level += 1;
    }
}
