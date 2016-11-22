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

std::string GDL_getHPMax(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->m_maxHealth);
}

std::string GDL_getHPCurrent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->m_maxHealth * u->m_percentHealth);
}

std::string GDL_getHPPercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return toString(u->m_percentHealth, 2);
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

// dynamic label getTextColor function


// dynamic bar getBarPercent function
float GDB_getHealthPercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return (u->m_maxHealth);
}
float GDB_getExperiencePercent(void* source, float time) {
    Unit* u = (Unit*) source;
    return ((float)u->getExperience()) / ((float)u->getLevel()*50);
}