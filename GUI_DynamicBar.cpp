
#include "GUI.h"

GUI_DynamicBar::GUI_DynamicBar() : GUI_Bar() {
    m_getBarPercent = null;
    m_getBarColor = null;
    m_source = null;
}

GUI_DynamicBar::~GUI_DynamicBar() {
}

void GUI_DynamicBar::render(GraphicEngine* Graphic) {
    if (m_visible) {
        if(getBarPercent()!=m_barPercent || getBarColor(m_mode) != m_barColor[m_mode])
            m_needLoadBar = true;
        glDisable(GL_DEPTH_TEST);
        renderGUI(Graphic);
        renderBar(Graphic);
        renderChildren(Graphic);
        glEnable(GL_DEPTH_TEST);
    }
}

void GUI_DynamicBar::setGetBarPercent(float(*getBarPercent)(void*, float)) {
    m_getBarPercent = getBarPercent;
}

void GUI_DynamicBar::setGetBarColor(glm::vec3(*getBarColor)(void*, float)) {
    m_getBarColor = getBarColor;
}

void GUI_DynamicBar::setSource(void* source) {
    m_source = source;
}

float GUI_DynamicBar::getBarPercent() {
    if (m_source != null && m_getBarPercent != null) {
        return m_getBarPercent(m_source, m_time);
    }
    return m_barPercent;
}

glm::vec3 GUI_DynamicBar::getBarColor() {
    if (m_source != null && m_getBarColor != null) {
        return m_getBarColor(m_source, m_time);
    }
    return m_barColor[m_mode];
}

glm::vec3 GUI_DynamicBar::getBarColor(unsigned int mode) {
    if (m_source != null && m_getBarColor != null) {
        return m_getBarColor(m_source, m_time);
    }
    return m_barColor[mode];
}


