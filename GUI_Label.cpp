
#include "GUI.h"

GUI_Label::GUI_Label() : GUI() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_text[i] = "Fric = Pognon";
        m_textColor[i] = glm::vec3(1, 1, 1);
        m_fontSize[i] = 1;
        m_blinkSpeed[i] = 0;
        m_blinkText[i] = false;
        m_textAlignement[i] = TEXT_ALIGN_CENTER;
    }
    m_displayText = true;
}

GUI_Label::~GUI_Label() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboGUI[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboGUI[i]);
        if (glIsVertexArray(m_vaoGUI[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoGUI[i]);
    }
    clearChildren();
}

void GUI_Label::render(GraphicEngine* Graphic) {
    if (m_visible) {
        glDisable(GL_DEPTH_TEST);
        renderGUI(Graphic);
        renderLabel(Graphic);
        renderChildren(Graphic);
        glEnable(GL_DEPTH_TEST);
    }
}

void GUI_Label::renderLabel(GraphicEngine* Graphic) const {
    if (m_displayText) {
        glm::vec2 lineSize = Graphic->getLineSize(getText(m_mode), m_fontSize[m_mode]);
        glm::vec2 pos = m_position[m_mode];
        pos.y = pos.y + m_size[m_mode].y / 2 - lineSize.y / 2;
        if (m_textAlignement[m_mode] == TEXT_ALIGN_RIGHT) {
            pos.x = pos.x - lineSize.x;
        } else if (m_textAlignement[m_mode] == TEXT_ALIGN_CENTER) {
            pos.x = pos.x + m_size[m_mode].x / 2 - lineSize.x / 2;
        }
        Graphic->writeLine(getText(m_mode), pos.x, pos.y, m_fontSize[m_mode], getTextColor(m_mode));
    }
}

std::string GUI_Label::getText() const {
    return m_text[m_mode];
}

std::string GUI_Label::getText(unsigned int mode) const {
    return m_text[mode];
}

glm::vec3 GUI_Label::getTextColor() const {
    if (m_blinkText[m_mode]) {
        float blink = std::cos(m_time * m_blinkSpeed[m_mode]) / 4 + 0.75;
        return m_textColor[m_mode] * blink;
    }
    return m_textColor[m_mode];
}

glm::vec3 GUI_Label::getTextColor(unsigned int mode) const {
    if (m_blinkText[mode]) {
        float blink = std::cos(m_time * m_blinkSpeed[mode]) / 4 + 0.75;
        return m_textColor[mode] * blink;
    }
    return m_textColor[m_mode];
}

unsigned int GUI_Label::getTextAlignement() const {
    return m_textAlignement[m_mode];
}

unsigned int GUI_Label::getTextAlignement(unsigned int mode) const {
    return m_textAlignement[mode];
}

float GUI_Label::getFontSize() const {
    return m_fontSize[m_mode];
}

float GUI_Label::getFontSize(unsigned int mode) const {
    return m_fontSize[mode];
}

float GUI_Label::getBlinkSpeed() const {
    return m_blinkSpeed[m_mode];
}

float GUI_Label::getBlinkSpeed(unsigned int mode) const {
    return m_blinkSpeed[mode];
}

bool GUI_Label::getBlinkText() const {
    return m_blinkText[m_mode];
}

bool GUI_Label::getBlinkText(unsigned int mode) const {
    return m_blinkText[mode];
}

bool GUI_Label::getDisplayText() const {
    return m_displayText;
}

void GUI_Label::setText(std::string text) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_text[i] = text;
    }
}

void GUI_Label::setText(std::string text, unsigned int mode) {
    m_text[mode] = text;
}

void GUI_Label::setTextAlignement(unsigned int alignement) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_textAlignement[i] = alignement;
    }
}

void GUI_Label::setTextAlignement(unsigned int alignement, unsigned int mode) {
    m_textAlignement[mode] = alignement;
}

void GUI_Label::setTextColor(glm::vec3 color) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_textColor[i] = color;
    }
}

void GUI_Label::setTextColor(glm::vec3 color, unsigned int mode) {
    m_textColor[mode] = color;
}

void GUI_Label::setTextColor(float r, float g, float b) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_textColor[i].x = r;
        m_textColor[i].y = g;
        m_textColor[i].z = b;
    }
}

void GUI_Label::setTextColor(float r, float g, float b, unsigned int mode) {
    m_textColor[mode].x = r;
    m_textColor[mode].y = g;
    m_textColor[mode].z = b;
}

void GUI_Label::setFontSize(float size) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_fontSize[i] = size;
    }
}

void GUI_Label::setFontSize(float size, unsigned int mode) {
    m_fontSize[mode] = size;
}

void GUI_Label::setBlinkSpeed(float speed) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_blinkSpeed[i] = speed;
    }
}

void GUI_Label::setBlinkSpeed(float speed, unsigned int mode) {
    m_blinkSpeed[mode] = speed;
}

void GUI_Label::setBlinkText(bool blink) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_blinkText[i] = blink;
    }
}

void GUI_Label::setBlinkText(bool blink, unsigned int mode) {
    m_blinkText[mode] = blink;
}

void GUI_Label::setDisplayText(bool display) {
    m_displayText = display;
}

