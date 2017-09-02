#pragma once

#ifndef HEIGHTMAPDATA_H
#define HEIGHTMAPDATA_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

Uint32 getPixelColor(SDL_Surface * surface, UInt x, UInt y);

class HeightMapData : public GameObject {
public:
    HeightMapData(std::string imagePath);
    ~HeightMapData();
    void loadHeightMapData(SDL_Surface *map);
    float getPixel(UInt X, UInt Y);
    void setPixel(UInt X, UInt Y, float value);
    float* getVertice();
    UInt getVerticeCount();
    UInt getX();
    UInt getY();
    float collision(glm::vec3 p);
    
private:
    UInt m_verticeCount;
    UInt m_x, m_y;
    float *m_pixel;
    float *m_vertice;
};

#endif
