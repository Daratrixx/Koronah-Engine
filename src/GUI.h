/* 
 * File:   GUI.h
 * Author: ANTOINE
 *
 * Created on 8 août 2016, 17:38
 */
#pragma once

#ifndef GUI_H
#define	GUI_H

#include "Types.h"
#include "Settings.h"
#include "Shader.h"
#include "GraphicEngine.h"
#include "TextEngine.h"
#include "Texture.h"
#include "Unit.h"
#include "Texture.h"
#include "Player.h"
#include "Input.h"


class GUI {
public:
    GUI();
    virtual ~GUI();

    virtual void render(GraphicEngine* Graphic);
    void renderGUI(GraphicEngine* Graphic);
    void renderChildren(GraphicEngine* Graphic) const;
    virtual void loadGUI();

    void addChild(GUI* child);
    void removeChild(GUI* child);
    void removeChildAt(const UShort & index);
    void clearChildren();

    GUI* getParent() const;
    GUI** getChildren() const;
    GUI* getChildAt(const UShort & index) const;
    UShort getChildrenCount() const;
    glm::vec2 getPosition() const;
    glm::vec2 getPosition(const UShort & mode) const;
    glm::vec2 getSize() const;
    glm::vec2 getSize(const UShort & mode) const;
    glm::vec4 getColor() const;
    glm::vec4 getColor(const UShort & mode) const;
    GLuint getTextureID() const;
    UShort getMode() const;
    bool getVisible() const;
    bool getDisplayColor() const;
    void setParent(GUI* parent);
    void setChildren(GUI** children);
    void setPosition(const glm::vec2 & pos);
    void setPosition(const glm::vec2 & pos, const UShort & mode);
    void setPosition(const float & x, const float & y);
    void setPosition(const float & x, const float & y, const UShort & mode);
    void setSize(const glm::vec2 & size);
    void setSize(const glm::vec2 & size, const UShort & mode);
    void setSize(const float & w, const float & h);
    void setSize(const float & w, const float & h, const UShort & mode);
    void setColor(const glm::vec4 & color);
    void setColor(const glm::vec4 & color, const UShort &);
    void setColor(const float & r, const float & g, const float & b, const float & a);
    void setColor(const float & r, const float & g, const float & b, const float & a, const UShort & mode);
    void setTextureID(const GLuint & textureID);
    void setMode(const UShort & mode);
    void setVisible(const bool & visible);
    void setDisplayColor(const bool & display);
    void setPositionType(const UShort & type);
    void setSizeType(const UShort & type);


    virtual void update(const float & time);
    virtual GUI* tryActive(const float & x, const float & y);
    virtual GUI* tryActive(const glm::vec2 & pos);
    virtual GUI* tryActiveChildren(const float & x, const float & y);
    virtual GUI* tryActiveChildren(const glm::vec2 & pos);
    virtual GUI* tryClick(const float & x, const float & y);
    virtual GUI* tryClick(const glm::vec2 & pos);
    virtual GUI* tryClickChildren(const float & x, const float & y);
    virtual GUI* tryClickChildren(const glm::vec2 & pos);
    virtual void tryHover(const float & x, const float & y);
    virtual void tryHover(const glm::vec2 & pos);
    virtual void tryHoverChildren(const float & x, const float & y);
    virtual void tryHoverChildren(const glm::vec2 & pos);
    virtual bool cursorPositionIn(const float & x, const float & y);
    virtual bool cursorPositionIn(const glm::vec2 & pos);
    virtual void onClick();
    virtual void onCursorEnter();
    virtual void onCursorLeave();

protected:
    bool m_needLoadGUI;
    glm::vec2 m_position[GUI_MODE_COUNT];
    glm::vec2 m_size[GUI_MODE_COUNT];
    glm::vec4 m_color[GUI_MODE_COUNT];
    bool m_visible;
    bool m_displayColor;
    GUI* m_parent;
    GUI** m_children;
    GLuint m_textureID;
    UShort m_childrenCount;
    UShort m_mode;
    UShort m_positionType;
    UShort m_sizeType;
    float m_time;

    GLuint m_vboGUI[GUI_MODE_COUNT];
    GLuint m_vaoGUI[GUI_MODE_COUNT];
};

class GUI_Label : public GUI {
public:
    GUI_Label();
    virtual ~GUI_Label();

    virtual void render(GraphicEngine* Graphic);
    virtual void renderLabel(GraphicEngine* Graphic) const;

    virtual std::string getText() const;
    virtual std::string getText(const UShort & mode) const;
    virtual glm::vec3 getTextColor() const;
    virtual glm::vec3 getTextColor(const UShort & mode) const;
    virtual UShort getTextAlignement() const;
    virtual UShort getTextAlignement(const UShort & mode) const;
    float getFontSize() const;
    float getFontSize(const UShort & mode) const;
    float getBlinkSpeed() const;
    float getBlinkSpeed(const UShort & mode) const;
    bool getBlinkText() const;
    bool getBlinkText(const UShort & mode) const;
    bool getDisplayText() const;
    void setText(const std::string & text);
    void setText(const std::string & text, const UShort & mode);
    void setTextAlignement(const UShort & alignement);
    void setTextAlignement(const UShort & alignement, const UShort & mode);
    void setTextColor(const glm::vec3 & color);
    void setTextColor(const float & r, const float & g, const float & b);
    void setTextColor(const glm::vec3 & color, const UShort & mode);
    void setTextColor(const float & r, const float & g, const float & b, const UShort & mode);
    void setFontSize(const float & size);
    void setFontSize(const float & size, const UShort & mode);
    void setBlinkSpeed(const float & speed);
    void setBlinkSpeed(const float & speed, const UShort & mode);
    void setBlinkText(const bool & blink);
    void setBlinkText(const bool & blink, const UShort & mode);
    void setDisplayText(const bool & display);

protected:
    std::string m_text[GUI_MODE_COUNT];
    glm::vec3 m_textColor[GUI_MODE_COUNT];
    UShort m_textAlignement[GUI_MODE_COUNT];
    float m_fontSize[GUI_MODE_COUNT];
    float m_blinkSpeed[GUI_MODE_COUNT];
    bool m_blinkText[GUI_MODE_COUNT];
    bool m_displayText;
};

class GUI_DynamicLabel : public GUI_Label {
public:
    GUI_DynamicLabel();
    virtual ~GUI_DynamicLabel();

    void setGetText(std::string(*getText)(void*, const float &));
    void setGetTextColor(glm::vec3(*getTextColor)(void*, const float &));
    void setSource(void* source);
    virtual std::string getText() const;
    virtual std::string getText(const UShort & mode) const;
    virtual glm::vec3 getTextColor() const;
    virtual glm::vec3 getTextColor(const UShort & mode) const;

protected:
    std::string(*m_getText)(void* source, const float & time);
    glm::vec3(*m_getTextColor)(void* source, const float & time);
    void* m_source;
};

class GUI_Button : public GUI_Label {
public:
    GUI_Button();
    virtual ~GUI_Button();

    void setOnClickCallBack(void(*callBack)(void));

    virtual void onClick();

protected:
    void (*m_onClick)(void);
};

class GUI_Bar : public GUI {
public:
    GUI_Bar();
    virtual ~GUI_Bar();

    virtual void render(GraphicEngine* Graphic);
    void renderBar(GraphicEngine* Graphic);
    virtual void loadBar();

    void setBarPercent(const float & percent);
    void setBarColor(const glm::vec3 & color);
    void setBarColor(const glm::vec3 & color, const UShort & mode);
    void setBarColor(const float & r, const float & g, const float & b);
    void setBarColor(const float & r, const float & g, const float & b, const UShort & mode);
    void setBarMargin(const glm::vec2 & margin);
    void setBarMargin(const glm::vec2 & margin, const UShort & mode);
    void setBarMargin(const float & w, const float & h);
    void setBarMargin(const float & w, const float & h, const UShort & mode);
    virtual float getBarPercent();
    virtual glm::vec3 getBarColor();
    virtual glm::vec3 getBarColor(const UShort & mode);
    virtual glm::vec2 getBarMargin();
    virtual glm::vec2 getBarMargin(const UShort & mode);

protected:
    bool m_needLoadBar;
    glm::vec2 m_barMargin[GUI_MODE_COUNT];
    glm::vec3 m_barColor[GUI_MODE_COUNT];
    float m_barPercent;

    GLuint m_vboBar[GUI_MODE_COUNT];
    GLuint m_vaoBar[GUI_MODE_COUNT];
};

class GUI_DynamicBar : public GUI_Bar {
public:
    GUI_DynamicBar();
    virtual ~GUI_DynamicBar();
    virtual void render(GraphicEngine* Graphic);
    void setGetBarPercent(float(*getBarPercent)(void*, const float &));
    void setGetBarColor(glm::vec3(*getColorColor)(void*, const float &));
    void setSource(void* source);
    virtual float getBarPercent();
    virtual glm::vec3 getBarColor();
    virtual glm::vec3 getBarColor(const UShort & mode);

protected:
    float(*m_getBarPercent)(void* source, const float & time);
    glm::vec3(*m_getBarColor)(void* source, const float & time);
    void* m_source;
};

class GUI_OrderPanel : public GUI {
public:
    GUI_OrderPanel();
    virtual ~GUI_OrderPanel();

    GUI_Button* m_orderMove;
    GUI_Button* m_orderAttack;
    GUI_Button* m_orderStop;
    GUI_Button* m_orderHold;
    GUI_Button* m_orderPatrol;
};

class GUI_PlayerInfoPanel : public GUI {
public:
    GUI_PlayerInfoPanel();
    virtual ~GUI_PlayerInfoPanel();

    void setPlayerInfoSource(Player* p);
    
    GUI_DynamicLabel* m_labelPlayerName;
    GUI_DynamicLabel* m_labelEnergy;
    GUI_DynamicLabel* m_labelMaterials;
    GUI_DynamicLabel* m_labelSupply;
};

class GUI_InputSettingsPannel : public GUI {
public:
    GUI_InputSettingsPannel();
    virtual ~GUI_InputSettingsPannel();
    void initOtherCommand(const UInt & i, float & x, float & y);
    void initGridCommand(const UInt & i, float & x, float & y);
    void setInputSettingsSource(InputMapping* p);
    virtual GUI* tryActive(const float & x, const float & y);
    virtual GUI* tryClick(const float & x, const float & y);
    Command getCommand(const float & x, const float & y);
    Command getCommand(const glm::vec2 & pos);
    InputMapping* m_settingsSource;
    GUI_Label* m_commandLabel[COMMAND_KEY_COUNT];
    GUI_Button* m_keyButton[COMMAND_KEY_COUNT];
    GUI_Button* m_buttonReset;
};


// dynamic label getText function
std::string GDL_getPlayerName(void* source, const float & time);
std::string GDL_getPlayerEnergy(void* source, const float & time);
std::string GDL_getPlayerMaterials(void* source, const float & time);
std::string GDL_getPlayerSupply(void* source, const float & time);
std::string GDL_getHPMax(void* source, const float & time);
std::string GDL_getHPCurrent(void* source, const float & time);
std::string GDL_getHPPercent(void* source, const float & time);
std::string GDL_getFPS(void* source, const float & time);

std::string GDL_getName(void* source, const float & time);
std::string GDL_getLevel(void* source, const float & time);

// dynamic bar getBarPercent function
float GDB_getHealthPercent(void* source, const float & time);
float GDB_getExperiencePercent(void* source, const float & time);

#endif	/* GUI_H */

