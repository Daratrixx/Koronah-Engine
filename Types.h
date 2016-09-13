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
#define DEFAULT_FRAMEBUFFER_WIDTH 400
#define DEFAULT_FRAMEBUFFER_HEIGHT 300
#define IDENTITY glm::mat4()
#define PI 3.14159265
#define RADIAN PI/180
#define DEGRE 180/PI
#define SHADER_INDEX_VERTEX 0
#define SHADER_INDEX_NORMAL 1
#define SHADER_INDEX_TEXCOORD_0 2
#define SHADER_INDEX_TEXTURE_INDEX 1
#define SHADER_INDEX_OPACITY 2
#define SHADER_INDEX_SIZE 3
#define SHADER_INDEX_GUI_SIZE 1
#define SHADER_INDEX_GUI_COLOR 2
#define PARTICLE_MAX_COUNT 10000
#define LIGHT_COUNT 16

#define ORDER_EXIT -1
#define ORDER_CONTINUE 0
#define ORDER_TO_PLAYGROUND 1
#define ORDER_TO_MENU 2

#define GUI_NORMAL 0
#define GUI_HOVER 1
#define GUI_MODE_COUNT 2

// define functions
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#endif	/* TYPES_H */
