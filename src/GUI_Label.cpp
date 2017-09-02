
#include "GUI.h"

GUI_Label::GUI_Label() : GUI() {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_text[i] = "";
        m_textColor[i] = glm::vec3(1, 1, 1);
        m_fontSize[i] = 0.5f;
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
        std::string text = getText(m_mode);
        glm::vec2 lineSize = Graphic->getLineSize(text, m_fontSize[m_mode]);
        glm::vec2 pos = getPosition(m_mode);
        glm::vec2 size = getSize(m_mode);
        pos.y = pos.y + size.y / 2 - lineSize.y / 2;
        if (m_textAlignement[m_mode] == TEXT_ALIGN_RIGHT) {
            pos.x = pos.x + size.x - lineSize.x;
        } else if (m_textAlignement[m_mode] == TEXT_ALIGN_CENTER) {
            pos.x = pos.x + (size.x - lineSize.x) / 2;
        }
        //Graphic->writeLine(text, pos.x, pos.y, m_fontSize[m_mode], getTextColor(m_mode));
        writeLine(text, pos.x, pos.y, m_fontSize[m_mode], getTextColor(m_mode));
    }
}

std::string GUI_Label::getText() const {
    return m_text[m_mode];
}

std::string GUI_Label::getText(const UShort & mode) const {
    return m_text[mode];
}

glm::vec3 GUI_Label::getTextColor() const {
    if (m_blinkText[m_mode]) {
        float blink = std::cos(m_time * m_blinkSpeed[m_mode]) / 4 + 0.75;
        return m_textColor[m_mode] * blink;
    }
    return m_textColor[m_mode];
}

glm::vec3 GUI_Label::getTextColor(const UShort & mode) const {
    if (m_blinkText[mode]) {
        float blink = std::cos(m_time * m_blinkSpeed[mode]) / 4 + 0.75;
        return m_textColor[mode] * blink;
    }
    return m_textColor[m_mode];
}

UShort GUI_Label::getTextAlignement() const {
    return m_textAlignement[m_mode];
}

UShort GUI_Label::getTextAlignement(const UShort & mode) const {
    return m_textAlignement[mode];
}

float GUI_Label::getFontSize() const {
    return m_fontSize[m_mode];
}

float GUI_Label::getFontSize(const UShort & mode) const {
    return m_fontSize[mode];
}

float GUI_Label::getBlinkSpeed() const {
    return m_blinkSpeed[m_mode];
}

float GUI_Label::getBlinkSpeed(const UShort & mode) const {
    return m_blinkSpeed[mode];
}

bool GUI_Label::getBlinkText() const {
    return m_blinkText[m_mode];
}

bool GUI_Label::getBlinkText(const UShort & mode) const {
    return m_blinkText[mode];
}

bool GUI_Label::getDisplayText() const {
    return m_displayText;
}

void GUI_Label::setText(const std::string & text) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_text[i] = text;
    }
}

void GUI_Label::setText(const std::string & text, const UShort & mode) {
    m_text[mode] = text;
}

void GUI_Label::setTextAlignement(const UShort & alignement) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_textAlignement[i] = alignement;
    }
}

void GUI_Label::setTextAlignement(const UShort & alignement, const UShort & mode) {
    m_textAlignement[mode] = alignement;
}

void GUI_Label::setTextColor(const glm::vec3 & color) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_textColor[i] = color;
    }
}

void GUI_Label::setTextColor(const glm::vec3 & color, const UShort & mode) {
    m_textColor[mode] = color;
}

void GUI_Label::setTextColor(const float & r, const float & g, const float & b) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_textColor[i].x = r;
        m_textColor[i].y = g;
        m_textColor[i].z = b;
    }
}

void GUI_Label::setTextColor(const float & r, const float & g, const float & b, const UShort & mode) {
    m_textColor[mode].x = r;
    m_textColor[mode].y = g;
    m_textColor[mode].z = b;
}

void GUI_Label::setFontSize(const float & size) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_fontSize[i] = size;
    }
}

void GUI_Label::setFontSize(const float & size, const UShort & mode) {
    m_fontSize[mode] = size;
}

void GUI_Label::setBlinkSpeed(const float & speed) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_blinkSpeed[i] = speed;
    }
}

void GUI_Label::setBlinkSpeed(const float & speed, const UShort & mode) {
    m_blinkSpeed[mode] = speed;
}

void GUI_Label::setBlinkText(const bool & blink) {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_blinkText[i] = blink;
    }
}

void GUI_Label::setBlinkText(const bool & blink, const UShort & mode) {
    m_blinkText[mode] = blink;
}

void GUI_Label::setDisplayText(const bool & display) {
    m_displayText = display;
}

