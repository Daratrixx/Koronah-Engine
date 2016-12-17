
#include "GUI.h"

GUI_Button::GUI_Button() : GUI_Label() {
    m_onClick = null;
}

GUI_Button::~GUI_Button() {

}

void GUI_Button::setOnClickCallBack(void(*callBack)(void)) {
    m_onClick = callBack;
}

void GUI_Button::onClick() {
    if (m_onClick != null)
        m_onClick();
    else
        std::cout << "no callback function" << std::endl;
}