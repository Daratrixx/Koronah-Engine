#include "GUI.h"

GUI_PlayerInfoPanel::GUI_PlayerInfoPanel() : GUI() {
    setPosition(0, 0);
    setSize(800, 100);
    setTextureID(loadTexture("data/gui/iconBorder.png"));

    m_labelPlayerName = new GUI_DynamicLabel();
    m_labelPlayerName->setPosition(100, 90);
    m_labelPlayerName->setSize(200, 20);
    m_labelPlayerName->setText("PlayerName");
    m_labelPlayerName->setGetText(GDL_getPlayerName);
    m_labelPlayerName->setTextAlignement(TEXT_ALIGN_CENTER);
    m_labelPlayerName->setTextureID(loadTexture("data/gui/iconBorder.png"));
    addChild(m_labelPlayerName);

    m_labelEnergy = new GUI_DynamicLabel();
    m_labelEnergy->setPosition(5, 5);
    m_labelEnergy->setSize(200, 20);
    m_labelEnergy->setText("PlayerEnergy");
    m_labelEnergy->setGetText(GDL_getPlayerEnergy);
    m_labelEnergy->setTextAlignement(TEXT_ALIGN_RIGHT);
    m_labelEnergy->setTextureID(loadTexture("data/gui/playerInfoEnergy.png"));
    addChild(m_labelEnergy);

    m_labelMaterials = new GUI_DynamicLabel();
    m_labelMaterials->setPosition(5, 30);
    m_labelMaterials->setSize(200, 20);
    m_labelMaterials->setText("PlayerMaterials");
    m_labelMaterials->setGetText(GDL_getPlayerMaterials);
    m_labelMaterials->setTextAlignement(TEXT_ALIGN_RIGHT);
    m_labelMaterials->setTextureID(loadTexture("data/gui/playerInfoMaterials.png"));
    addChild(m_labelMaterials);

    m_labelSupply = new GUI_DynamicLabel();
    m_labelSupply->setPosition(5, 55);
    m_labelSupply->setSize(200, 20);
    m_labelSupply->setText("PlayerSupply");
    m_labelSupply->setGetText(GDL_getPlayerSupply);
    m_labelSupply->setTextAlignement(TEXT_ALIGN_RIGHT);
    m_labelSupply->setTextureID(loadTexture("data/gui/iconBorder.png"));
    addChild(m_labelSupply);
}

GUI_PlayerInfoPanel::~GUI_PlayerInfoPanel() {
    
}

void GUI_PlayerInfoPanel::setPlayerInfoSource(Player* p) {
    m_labelPlayerName->setSource(p);
    m_labelEnergy->setSource(p);
    m_labelMaterials->setSource(p);
    m_labelSupply->setSource(p);
}

