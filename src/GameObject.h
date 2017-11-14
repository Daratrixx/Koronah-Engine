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

#include "Serializable.h"

class GameObject : public Serializable {
    
public:
    GameObject();
    GameObject(GameObject* o);
    virtual ~GameObject();
    virtual bool writeInFile(std::ofstream & fout);
    virtual bool readFromFile(std::ifstream & fin);
    
    void setID(const UInt & id);
    UInt getID() const;
    
    void setParentObject(GameObject* parent);
    GameObject* getParentObject() const;
    
    /* 3D function */
    UInt getModelId() const;
    void setModelId(const UInt & modelId);
    UInt getTextureId() const;
    void setTextureId(const UInt & tectureId);
    UInt getHaloMapId() const;
    void setHaloMapId(const UInt & tectureId);
    
    
    void setPositionXYZ(const float & x, const float & y, const float & z);
    void setPositionXYZ(const glm::vec3 & pos);
    void setPositionXY(const float & x, const float & y);
    void setPositionXY(const glm::vec2 & pos);
    void setPositionX(const float & x);
    void setPositionY(const float & y);
    void setPositionZ(const float & z);
    glm::vec3 getPositionXYZ() const;
    glm::vec2 getPositionXY() const;
    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;
    void addPositionXYZ(const float & x, const float & y, const float & z);
    void addPositionXYZ(const glm::vec3 & pos);
    void addPositionXY(const float & x, const float & y);
    void addPositionXY(const glm::vec2 & pos);
    
    void setAngle(const float & x, const float & y, const float & z);
    void setAngle(const glm::vec3 & angle);
    glm::vec3 getAngle() const;
    void addAngle(const float & x, const float & y, const float & z);
    void addAngle(const glm::vec3 & angle);
    void correctAngle();
    
    void setScale(const float & x, const float & y, const float & z);
    void setScale(const glm::vec3 & pos);
    glm::vec3 getScale() const;
    void addScale(const float & x, const float & y, const float & z);
    void addScale(const glm::vec3 & pos);
    
    void setColor(const float & x, const float & y, const float & z);
    void setColor(const glm::vec3 & color);
    glm::vec3 getColor() const;
    
    void setTeamColor(const float & x, const float & y, const float & z);
    void setTeamColor(const glm::vec3 & color);
    glm::vec3 getTeamColor() const;
    
    glm::mat4 getVertexMatrice();
    glm::mat4 getCircleMatrice();
    
    
    UInt m_objectId;
    UInt m_modelId;
    UInt m_textureId;
    UInt m_haloMapId;
    std::string m_objectName;
    glm::vec2 m_position; // Z hauteur
    float m_depth;
    glm::vec3 m_angle; // Z rotation horizontal
    glm::vec3 m_scale;
    glm::vec3 m_color;
    glm::vec3 m_teamColor;
    
    bool m_selectionCircleDisplayed;
    glm::vec3 m_selectionCircleColor;
    float m_selectionCircleRadius;
    
    static UInt OBJECT_COUNT;
    static UInt GET_NEXT_ID();
};

#endif	/* GAMEOBJECT_H */

