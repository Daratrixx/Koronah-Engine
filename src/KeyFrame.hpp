#pragma once

#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef VERTEX_HPP
#include "Vertex.hpp"
#endif

class KeyFrame {
public:

    KeyFrame() {
        m_frameVertice = NULL;
        m_frameNormal = NULL;
        m_frameTexture = NULL;
    }

    ~KeyFrame() {
        m_verticeList.clear();
        m_normalList.clear();
        m_textureList.clear();
        m_frameVertice = NULL;
        m_frameNormal = NULL;
        m_frameTexture = NULL;
    }

    void addVertexData(const float & x, const float & y, const float & z) {
        m_verticeList.push_back(VertexData(x, y, z));
    }

    void addNormalData(const float & x, const float & y, const float & z) {
        m_normalList.push_back(VertexData(x, y, z));
    }

    void addTextureData(const float & x, const float & y) {
        m_textureList.push_back(TextureData(x, y));
    }

    void startVertice() {
        if (m_verticeList.size() > 0) {
            m_frameVertice = createVertice();
            m_verticeList.clear();
        }
    }

    void startNormal() {
        if (m_normalList.size() > 0) {
            m_frameNormal = createNormal();
            m_normalList.clear();
        }
    }

    void startTexture() {
        if (m_textureList.size() > 0) {
            m_frameTexture = createTexture();
            m_textureList.clear();
        }
    }

    float* createVertice() {
        if (m_verticeList.size() == 0) {
            std::cout << "Error : no vertex data" << std::endl;
            return null;
        }

        float* vertices = new float[3 * m_verticeList.size()];
        if (!vertices) {
            std::cout << "Error : unable to create vertice array" << std::endl;
            return null;
        }

        for (UInt i = 0; i < m_verticeList.size(); i++) {
            VertexData temp = m_verticeList[i];
            *(vertices + i * 3 + 0) = temp.getPos(0);
            *(vertices + i * 3 + 1) = temp.getPos(1);
            *(vertices + i * 3 + 2) = temp.getPos(2);
        }

        return vertices;
    }

    float* createNormal() {
        if (m_normalList.size() == 0) {
            std::cout << "Error : no normal data" << std::endl;
            return null;
        }

        float* normal = new float[3 * m_normalList.size()];
        if (!normal) {
            std::cout << "Error : unable to create normal array" << std::endl;
            return null;
        }

        for (UInt i = 0; i < m_normalList.size(); i++) {
            VertexData temp = m_normalList[i];
            *(normal + i * 3 + 0) = temp.getPos(0);
            *(normal + i * 3 + 1) = temp.getPos(1);
            *(normal + i * 3 + 2) = temp.getPos(2);
        }

        return normal;
    }

    float* createTexture() {
        if (m_textureList.size() == 0) {
            std::cout << "Error : no texture data" << std::endl;
            return null;
        }

        float* verticesT = new float[2 * m_textureList.size()];
        if (!verticesT) {
            std::cout << "Error : unable to create texture array" << std::endl;
            return null;
        }

        for (UInt i = 0; i < m_textureList.size(); i++) {
            TextureData temp = m_textureList[i];
            *(verticesT + i * 2 + 0) = temp.getPos(0);
            *(verticesT + i * 2 + 1) = temp.getPos(1);
        }

        return verticesT;
    }

    float* getVertice() {
        if (!m_frameVertice)
            m_frameVertice = createVertice();
        return m_frameVertice;
    }

    float* getNormal() {
        if (!m_frameNormal)
            m_frameNormal = createNormal();
        return m_frameNormal;
    }

    float* getTexture() {
        if (!m_frameTexture)
            m_frameTexture = createTexture();
        return m_frameTexture;
    }

    int getVerticeCount() {
        return m_verticeList.size();
    }

    int getNormalCount() {
        return m_normalList.size();
    }

    int getTextureCount() {
        return m_textureList.size();
    }

private:
    std::vector<VertexData> m_verticeList;
    std::vector<VertexData> m_normalList;
    std::vector<TextureData> m_textureList;
    float* m_frameVertice;
    float* m_frameNormal;
    float* m_frameTexture;
};

#endif
