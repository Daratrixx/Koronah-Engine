/* 
 * File:   Settings.h
 * Author: ANTOINE
 *
 * Created on 27 septembre 2016, 18:51
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Setting {
public:
    Setting();
    virtual ~Setting();
    virtual bool load();
    virtual void reset();
    virtual bool save();
};

class GraphicSetting : public Setting {
public:
    GraphicSetting();
    virtual ~GraphicSetting();
    virtual bool load();
    virtual void reset();
    virtual bool save();

    unsigned screenWidth, screenHeight;
    unsigned scanDivisor;
    bool fullScreen;

};

class InputSetting : public Setting {
public:
    InputSetting();
    virtual ~InputSetting();
    virtual bool load();
    virtual void reset();
    virtual bool save();

    float mouseSensibility;
    float keyboardSensibility;
};

GraphicSetting* getGraphicSetting();
InputSetting* getInputSetting();
void loadSettings();
void saveSettings();

#endif /* SETTINGS_H */

