#include "GUI.h"

GUI_Window::GUI_Window() : GUI() {
    GUI_DynamicLabel* gdl;
    gdl = new GUI_DynamicLabel();
    gdl->setText("x");
    gdl->setBlinkSpeed(10, GUI_HOVER);
    gdl->setBlinkText(true, GUI_HOVER);
    gdl->setTextColor(0, 0.5f, 0.5f, GUI_NORMAL);
    gdl->setTextColor(0, 1, 1, GUI_HOVER);
    gdl->setPosition(720, 520);
    gdl->setSize(15, 15);
    gdl->setFontSize(0.75);
    gdl->setDisplayColor(false);
    setCloseButton(gdl);
}

GUI_Window::~GUI_Window() {
}

void GUI_Window::setCloseButton(GUI* gui) {
    m_closeButton = gui;
    addChild(gui);
}

bool GUI_Window::isCloseButton(GUI* gui) const {
    return gui == m_closeButton;
}