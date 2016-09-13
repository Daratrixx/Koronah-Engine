/* 
 * File:   ModelHeightMap.hpp
 * Author: ANTOINE
 *
 * Created on 22 juin 2016, 22:29
 */
#pragma once

#ifndef MODELHEIGHTMAP_HPP
#define	MODELHEIGHTMAP_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef MODEL_H
#include "Model.h"
#endif

#ifndef HEIGHTMAPDATA_H
#include "HeightMapData.h"
#endif

class ModelHeightMap : public Model {
public:

    ModelHeightMap(int verticeCount, int width, int height, float* verticeData) : Model() {
        loadHeightMapData(verticeCount, width, height, verticeData);
        load();
    }

    ModelHeightMap(HeightMapData* heightMapData) : Model() {
        loadHeightMapData(heightMapData->getVerticeCount(), heightMapData->getX(), heightMapData->getY(), heightMapData->getVertice());
        load();
    }

    virtual ~ModelHeightMap() {

    }

    void loadHeightMapData(int verticeCount, unsigned int width, unsigned int height, float* verticeData) {
        m_verticeCount = verticeCount;
        m_verticeData = verticeData;

        float xSize, ySize;
        xSize = 1 / (float) (width);
        ySize = 1 / (float) (height);
        // Texture par defaut
        float *temp = new float[m_verticeCount * 2];
        
        m_textureData = temp;
        for (unsigned int j = 0u; j < height; j++) {
            for (unsigned int i = 0u; i < width; i++) {
                float xOffset, yOffset;
                xOffset = i * xSize;
                yOffset = j * ySize;

                *(temp) = xOffset;
                *(temp + 1) = yOffset;
                *(temp + 2) = xOffset;
                *(temp + 3) = yOffset + ySize;
                *(temp + 4) = xOffset + xSize;
                *(temp + 5) = yOffset + ySize;

                *(temp + 6) = xOffset;
                *(temp + 7) = yOffset;
                *(temp + 8) = xOffset + xSize;
                *(temp + 9) = yOffset + ySize;
                *(temp + 10) = xOffset + xSize;
                *(temp + 11) = yOffset;
                
                temp += 12;
            }
        }
        // Normal
        /**temp = new float[m_verticeCount * 3];
        for (int i = 0; i < m_verticeCount * 3; i += 18) {
            int x = (i/12) % (width);
            int y = (i/12) / (width);
            float xOffset, yOffset;
            xOffset = x * xSize;
            yOffset = y * ySize;
            *(temp + i) = xOffset;
            *(temp + i + 1) = yOffset;
            *(temp + i + 2) = xOffset + xSize;
            *(temp + i + 3) = yOffset + ySize;
            *(temp + i + 4) = xOffset + xSize;
            *(temp + i + 5) = yOffset;
            *(temp + i + 6) = xOffset;
            *(temp + i + 7) = yOffset;
            *(temp + i + 8) = xOffset;
            *(temp + i + 9) = yOffset + ySize;
            *(temp + i + 10) = xOffset + xSize;
            *(temp + i + 11) = yOffset + ySize;
        }
        m_normalData = temp;*/
    }

};

#endif	/* MODELHEIGHTMAP_HPP */

