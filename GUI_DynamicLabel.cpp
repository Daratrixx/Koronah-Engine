#include "GUI.h"
#include "GameObject.h"
#include "Unit.h"
#include "String.h"
#include "Time.h"

GUI_DynamicLabel::GUI_DynamicLabel() : GUI_Label() {
    m_getText = null;
    m_getTextColor = null;
    m_source = null;
}

GUI_DynamicLabel::~GUI_DynamicLabel() {

}

void GUI_DynamicLabel::setGetText(std::string(*getText)(void*, float)) {
    m_getText = getText;
}

void GUI_DynamicLabel::setGetTextColor(glm::vec3(*getTextColor)(void*, float)) {
    m_getTextColor = getTextColor;
}

void GUI_DynamicLabel::setSource(void* source) {
    m_source = source;
}

std::string GUI_DynamicLabel::getText() const {
    if (m_getText != null && m_source != null)
        return m_getText(m_source, 0);
    else
        return m_text[m_mode];
}

std::string GUI_DynamicLabel::getText(unsigned int mode) const {
    if (m_getText != null && m_source != null)
        return m_getText(m_source, 0);
    else
        return m_text[mode];
}

glm::vec3 GUI_DynamicLabel::getTextColor() const {
    if (m_getTextColor != null && m_source != null) {
        return m_getTextColor(m_source,m_time);
    } else {
        float blink = std::cos(m_time * m_blinkSpeed[m_mode]) / 4 + 0.75;
        return m_textColor[m_mode] * blink;
    }
}

glm::vec3 GUI_DynamicLabel::getTextColor(unsigned int mode) const {
    if (m_getTextColor != null && m_source != null) {
        return m_getTextColor(m_source,m_time);
    } else {
        float blink = std::cos(m_time * m_blinkSpeed[mode]) / 4 + 0.75;
        return m_textColor[mode] * blink;
    }
}

// dynamic label getText function

std::string GDL_getPosX(void* source, float time) {
    GameObject* go = (GameObject*) source;
    return toString(go->getPositionX(), 2);
}

std::string GDL_getPosY(void* source, float time) {
    GameObject* go = (GameObject*) source;
    return toString(go->getPositionY(), 2);
}

std::string GDL_getPosZ(void* source, float time) {
    GameObject* go = (GameObject*) source;
    return toString(go->getPositionZ(), 2);
}

std::string GDL_getHPMax(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getMaxHealth());
}

std::string GDL_getHPCurrent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentHealth());
}

std::string GDL_getHPPercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentHealth()/u->getMaxHealth(), 2);
}

std::string GDL_getHealth(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentHealth()) + " / " + toString(u->getMaxHealth());
}

std::string GDL_getENMax(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getMaxConcentration());
}

std::string GDL_getENCurrent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentConcentration());
}

std::string GDL_getENPercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentConcentration()/u->getMaxConcentration(), 2);
}

std::string GDL_getConcentration(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->getCurrentConcentration(), 0) + " / " + toString(u->getMaxConcentration(), 0);
}
std::string GDL_getFPS(void* source, float time) {
    TimeEngine* te = (TimeEngine*) source;
    return "FPS " + toString(te->getFPS());
}
std::string GDL_getName(void* source, float time) {
    Unit* u = (Unit*) source;
    return u->getName();
}
std::string GDL_getLevel(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Lvl " + toString(u->getLevel());
}
std::string GDL_getBaseConstitution(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Const. " + toString(u->getBase(UNIT_CONSTITUTION));
}
std::string GDL_getBaseMental(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Mental " + toString(u->getBase(UNIT_MENTAL));
}
std::string GDL_getBaseDexterity(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Dext. " + toString(u->getBase(UNIT_DEXTERITY));
}
std::string GDL_getBaseFate(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Fate " + toString(u->getBase(UNIT_FATE));
}
std::string GDL_getBaseSocial(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Social " + toString(u->getBase(UNIT_SOCIAL));
}
std::string GDL_getTotalConstitution(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Const. " + toString(u->getTotal(UNIT_CONSTITUTION)) + " " + toString(u->getGrowth(UNIT_CONSTITUTION), 2);
}
std::string GDL_getTotalMental(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Mental " + toString(u->getTotal(UNIT_MENTAL)) + " " + toString(u->getGrowth(UNIT_MENTAL), 2);
}
std::string GDL_getTotalDexterity(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Dext. " + toString(u->getTotal(UNIT_DEXTERITY)) + " " + toString(u->getGrowth(UNIT_DEXTERITY), 2);
}
std::string GDL_getTotalFate(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Fate " + toString(u->getTotal(UNIT_FATE)) + " " + toString(u->getGrowth(UNIT_FATE), 2);
}
std::string GDL_getTotalSocial(void* source, float time) {
    Unit* u = (Unit*) source;
    return "Social " + toString(u->getTotal(UNIT_SOCIAL)) + " " + toString(u->getGrowth(UNIT_SOCIAL), 2);
}

// dynamic label getTextColor function

glm::vec3 GDL_getHPColor(void* source, float time) {
    Unit* u = (Unit*) source;
    float percent = ((float)u->getCurrentHealth())/u->getMaxHealth();
    if (percent < 0.3f) {
        float flux = std::cos(time * 9) * 0.25 + 0.75;
        return glm::vec3(1, 0, 0) * flux;
    }
    if (percent < 0.7f) {
        float flux = std::cos(time * 3) * 0.15 + 0.85;
        return glm::vec3(1, 1, 0) * flux;
    }
    return glm::vec3(0, 1, 0);
}

glm::vec3 GDL_getENColor(void* source, float time) {
    //Unit* u = (Unit*) source;
    return glm::vec3(0.25f, 0, 0.75f);
}


// dynamic bar getBarPercent function
float GDL_getExperiencePercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return ((float)u->getExperience()) / ((float)u->getLevel()*50);
}