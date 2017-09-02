#include "GUI.h"

GUI_InputSettingsPannel::GUI_InputSettingsPannel() : GUI() {
    setPosition(250, 25);
    setSize(525, 550);
    setColor(0.25f, 0.25f, 0.25f, 0.5f);
    m_commandLabel[0] = null;
    m_keyButton[0] = null;
    float x = 320, y = 525;
    for (UInt i = 1; i < COMMAND_KEY_COUNT; i++) {
        if (i < COMMAND_GRID_00 || i > COMMAND_GRID_42) {
            initOtherCommand(i, x, y);
        } else initGridCommand(i, x, y);
    }
    m_buttonReset = new GUI_Button();
    m_buttonReset->setText("Default");
    m_buttonReset->setPosition(5, 5);
    m_buttonReset->setSize(50, 30);
    m_buttonReset->setColor(0, 0, 0.25f, 1);
    m_buttonReset->setFontSize(0.8f);
    m_buttonReset->setFontSize(0.8f, GUI_ACTIVE);
    m_buttonReset->setBlinkSpeed(10, GUI_HOVER);
    m_buttonReset->setBlinkText(true, GUI_HOVER);
    m_buttonReset->setTextColor(0, 0.5f, 0.5f);
    m_buttonReset->setTextColor(0, 1, 1, GUI_HOVER);
    m_buttonReset->setPositionType(GUI_POSITION_RELATIVE);
    addChild(m_buttonReset);
}

GUI_InputSettingsPannel::~GUI_InputSettingsPannel() {

}

void GUI_InputSettingsPannel::initOtherCommand(const UInt & i, float & x, float & y) {
    GUI_Label* l;
    GUI_Button* b;
    l = new GUI_Label();
    l->setText("COMMAND");
    l->setPosition(55, y);
    l->setSize(250, 20);
    l->setColor(0, 0, 0, 0.25f);
    l->setFontSize(0.4f);
    l->setTextColor(1, 1, 1);
    l->setTextAlignement(TEXT_ALIGN_RIGHT);
    l->setPositionType(GUI_POSITION_RELATIVE);
    addChild(l);
    m_commandLabel[i] = l;

    b = new GUI_Button();
    b->setText("KEY");
    b->setPosition(x, y);
    b->setSize(200, 20);
    b->setColor(0, 0, 0, 0.5f);
    b->setColor(0, 0, 0, 0.25f, GUI_HOVER);
    b->setFontSize(0.4f);
    b->setTextColor(1, 1, 1);
    b->setTextAlignement(TEXT_ALIGN_CENTER);
    b->setPositionType(GUI_POSITION_RELATIVE);
    addChild(b);
    m_keyButton[i] = b;
    y -= 25;
}

void GUI_InputSettingsPannel::initGridCommand(const UInt & i, float & x, float & y) {
    GUI_Label* l;
    GUI_Button* b;
    if (i == COMMAND_GRID_00) { // first column first row button, plus label
        // label
        l = new GUI_Label();
        l->setText("Grid keys :");
        l->setPosition(55, y);
        l->setSize(250, 20);
        l->setColor(0, 0, 0, 0.25f);
        l->setFontSize(0.4f);
        l->setTextColor(1, 1, 1);
        l->setTextAlignement(TEXT_ALIGN_RIGHT);
        l->setPositionType(GUI_POSITION_RELATIVE);
        addChild(l);
        m_commandLabel[i] = null;
        y -= 20;
        x = 320;
    } else if (i == COMMAND_GRID_01 || i == COMMAND_GRID_02) { // first column last row button
        y -= 40;
        x = 320;
    }
    // every button
    m_commandLabel[i] = null;
    b = new GUI_Button();
    b->setText("KEY");
    b->setPosition(x, y);
    b->setSize(40, 40);
    b->setColor(0, 0, 0, 0.5f);
    b->setColor(0, 0, 0, 0.25f, GUI_HOVER);
    b->setFontSize(0.6f);
    b->setTextColor(1, 1, 1);
    b->setTextAlignement(TEXT_ALIGN_CENTER);
    b->setPositionType(GUI_POSITION_RELATIVE);
    addChild(b);
    x += 40;
    m_keyButton[i] = b;
    if (i == COMMAND_GRID_42) { // last button, skip some pixel
        y -= 25;
        x = 320;
    }
}

void GUI_InputSettingsPannel::setInputSettingsSource(InputMapping* p) {
    m_settingsSource = p;
    GUI_Label* l;
    GUI_Button* b;

    for (unsigned i = 1; i < COMMAND_KEY_COUNT; i++) {
        l = m_commandLabel[i];
        if (l != null)
            l->setText(m_settingsSource->command[i] + " :");
        b = m_keyButton[i];
        if (b != null)
            b->setText(m_settingsSource->name[i]);
    }
}

GUI* GUI_InputSettingsPannel::tryActive(const float & x, const float & y) {
    if (cursorPositionIn(x, y)) {
        if (m_buttonReset->cursorPositionIn(x, y)) {
            std::cout << "reset button activated" << std::endl;
            m_buttonReset->setMode(GUI_ACTIVE);
            return m_buttonReset;
        }
        std::cout << "frame activated" << std::endl;
        m_mode = GUI_ACTIVE;
        return this;
    }
    return null;
}

GUI* GUI_InputSettingsPannel::tryClick(const float & x, const float & y) {
    if (cursorPositionIn(x, y)) {
        if (m_buttonReset->cursorPositionIn(x, y) && m_buttonReset->getMode() == GUI_ACTIVE) {
            std::cout << "reset button clicked" << std::endl;
            m_buttonReset->onClick();
            m_buttonReset->setMode(GUI_NORMAL);
            m_buttonReset->tryHover(x, y);
            return m_buttonReset;
        } else if (m_mode == GUI_ACTIVE) {
            onClick();
            std::cout << "frame clicked" << std::endl;
            m_mode = GUI_NORMAL;
            tryHover(x, y);
            return this;
        }
    }
    if (m_mode == GUI_ACTIVE) {
        m_mode = GUI_NORMAL;
        tryHover(x, y);
    }
    return null;
}

Command GUI_InputSettingsPannel::getCommand(const float & x, const float & y) {
    for (int i = 1; i < COMMAND_KEY_COUNT; i++) {
        if ((m_commandLabel[i] != null && m_commandLabel[i]->cursorPositionIn(x, y))
                || (m_keyButton[i] != null && m_keyButton[i]->cursorPositionIn(x, y)))

            return (Command) i;
    }
    return COMMAND_NONE;
}

Command GUI_InputSettingsPannel::getCommand(const glm::vec2 & pos) {
    return getCommand(pos.x, pos.y);
}

