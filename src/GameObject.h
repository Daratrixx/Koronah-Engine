/* 
 * File:   GameObject.h
 * Author: ANTOINE
 *
 * Created on 29 mai 2016, 19:10
 */
#pragma once

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

#ifndef TYPES_H
#include "Types.h"
#endif

class GameObject {
    
public:
    GameObject();
    GameObject(GameObject* o);
    virtual ~GameObject();
    
    void setID(int id);
    int getID() const;
    
    void setParentObject(GameObject* parent);
    GameObject* getParentObject() const;
    
    /* 3D function */
    int getModelId() const;
    void setModelId(int modelId);
    int getTextureId() const;
    void setTextureId(int tectureId);
    int getHaloMapId() const;
    void setHaloMapId(int tectureId);
    
    
    void setPositionXYZ(float x, float y, float z);
    void setPositionXYZ(glm::vec3 pos);
    void setPositionXY(float x, float y);
    void setPositionXY(glm::vec2 pos);
    void setPositionX(float x);
    void setPositionY(float y);
    void setPositionZ(float z);
    glm::vec3 getPositionXYZ() const;
    glm::vec2 getPositionXY() const;
    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;
    void addPositionXYZ(float x, float y, float z);
    void addPositionXYZ(glm::vec3 pos);
    void addPositionXY(float x, float y);
    void addPositionXY(glm::vec2 pos);
    
    void setAngle(float x, float y, float z);
    void setAngle(glm::vec3 angle);
    glm::vec3 getAngle() const;
    void addAngle(float x, float y, float z);
    void addAngle(glm::vec3 angle);
    void correctAngle();
    
    void setScale(float x, float y, float z);
    void setScale(glm::vec3 pos);
    glm::vec3 getScale() const;
    void addScale(float x, float y, float z);
    void addScale(glm::vec3 pos);
    
    void setColor(float x, float y, float z);
    void setColor(glm::vec3 color);
    glm::vec3 getColor() const;
    
    void setTeamColor(float x, float y, float z);
    void setTeamColor(glm::vec3 color);
    glm::vec3 getTeamColor() const;
    
    glm::mat4 getVertexMatrice();
    glm::mat4 getNormalMatrice();
    
    
    int m_objectId;
    int m_modelId;
    int m_textureId;
    int m_haloMapId;
    std::string m_objectName;
    glm::vec2 m_position; // Z hauteur
    float m_depth;
    glm::vec3 m_angle; // Z rotation horizontal
    glm::vec3 m_scale;
    glm::vec3 m_color;
    glm::vec3 m_teamColor;
    
    static int OBJECT_COUNT;
    static int GET_NEXT_ID();
};

#endif	/* GAMEOBJECT_H */

