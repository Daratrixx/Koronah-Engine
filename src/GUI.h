/* 
 * File:   GUI.h
 * Author: ANTOINE
 *
 * Created on 8 août 2016, 17:38
 */
#pragma once

#ifndef GUI_H
#define	GUI_H

#ifndef TYPE_H
#include "Types.h"
#endif

#ifndef SETTINGS_H
#include "Settings.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

#ifndef GRAPHICENGINE_H
#include "GraphicEngine.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

#include "Texture.h"

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
    void removeChildAt(unsigned int index);
    void clearChildren();

    GUI* getParent() const;
    GUI** getChildren() const;
    GUI* getChildAt(unsigned int index) const;
    int getChildrenCount() const;
    glm::vec2 getPosition() const;
    glm::vec2 getPosition(unsigned int mode) const;
    glm::vec2 getSize() const;
    glm::vec2 getSize(unsigned int mode) const;
    glm::vec4 getColor() const;
    glm::vec4 getColor(unsigned int mode) const;
    GLuint getTextureID() const;
    bool getVisible() const;
    bool getDisplayColor() const;
    void setParent(GUI* parent);
    void setChildren(GUI** children);
    void setPosition(glm::vec2 pos);
    void setPosition(glm::vec2 pos, unsigned int mode);
    void setPosition(float x, float y);
    void setPosition(float x, float y, unsigned int mode);
    void setSize(glm::vec2 size);
    void setSize(glm::vec2 size, unsigned int mode);
    void setSize(float w, float h);
    void setSize(float w, float h, unsigned int mode);
    void setColor(glm::vec4 color);
    void setColor(glm::vec4 color, unsigned int mode);
    void setColor(float r, float g, float b, float a);
    void setColor(float r, float g, float b, float a, unsigned int mode);
    void setTextureID(GLuint textureID);
    void setVisible(bool visible);
    void setDisplayColor(bool display);
    void setPositionType(unsigned int type);
    void setSizeType(unsigned int type);


    virtual void update(float time);
    virtual GUI* tryActive(float x, float y);
    virtual GUI* tryActive(glm::vec2 pos);
    virtual GUI* tryActiveChildren(float x, float y);
    virtual GUI* tryActiveChildren(glm::vec2 pos);
    virtual GUI* tryClick(float x, float y);
    virtual GUI* tryClick(glm::vec2 pos);
    virtual GUI* tryClickChildren(float x, float y);
    virtual GUI* tryClickChildren(glm::vec2 pos);
    virtual void tryHover(float x, float y);
    virtual void tryHover(glm::vec2 pos);
    virtual void tryHoverChildren(float x, float y);
    virtual void tryHoverChildren(glm::vec2 pos);
    virtual bool cursorPositionIn(float x, float y);
    virtual bool cursorPositionIn(glm::vec2 pos);
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
    unsigned int m_childrenCount;
    unsigned int m_mode;
    unsigned int m_positionType;
    unsigned int m_sizeType;
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
    virtual std::string getText(unsigned int mode) const;
    virtual glm::vec3 getTextColor() const;
    virtual glm::vec3 getTextColor(unsigned int mode) const;
    virtual unsigned int getTextAlignement() const;
    virtual unsigned int getTextAlignement(unsigned int mode) const;
    float getFontSize() const;
    float getFontSize(unsigned int mode) const;
    float getBlinkSpeed() const;
    float getBlinkSpeed(unsigned int mode) const;
    bool getBlinkText() const;
    bool getBlinkText(unsigned int mode) const;
    bool getDisplayText() const;
    void setText(std::string text);
    void setText(std::string text, unsigned int mode);
    void setTextAlignement(unsigned int alignement);
    void setTextAlignement(unsigned int alignement, unsigned int mode);
    void setTextColor(glm::vec3 color);
    void setTextColor(float r, float g, float b);
    void setTextColor(glm::vec3 color, unsigned int mode);
    void setTextColor(float r, float g, float b, unsigned int mode);
    void setFontSize(float size);
    void setFontSize(float size, unsigned int mode);
    void setBlinkSpeed(float speed);
    void setBlinkSpeed(float speed, unsigned int mode);
    void setBlinkText(bool blink);
    void setBlinkText(bool blink, unsigned int mode);
    void setDisplayText(bool display);

protected:
    std::string m_text[GUI_MODE_COUNT];
    glm::vec3 m_textColor[GUI_MODE_COUNT];
    unsigned int m_textAlignement[GUI_MODE_COUNT];
    float m_fontSize[GUI_MODE_COUNT];
    float m_blinkSpeed[GUI_MODE_COUNT];
    bool m_blinkText[GUI_MODE_COUNT];
    bool m_displayText;
};

class GUI_DynamicLabel : public GUI_Label {
public:
    GUI_DynamicLabel();
    virtual ~GUI_DynamicLabel();

    void setGetText(std::string(*getText)(void*, float));
    void setGetTextColor(glm::vec3(*getTextColor)(void*, float));
    void setSource(void* source);
    virtual std::string getText() const;
    virtual std::string getText(unsigned int mode) const;
    virtual glm::vec3 getTextColor() const;
    virtual glm::vec3 getTextColor(unsigned int mode) const;

protected:
    std::string(*m_getText)(void* source, float time);
    glm::vec3(*m_getTextColor)(void* source, float time);
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

    void setBarPercent(float percent);
    void setBarColor(glm::vec3 color);
    void setBarColor(float r, float g, float b);
    void setBarColor(glm::vec3 color, unsigned int mode);
    void setBarColor(float r, float g, float b, unsigned int mode);
    void setBarMargin(glm::vec2 margin);
    void setBarMargin(glm::vec2 margin, unsigned int mode);
    void setBarMargin(float w, float h);
    void setBarMargin(float w, float h, unsigned int mode);
    virtual float getBarPercent();
    virtual glm::vec3 getBarColor();
    virtual glm::vec3 getBarColor(unsigned int mode);
    virtual glm::vec2 getBarMargin();
    virtual glm::vec2 getBarMargin(unsigned int mode);

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
    void setGetBarPercent(float(*getBarPercent)(void*, float));
    void setGetBarColor(glm::vec3(*getColorColor)(void*, float));
    void setSource(void* source);
    virtual float getBarPercent();
    virtual glm::vec3 getBarColor();
    virtual glm::vec3 getBarColor(unsigned int mode);

protected:
    float(*m_getBarPercent)(void* source, float time);
    glm::vec3(*m_getBarColor)(void* source, float time);
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


// dynamic label getText function
std::string GDL_getHPMax(void* source, float time);
std::string GDL_getHPCurrent(void* source, float time);
std::string GDL_getHPPercent(void* source, float time);
std::string GDL_getFPS(void* source, float time);

std::string GDL_getName(void* source, float time);
std::string GDL_getLevel(void* source, float time);

// dynamic bar getBarPercent function
float GDB_getHealthPercent(void* source, float time);
float GDB_getExperiencePercent(void* source, float time);

#endif	/* GUI_H */

