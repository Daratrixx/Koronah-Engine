#pragma once

#ifndef FACE_HPP
#define FACE_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

class Face {
public:

    Face() {
    }

    Face(const UInt & A, const UInt & B, const UInt & C) {
        m_vertex[0] = A;
        m_vertex[1] = B;
        m_vertex[2] = C;
    }

    ~Face() {
    }

    void setVertex(const UInt & A, const UInt & B, const UInt & C) {
        m_vertex[0] = A;
        m_vertex[1] = B;
        m_vertex[2] = C;
    }

    int getVertex(int n) {
        return m_vertex[n];
    }
private:
    int m_vertex[3];
};

class FaceT : public Face {
public:

    FaceT() {
    }

    FaceT(const UInt & A, const UInt & B, const UInt & C) {
        m_texture[0] = A;
        m_texture[1] = B;
        m_texture[2] = C;
    }

    ~FaceT() {
    }

    void setTexture(const UInt & A, const UInt & B, const UInt & C) {
        m_texture[0] = A;
        m_texture[1] = B;
        m_texture[2] = C;
    }

    int getTexture(int n) {
        return m_texture[n];
    }
private:
    UInt m_texture[3];
};

#endif
