#pragma once

#ifndef HEIGHTMAPDATA_H
#define HEIGHTMAPDATA_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

Uint32 getPixelColor(SDL_Surface * surface, int x, int y);

class HeightMapData : public GameObject {
public:
    HeightMapData(std::string imagePath);
    ~HeightMapData();
    void loadHeightMapData(SDL_Surface *map);
    float getPixel(int X, int Y);
    void setPixel(int X, int Y, float value);
    float* getVertice();
    int getVerticeCount();
    int getX();
    int getY();
    float collision(glm::vec3 p);
    
private:
    int m_verticeCount;
    int m_x, m_y;
    float *m_pixel;
    float *m_vertice;
};

#endif
