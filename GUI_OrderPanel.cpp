#include "GUI.h"

GUI_OrderPanel::GUI_OrderPanel() : GUI() {
    GUI* border;
    setPosition(500,50);
    setSize(240,50);
    setTextureID(loadTexture("data/gui/iconBorder.png"));

    m_orderMove = new GUI_Button();
    m_orderMove->setPosition(4, 4);
    m_orderMove->setSize(32, 32);
    m_orderMove->setTextureID(loadTexture("data/icon/orderMove.png"));
    m_orderMove->setColor(1.5f, 1.5f, 1.5f, 1, GUI_HOVER);
    m_orderMove->setPositionType(GUI_RELATIVE);
    border = new GUI();
    border->setPosition(0, 5);
    border->setSize(40, 40);
    border->setTextureID(loadTexture("data/gui/iconBorder.png"));
    border->setPositionType(GUI_RELATIVE);
    border->addChild(m_orderMove);
    addChild(border);

    m_orderAttack = new GUI_Button();
    m_orderAttack->setPosition(4, 4);
    m_orderAttack->setSize(32, 32);
    m_orderAttack->setTextureID(loadTexture("data/icon/orderAttack.png"));
    m_orderAttack->setColor(1.5f, 1.5f, 1.5f, 1, GUI_HOVER);
    m_orderAttack->setPositionType(GUI_RELATIVE);
    border = new GUI();
    border->setPosition(50, 5);
    border->setSize(40, 40);
    border->setTextureID(loadTexture("data/gui/iconBorder.png"));
    border->setPositionType(GUI_RELATIVE);
    border->addChild(m_orderAttack);
    addChild(border);

    m_orderStop = new GUI_Button();
    m_orderStop->setPosition(4, 4);
    m_orderStop->setSize(32, 32);
    m_orderStop->setTextureID(loadTexture("data/icon/orderStop.png"));
    m_orderStop->setColor(1.5f, 1.5f, 1.5f, 1, GUI_HOVER);
    m_orderStop->setPositionType(GUI_RELATIVE);
    border = new GUI();
    border->setPosition(100, 5);
    border->setSize(40, 40);
    border->setTextureID(loadTexture("data/gui/iconBorder.png"));
    border->setPositionType(GUI_RELATIVE);
    border->addChild(m_orderStop);
    addChild(border);

    m_orderHold = new GUI_Button();
    m_orderHold->setPosition(4, 4);
    m_orderHold->setSize(32, 32);
    m_orderHold->setTextureID(loadTexture("data/icon/orderHold.png"));
    m_orderHold->setColor(1.5f, 1.5f, 1.5f, 1, GUI_HOVER);
    m_orderHold->setPositionType(GUI_RELATIVE);
    border = new GUI();
    border->setPosition(150, 5);
    border->setSize(40, 40);
    border->setTextureID(loadTexture("data/gui/iconBorder.png"));
    border->setPositionType(GUI_RELATIVE);
    border->addChild(m_orderHold);
    addChild(border);

    m_orderPatrol = new GUI_Button();
    m_orderPatrol->setPosition(4, 4);
    m_orderPatrol->setSize(32, 32);
    m_orderPatrol->setTextureID(loadTexture("data/icon/orderPatrol.png"));
    m_orderPatrol->setColor(1.5f, 1.5f, 1.5f, 1, GUI_HOVER);
    m_orderPatrol->setPositionType(GUI_RELATIVE);
    border = new GUI();
    border->setPosition(200, 5);
    border->setSize(40, 40);
    border->setTextureID(loadTexture("data/gui/iconBorder.png"));
    border->setPositionType(GUI_RELATIVE);
    border->addChild(m_orderPatrol);
    addChild(border);
}

GUI_OrderPanel::~GUI_OrderPanel() {

}