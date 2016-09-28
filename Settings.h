/* 
 * File:   Settings.h
 * Author: ANTOINE
 *
 * Created on 27 septembre 2016, 18:51
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifndef TYPES_H
#include "Types.h"
#endif

glm::vec3* Settings_RESOLUTION();
glm::vec2 Settings_getResolution();
int Settings_getScreenWidth();
int Settings_getScreenHeight();
float Settings_getScreenRatio();
void Settings_setResolution(glm::vec2 resolution);
void Settings_setResolution(float w, float h);

#endif	/* SETTINGS_H */

