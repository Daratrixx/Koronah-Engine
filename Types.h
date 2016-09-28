/* 
 * File:   TYPES_H
 * Author: ANTOINE
 *
 * Created on 11 mai 2016, 20:42
 */
#pragma once

#ifndef TYPES_H
#define	TYPES_H

// include main files
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// define constants
#define null NULL
#define NONE ((void)0)
#define none NONE
#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600
#define DEFAULT_SCREEN_NEAR 1
#define DEFAULT_SCREEN_FAR 200
#define DEFAULT_FRAMEBUFFER_WIDTH 400
#define DEFAULT_FRAMEBUFFER_HEIGHT 300
#define SCAN_SCALE 8
#define IDENTITY glm::mat4()
#define PI 3.14159265
#define RADIAN PI/180
#define DEGRE 180/PI
#define SHADER_TEXTURE_LOCATION_VERTEX 0
#define SHADER_TEXTURE_LOCATION_NORMAL 1
#define SHADER_TEXTURE_LOCATION_TEXCOORD_0 2
#define SHADER_SCAN_LOCATION_VERTEX 0
#define SHADER_SCAN_LOCATION_NORMAL 1
#define SHADER_SCAN_LOCATION_TEXCOORD_0 2
#define SHADER_PARTICLE_LOCATION_VERTEX 0
#define SHADER_PARTICLE_LOCATION_TEXTURE_INDEX 1
#define SHADER_PARTICLE_LOCATION_OPACITY 2
#define SHADER_PARTICLE_LOCATION_SIZE 3
#define SHADER_GUI_LOCATION_VERTEX 0
#define SHADER_GUI_LOCATION_SIZE 1
#define SHADER_GUI_LOCATION_COLOR 2
#define SHADER_SCREEN_LOCATION_POSITION 0
#define SHADER_SCREEN_LOCATION_TEXCOORD_0 1
#define SHADER_SQUARE_LOCATION_POSITION 0
#define PARTICLE_MAX_COUNT 10000
#define LIGHT_COUNT 16

#define ORDER_EXIT -1
#define ORDER_CONTINUE 0
#define ORDER_TO_PLAYGROUND 1
#define ORDER_TO_MENU 2

#define GUI_NORMAL 0
#define GUI_HOVER 1
#define GUI_MODE_COUNT 2

#define TEXT_ALIGN_LEFT 0
#define TEXT_ALIGN_RIGHT 1
#define TEXT_ALIGN_CENTER 2

// lystaroth
#define UNIT_CONSTITUTION 0
#define UNIT_MENTAL 1
#define UNIT_DEXTERITY 2
#define UNIT_FATE 3
#define UNIT_SOCIAL 4

#define ALTERATION_BLEEDING 0
#define ALTERATION_POISON 1
#define ALTERATION_TOXIN 2
#define ALTERATION_COLD 3
#define ALTERATION_EXHAUST 4
#define ALTERATION_BURN 5

#define ARMOR_CUIRASS 0
#define ARMOR_BOOTS 1
#define ARMOR_FAULD 2
#define ARMOR_GLOVES 3
#define ARMOR_HELMET 4
#define ARMOR_CLOACK 5
#define WEAPON_LEFT 0
#define WEAPON_RIGHT 1

// dark star
#define RACE_TONITH 0
#define RACE_SCORDOM 1
#define RACE_EU 2
#define RACE_USA 3
#define RACE_AU 4
#define RACE_COUNT 5

#define MAX_PLAYER_COUNT 8
#define MAX_PLAYER_UNIT_COUNT 200;
#define MAX_MAP_SIZE 128
#define MAX_UNIT_COUNT 10000

#define GAME_NO_STATE 0
#define GAME_LEFT_DOWN 1
#define GAME_LEFT_SQUARING 2
#define GAME_LEFT_WAIT_UNIT_TARGET 3
#define GAME_LEFT_WAIT_MAP_TARGET 4

#define UNIT_BEHAVIOR_HOLD 0
#define UNIT_BEHAVIOR_IDLE 1
#define UNIT_BEHAVIOR_MOVING 2
#define UNIT_BEHAVIOR_PUSHED 3

// define functions
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif	/* TYPES_H */
