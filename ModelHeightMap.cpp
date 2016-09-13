#include "Model.h"

ModelHeightMap::ModelHeightMap(int verticeCount, int width, int height, float* verticeData) : Model() {
    loadHeightMapData(verticeCount, width, height, verticeData);
    load();
}

ModelHeightMap::ModelHeightMap(HeightMapData* heightMapData) : Model() {
    loadHeightMapData(heightMapData->getVerticeCount(), heightMapData->getX(), heightMapData->getY(), heightMapData->getVertice());
    load();
}

ModelHeightMap::~ModelHeightMap() {

}

void ModelHeightMap::loadHeightMapData(int verticeCount, unsigned int width, unsigned int height, float* verticeData) {
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
}