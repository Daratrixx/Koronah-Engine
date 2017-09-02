#pragma once

#ifndef SHAPE_HPP
#define SHAPE_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef FACE_HPP
#include "Face.hpp"
#endif

class Shape {
public:

    Shape() {
        m_vertice = NULL;
        m_texture = NULL;
        m_normal = NULL;
    }

    ~Shape() {
        m_facesVertice.clear();
        m_facesNormal.clear();
        m_facesTexture.clear();
    }

    void addFaceV(const UInt & a, const UInt & b, const UInt & c) {
        m_facesVertice.push_back(Face(a, b, c));
    }

    void addFaceN(const UInt & a, const UInt & b, const UInt & c) {
        m_facesNormal.push_back(Face(a, b, c));
    }

    void addFaceT(const UInt & a, const UInt & b, const UInt & c) {
        m_facesTexture.push_back(Face(a, b, c));
    }

    void setVertice(float* vertice) {
        if (m_vertice)
            delete m_vertice;

        m_vertice = new float[9 * m_facesVertice.size()];
        if (m_vertice && vertice) {
            for (UInt i = 0; i < m_facesVertice.size(); i++) {
                Face temp = m_facesVertice[i];
                *(m_vertice + i * 9 + 0) = *(vertice + temp.getVertex(0)*3 + 0);
                *(m_vertice + i * 9 + 1) = *(vertice + temp.getVertex(0)*3 + 1);
                *(m_vertice + i * 9 + 2) = *(vertice + temp.getVertex(0)*3 + 2);
                *(m_vertice + i * 9 + 3) = *(vertice + temp.getVertex(1)*3 + 0);
                *(m_vertice + i * 9 + 4) = *(vertice + temp.getVertex(1)*3 + 1);
                *(m_vertice + i * 9 + 5) = *(vertice + temp.getVertex(1)*3 + 2);
                *(m_vertice + i * 9 + 6) = *(vertice + temp.getVertex(2)*3 + 0);
                *(m_vertice + i * 9 + 7) = *(vertice + temp.getVertex(2)*3 + 1);
                *(m_vertice + i * 9 + 8) = *(vertice + temp.getVertex(2)*3 + 2);
            }
            //std::cout << "ModelObj with "<< (9 * m_facesVertice.size()) << " vertice data" << std::endl;
        } else {
            std::cout << "Error loading vertice  data" << std::endl;
        }
    }

    void setNormal(float* normal) {
        if (m_normal)
            delete m_normal;

        m_normal = new float[9 * m_facesNormal.size()];
        if (m_normal && normal) {
            for (UInt i = 0; i < m_facesNormal.size(); i++) {
                Face temp = m_facesNormal[i];
                *(m_normal + i * 9 + 0) = *(normal + temp.getVertex(0)*3 + 0);
                *(m_normal + i * 9 + 1) = *(normal + temp.getVertex(0)*3 + 1);
                *(m_normal + i * 9 + 2) = *(normal + temp.getVertex(0)*3 + 2);
                *(m_normal + i * 9 + 3) = *(normal + temp.getVertex(1)*3 + 0);
                *(m_normal + i * 9 + 4) = *(normal + temp.getVertex(1)*3 + 1);
                *(m_normal + i * 9 + 5) = *(normal + temp.getVertex(1)*3 + 2);
                *(m_normal + i * 9 + 6) = *(normal + temp.getVertex(2)*3 + 0);
                *(m_normal + i * 9 + 7) = *(normal + temp.getVertex(2)*3 + 1);
                *(m_normal + i * 9 + 8) = *(normal + temp.getVertex(2)*3 + 2);
            }
            //std::cout << "ModelObj with "<< (9 * m_facesNormal.size()) << " normal data" << std::endl;
        } else {
            std::cout << "Error loading normal data" << std::endl;
        }
    }

    void setTexture(float* texture) {
        if (m_texture)
            delete m_texture;

        m_texture = new float[6 * m_facesVertice.size()];
        if (!texture) {
            for (UInt i = 0; i < m_facesVertice.size(); i++) {
                *(m_texture + i * 6 + 0) = 0;
                *(m_texture + i * 6 + 1) = 0;
                *(m_texture + i * 6 + 2) = 0.5;
                *(m_texture + i * 6 + 3) = 1;
                *(m_texture + i * 6 + 4) = 1;
                *(m_texture + i * 6 + 5) = 0;
            }
            //std::cout << "ModelObj with no texture data" << std::endl;
        } else {
            for (UInt i = 0; i < m_facesVertice.size(); i++) {
                Face temp = m_facesTexture[i];
                *(m_texture + i * 6 + 0) = *(texture + temp.getVertex(0)*2 + 0);
                *(m_texture + i * 6 + 1) = *(texture + temp.getVertex(0)*2 + 1);
                *(m_texture + i * 6 + 2) = *(texture + temp.getVertex(1)*2 + 0);
                *(m_texture + i * 6 + 3) = *(texture + temp.getVertex(1)*2 + 1);
                *(m_texture + i * 6 + 4) = *(texture + temp.getVertex(2)*2 + 0);
                *(m_texture + i * 6 + 5) = *(texture + temp.getVertex(2)*2 + 1);
            }
            std::cout << "ModelObj with "<< (6 * m_facesVertice.size()) << " texture data" << std::endl;
        }
    }

    float* getVertice() const {
        return m_vertice;
    }

    float* getTexture() const {
        return m_texture;
    }

    float* getNormal() const {
        return m_normal;
    }

    UInt getVerticeCount() const {
        return m_facesVertice.size()*3;
    }
private:
    std::vector<Face> m_facesVertice;
    std::vector<Face> m_facesNormal;
    std::vector<Face> m_facesTexture;
    float* m_vertice;
    float* m_texture;
    float* m_normal;
};

#endif
