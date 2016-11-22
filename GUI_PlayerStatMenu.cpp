#include "GUI.h"

GUI_PlayerStatMenu::GUI_PlayerStatMenu(Unit* player) : GUI_Window() {
    setPosition(50, 50);
    setSize(700, 500);
    setColor(1, 1, 1, 0.9f);
    setTextureID(loadTexture("data/gui/playerStatMenu.png"));

    GUI_DynamicLabel* gdl;

    // meta
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(400, 525);
    gdl->setTextColor(0.75f, 0.5f, 0);
    gdl->setFontSize(0.75f);
    //gdl->setGetText(GDL_getName);
    addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(400, 500);
    gdl->setTextColor(0.5f, 0.5f, 0.5f);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getLevel);
    addChild(gdl);

    // stats
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(600, 200);
    gdl->setTextColor(0.75f, 0, 0);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getTotalConstitution);
    gdl->setTextAlignement(TEXT_ALIGN_RIGHT);
    addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(600, 175);
    gdl->setTextColor(0, 0, 1);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getTotalMental);
    gdl->setTextAlignement(TEXT_ALIGN_RIGHT);
    addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(600, 150);
    gdl->setTextColor(0, 0.75f, 0);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getTotalDexterity);
    gdl->setTextAlignement(TEXT_ALIGN_RIGHT);
    addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(600, 125);
    gdl->setTextColor(0.75f, 0, 0.75f);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getTotalFate);
    gdl->setTextAlignement(TEXT_ALIGN_RIGHT);
    addChild(gdl);
    gdl = new GUI_DynamicLabel();
    gdl->setPosition(600, 100);
    gdl->setTextColor(0.75f, 0.75f, 0);
    gdl->setFontSize(0.5f);
    //gdl->setGetText(GDL_getTotalSocial);
    gdl->setTextAlignement(TEXT_ALIGN_RIGHT);
    addChild(gdl);

    setPlayer(player);

    GUI_DynamicBar* gdb = new GUI_DynamicBar();
    gdb->setPosition(70, 472);
    gdb->setSize(660, 5);
    gdb->setBarMargin(0, 0);
    gdb->setColor(1, 1, 1, 1);
    gdb->setBarColor(0.75f, 0.5f, 0);
    gdb->setSource((void*) m_player);
    //gdb->setGetBarPercent(GDL_getExperiencePercent);
    addChild(gdb);
}

GUI_PlayerStatMenu::~GUI_PlayerStatMenu() {

}

void GUI_PlayerStatMenu::setPlayer(Unit* player) {
    m_player = player;
    for (unsigned int i = 0; i < m_childrenCount; i++) {
        GUI_DynamicLabel* gdl = (GUI_DynamicLabel*) m_children[i];
        gdl->setSource((void*) m_player);
    }
}

Unit* GUI_PlayerStatMenu::getPlayer() const {
    return m_player;
}
