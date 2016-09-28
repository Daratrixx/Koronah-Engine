
#include "Unit.h"

Unit* createHuman(std::string name, int level) {
    Unit* u = new Unit();
    u->setName(name);
    u->setLevel(level);
    u->setBase(UNIT_CONSTITUTION, 7);
    u->setBase(UNIT_MENTAL, 7);
    u->setBase(UNIT_DEXTERITY, 7);
    u->setBase(UNIT_FATE, 7);
    u->setBase(UNIT_SOCIAL, 7);
    u->setCurrentHealth(u->getMaxHealth());
    u->setCurrentConcentration(u->getMaxConcentration());
    return u;
}

Unit* createElven(std::string name, int level) {
    Unit* u = new Unit();
    u->setName(name);
    u->setLevel(level);
    u->setBase(UNIT_CONSTITUTION, 6);
    u->setBase(UNIT_MENTAL, 8);
    u->setBase(UNIT_DEXTERITY, 8);
    u->setBase(UNIT_FATE, 7);
    u->setBase(UNIT_SOCIAL, 6);
    u->setCurrentHealth(u->getMaxHealth());
    u->setCurrentConcentration(u->getMaxConcentration());
    return u;
}

Unit* createDwarf(std::string name, int level) {
    Unit* u = new Unit();
    u->setName(name);
    u->setLevel(level);
    u->setBase(UNIT_CONSTITUTION, 8);
    u->setBase(UNIT_MENTAL, 6);
    u->setBase(UNIT_DEXTERITY, 7);
    u->setBase(UNIT_FATE, 8);
    u->setBase(UNIT_SOCIAL, 6);
    u->setCurrentHealth(u->getMaxHealth());
    u->setCurrentConcentration(u->getMaxConcentration());
    return u;
}

Unit* createOrc(std::string name, int level) {
    Unit* u = new Unit();
    u->setName(name);
    u->setLevel(level);
    u->setBase(UNIT_CONSTITUTION, 9);
    u->setBase(UNIT_MENTAL, 6);
    u->setBase(UNIT_DEXTERITY, 7);
    u->setBase(UNIT_FATE, 7);
    u->setBase(UNIT_SOCIAL, 6);
    u->setCurrentHealth(u->getMaxHealth());
    u->setCurrentConcentration(u->getMaxConcentration());
    return u;
}

Unit* createDrakkarim(std::string name, int level) {
    Unit* u = new Unit();
    u->setName(name);
    u->setLevel(level);
    u->setBase(UNIT_CONSTITUTION, 8);
    u->setBase(UNIT_MENTAL, 9);
    u->setBase(UNIT_DEXTERITY, 7);
    u->setBase(UNIT_FATE, 5);
    u->setBase(UNIT_SOCIAL, 6);
    u->setCurrentHealth(u->getMaxHealth());
    u->setCurrentConcentration(u->getMaxConcentration());
    return u;
}

Unit::Unit() : Entity() {

    m_name = "No name";
    m_movingSpeed = 1;
    for (unsigned int i = 0; i < 5; i++) {
        m_base[i] = 0;
        m_growth[i] = 0;
        m_bonus[i] = 0;
        m_total[i] = 0;
    }

    //ressources
    m_currentHealth = 0;
    m_currentConcentration = 0;
    m_currentFavor = 0;

    m_level = 0;
    m_experience = 0;
    m_bonusPoint = 0;

    m_alterationCold = 0;
    m_alterationBurn = 0;
    m_alterationExaust = 0;
    m_alterationPoison = 0;
    m_alterationBleending = 0;
    for (unsigned int i = 0; i < 6; i++)
        m_armor[i] = null;
    for (unsigned int i = 0; i < 2; i++)
        m_weapon[i] = null;
}

Unit::~Unit() {
    std::cout << "Deleted Unit with ID " << m_objectId << std::endl;
}

void Unit::moveForward(float speed) {
    glm::vec3 direction = getForwardVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveBack(float speed) {
    glm::vec3 direction = getBackVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveRight(float speed) {
    glm::vec3 direction = getRightVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveLeft(float speed) {
    glm::vec3 direction = getLeftVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveUp(float speed) {
    glm::vec3 direction = getUpVector(m_angle);
    addPosition(direction * speed);
}

void Unit::moveDown(float speed) {
    glm::vec3 direction = getDownVector(m_angle);
    addPosition(direction * speed);
}

void Unit::damage(float damage) {
    m_currentHealth -= damage;
    if (m_currentHealth < 0)
        m_currentHealth = 0;
}

void Unit::heal(float heal) {
    m_currentHealth += heal;
    if (m_currentHealth > getMaxHealth())
        m_currentHealth = getMaxHealth();
}

void Unit::consume(float consume) {
    m_currentConcentration -= consume;
    if (m_currentConcentration < 0)
        m_currentConcentration = 0;
}

void Unit::recover(float recover) {
    m_currentConcentration += recover;
    if (m_currentConcentration > getMaxConcentration())
        m_currentConcentration = getMaxConcentration();
}

void Unit::setName(std::string name) {
    m_name = name;
}

std::string Unit::getName() const {
    return m_name;
}

void Unit::update(float time, std::vector<GameObject*> objects) {
    m_lastCollisionHit += time;
    if (m_lastCollisionHit > 1.5f && m_behavior == UNIT_BEHAVIOR_PUSHED)
        m_behavior = UNIT_BEHAVIOR_MOVING;
    doMovement(time);
    doCollision(objects);
}

void Unit::doMovement(float time) {
    if (m_behavior == UNIT_BEHAVIOR_MOVING) {
        float distance, speed;
        glm::vec3 direction = m_destination - m_position;
        distance = glm::length(direction);
        speed = m_movingSpeed * time;
        if (distance - m_radius > speed) {
            m_position += glm::normalize(direction) * speed;
        } else {
            m_destination = m_position;
            m_behavior = UNIT_BEHAVIOR_IDLE;
        }
    }
}

void Unit::doCollision(std::vector<GameObject*> objects) {
    glm::vec2 uPosition(m_position.x, m_position.z);
    for (unsigned int i = 0; i < objects.size(); i++) {
        Entity* o = (Entity*) objects[i];
        if (o != this) {
            glm::vec2 oPosition(o->getPositionX(), o->getPositionZ());
            float radius = m_radius + o->getRadius();

            glm::vec2 direction = oPosition - uPosition;
            float distance = glm::length(direction);
            if (distance < radius) {
                direction = direction * (radius - distance) / radius;
                if(m_behavior == UNIT_BEHAVIOR_HOLD && o->getBehavior() == UNIT_BEHAVIOR_HOLD) {
                    push(-direction.x, -direction.y);
                    o->push(direction.x, direction.y);
                    
                } else {
                if (m_behavior != UNIT_BEHAVIOR_HOLD)
                    push(-direction.x, -direction.y);
                if (o->getBehavior() != UNIT_BEHAVIOR_HOLD)
                    o->push(direction.x, direction.y);
                }
            }
        }
    }
}

void Unit::setDestination(glm::vec3 destination) {
    m_destination = destination;
    m_behavior = UNIT_BEHAVIOR_MOVING;
}

void Unit::setMovingSpeed(float movingSpeed) {
    m_movingSpeed = movingSpeed;
}

int Unit::getBase(unsigned int type) const {
    return m_base[type];
}

float Unit::getGrowth(unsigned int type) const {
    return m_growth[type];
}

int Unit::getBonus(unsigned int type) const {
    return m_bonus[type];
}

int Unit::getTotal(unsigned int type) const {
    return m_total[type];
}

void Unit::setBase(unsigned int type, int value) {
    m_total[type] += value - m_base[type];
    m_base[type] = value;
}

void Unit::setGrowth(unsigned int type, float value) {
    m_total[type] += value - m_growth[type];
    m_growth[type] = value;
}

void Unit::setBonus(unsigned int type, int value) {
    m_total[type] += value - m_bonus[type];
    m_bonus[type] = value;
}

void Unit::addBase(unsigned int type, int value) {
    m_total[type] += value;
    m_base[type] += value;
}

void Unit::addGrowth(unsigned int type, float value) {
    if (m_growth[type] <= m_base[type]) {
        m_total[type] -= (int) m_growth[type];
        m_growth[type] += value;
        m_total[type] += (int) m_growth[type];
    }
}

void Unit::addBonus(unsigned int type, int value) {
    m_total[type] += value;
    m_bonus[type] += value;
}
// ressources

int Unit::getCurrentHealth() const {
    return m_currentHealth;
}

int Unit::getCurrentConcentration() const {
    return m_currentConcentration;
}

int Unit::getCurrentFavor() const {
    return m_currentFavor;
}

void Unit::setCurrentHealth(int health) {
    m_currentHealth = health;
}

void Unit::setCurrentConcentration(int concentration) {
    m_currentConcentration = concentration;
}

void Unit::setCurrentFavor(int favor) {
    m_currentFavor = favor;
}

int Unit::getMaxHealth() const {
    return getTotal(UNIT_CONSTITUTION) * 2 + m_level;
}

int Unit::getMaxConcentration() const {
    return getTotal(UNIT_MENTAL) + m_level;
}

int Unit::getMaxFavor() const {
    return getTotal(UNIT_FATE) + m_level;
}

void Unit::addHealth(int health) {
    m_currentHealth += health;
    int max = getMaxHealth();
    if (m_currentHealth > max)
        m_currentHealth = max;
}

void Unit::addConcentration(int concentration) {
    m_currentConcentration += concentration;
    int max = getMaxConcentration();
    if (m_currentConcentration > max)
        m_currentConcentration = max;
}

void Unit::addFavor(int favor) {
    m_currentFavor += favor;
    int max = getMaxFavor();
    if (m_currentFavor > max)
        m_currentFavor = max;
}

void Unit::removeHealth(int health) {
    m_currentHealth -= health;
    if (m_currentHealth < 0)
        m_currentHealth = 0;
}

void Unit::removeConcentration(int concentration) {
    m_currentConcentration -= concentration;
    if (m_currentConcentration < 0)
        m_currentConcentration = 0;
}

void Unit::removeFavor(int favor) {
    m_currentFavor -= favor;
    if (m_currentFavor < 0)
        m_currentFavor = 0;
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
    for (unsigned int i = 0; i < 5; i++) {
        addGrowth(i, ((float) experience) / 500.f);
    }
}