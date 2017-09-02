/* 
 * File:   TYPES_H
 * Author: ANTOINE
 *
 * Created on 11 mai 2016, 20:42
 */
#pragma once

#ifndef TYPES_H
#define TYPES_H

#define _USE_MATH_DEFINES

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
#include <iterator>
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
#define DEFAULT_SCREEN_FOV 90
#define DEFAULT_FRAMEBUFFER_WIDTH 400
#define DEFAULT_FRAMEBUFFER_HEIGHT 300
#define SCAN_SCALE 2
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

#define ORDER_EXIT 0
#define ORDER_CONTINUE 1
#define ORDER_TO_PLAYGROUND 2
#define ORDER_TO_MENU 3
#define ORDER_TO_SETTINGS 4

#define GUI_NORMAL 0
#define GUI_HOVER 1
#define GUI_ACTIVE 2
#define GUI_MODE_COUNT 3

#define GUI_POSITION_FIXED 0
#define GUI_POSITION_RELATIVE 1

#define GUI_SIZE_FIXED 0
#define GUI_SIZE_RELATIVE 1

#define TEXT_ALIGN_LEFT 0
#define TEXT_ALIGN_RIGHT 1
#define TEXT_ALIGN_CENTER 2

// dark star
#define RACE_TONITH 0
#define RACE_SCORDOM 1
#define RACE_EU 2
#define RACE_USA 3
#define RACE_AU 4
#define RACE_COUNT 5

#define PLAYER_1 0
#define PLAYER_2 1
#define PLAYER_3 2
#define PLAYER_4 3
#define PLAYER_5 4
#define PLAYER_6 5
#define PLAYER_7 6
#define PLAYER_8 7
#define PLAYER_COUNT 8
#define MAX_PLAYER_UNIT_COUNT 2000;
#define MAX_MAP_SIZE 128
#define MAX_UNIT_COUNT 16000

#define COLOR_GREEN glm::vec3(0,1,0)
#define COLOR_PURPLE glm::vec3(.5f,0,.5f)
#define COLOR_ORANGE glm::vec3(.7f,.30f,0)
#define COLOR_BLUE glm::vec3(0,0,1)
#define COLOR_YELLOW glm::vec3(1,1,0)
#define COLOR_RED glm::vec3(1,0,0)
#define COLOR_BLACK glm::vec3(0,0,0)
#define COLOR_WHITE glm::vec3(1,1,1)
#define COLOR_BROWN glm::vec3(.5f,.25f,0)
#define COLOR_PINK glm::vec3(1,0.5f,.5f)

#define TEAM_COLOR_1 COLOR_GREEN
#define TEAM_COLOR_2 COLOR_PURPLE
#define TEAM_COLOR_3 COLOR_ORANGE
#define TEAM_COLOR_4 COLOR_BLUE
#define TEAM_COLOR_5 COLOR_YELLOW
#define TEAM_COLOR_6 COLOR_RED
#define TEAM_COLOR_7 COLOR_BLACK
#define TEAM_COLOR_8 COLOR_WHITE

#define GAME_NO_STATE 0
#define GAME_LEFT_DOWN 1
#define GAME_LEFT_SQUARING 2
#define GAME_LEFT_WAIT_UNIT_TARGET 3
#define GAME_LEFT_WAIT_MAP_TARGET 4
#define GAME_LEFT_WAIT_ORDER_ATTACK 5
#define GAME_LEFT_WAIT_ORDER_MOVE 6
#define GAME_LEFT_WAIT_ORDER_PATROL 7

#define SETTING_NO_STATE 0
#define SETTING_MAPPING 1
#define SETTING_SLIDING 2

#define UNIT_BEHAVIOR_HOLD 0
#define UNIT_BEHAVIOR_IDLE 1
#define UNIT_BEHAVIOR_BUILDING 2
#define UNIT_BEHAVIOR_MOVING 3
#define UNIT_BEHAVIOR_FOLLOWING 4
#define UNIT_BEHAVIOR_PATROLING 5
#define UNIT_BEHAVIOR_ATTACK_MOVING 6
#define UNIT_BEHAVIOR_ATTACKING 7
#define UNIT_BEHAVIOR_BEING_BUILT 8 // for buildings
#define UNIT_BEHAVIOR_TRAINING 9 // for buildings
#define UNIT_BEHAVIOR_PUSHED 10

#define PLAYER_RELATION_ENEMY 0
#define PLAYER_RELATION_ALLY 1
#define PLAYER_RELATION_VISION 2
#define PLAYER_RELATION_SHARE_VISION 4
#define PLAYER_RELATION_SHARE_CONTROL 8

// script args declaration
#define SCRIPT_ARG_NORMAL 0
#define SCRIPT_ARG_TRIGGERING_UNIT 1
#define SCRIPT_ARG_LAST_CREATED_UNIT 2
#define SCRIPT_ARG_ENTERING_UNIT 3
#define SCRIPT_ARG_LEAVING_UNIT 4
#define SCRIPT_ARG_KILLING_UNIT 5
#define SCRIPT_ARG_DYING_UNIT 6
#define SCRIPT_ARG_DAMAGING_UNIT 7
#define SCRIPT_ARG_DAMAGED_UNIT 8
#define SCRIPT_ARG_TRAINING_UNIT 9
#define SCRIPT_ARG_TRAINED_UNIT 10
#define SCRIPT_ARG_BUILDING_UNIT 11
#define SCRIPT_ARG_BUILDED_UNIT 12
#define SCRIPT_ARG_TRIGGERING_AREA 900
#define SCRIPT_ARG_ENTERED_AREA 901
#define SCRIPT_ARG_LEAVED_AREA 902
#define SCRIPT_ARG_FLOAT_TO_DELETE 1000
#define SCRIPT_ARG_DAMAGES_AMOUNT 1001

// define functions
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// forward class declaration

class GameEngine;
class Serializable;
class GameObject;
class Entity;
class Unit;
class Missile;
class Triggerable;
class TriggerableInstance;
class Buff;
class BuffInstance;
class Spell;
class SpellInstance;

class TextEngine;
class GraphicEngine;

class Model;
class Texture;

typedef int8_t Short;
typedef uint8_t UShort;

typedef int16_t Int;
typedef int16_t Integer;
typedef uint16_t UInt;

typedef int32_t Long;
typedef uint32_t ULong;

typedef float Float;
typedef float Real;

typedef std::string String;

typedef glm::vec2 Point;
typedef glm::vec4 Region;

#endif /* TYPES_H */
