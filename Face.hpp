#pragma once

#ifndef FACE_HPP
#define FACE_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

class Face {
    public:
        Face() {}
        Face(int A,int B,int C) {
            m_vertex[0]=A;
            m_vertex[1]=B;
            m_vertex[2]=C;
        }
        ~Face() {}
        
        void setVertex(int A,int B,int C) {
            m_vertex[0]=A;
            m_vertex[1]=B;
            m_vertex[2]=C;
        }
        int getVertex(int n) {
            return m_vertex[n];
        }
    private:
        int m_vertex[3];
};

class FaceT : public Face {
    public:
        FaceT() {}
        FaceT(int A,int B,int C) {
            m_texture[0]=A;
            m_texture[1]=B;
            m_texture[2]=C;
        }
        ~FaceT() {}
        
        void setTexture(int A,int B,int C) {
            m_texture[0]=A;
            m_texture[1]=B;
            m_texture[2]=C;
        }
        int getTexture(int n) {
            return m_texture[n];
        }
    private:
        int m_texture[3];
};

#endif
