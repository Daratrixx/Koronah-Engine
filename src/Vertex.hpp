#pragma once

#ifndef VERTEX_HPP
#define VERTEX_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

class VertexData {
public:

    VertexData() {
    }

    VertexData(const float & x, const float & y, const float & z) {
        m_cord[0] = x;
        m_cord[1] = y;
        m_cord[2] = z;
    }

    ~VertexData() {
    }

    VertexData sub(VertexData v) {
        VertexData out(m_cord[0] - v.getPos(0), m_cord[1] - v.getPos(1), m_cord[2] - v.getPos(2));
        return out;
    }

    VertexData cross(VertexData v) {
        float nx, ny, nz;
        nx = m_cord[1] * v.getPos(2) - m_cord[2] * v.getPos(1);
        ny = m_cord[2] * v.getPos(0) - m_cord[0] * v.getPos(2);
        nz = m_cord[0] * v.getPos(1) - m_cord[1] * v.getPos(0);
        VertexData out(nx, ny, nz);
        return out;
    }

    void setPos(const float & x, const float & y, const float & z) {
        m_cord[0] = x;
        m_cord[1] = y;
        m_cord[2] = z;
    }

    float getPos(UShort n) const {
        return m_cord[n];
    }

private:
    float m_cord[3];
};

class TextureData {
public:

    TextureData() {
    }

    TextureData(const float & x, const float & y) {
        m_cord[0] = x;
        m_cord[1] = y;
    }

    ~TextureData() {
    }

    void setPos(const float & x, const float & y) {
        m_cord[0] = x;
        m_cord[1] = y;
    }

    float getPos(UShort n) const {
        return m_cord[n];
    }

private:
    float m_cord[2];
};

#endif
