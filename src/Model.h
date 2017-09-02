/* 
 * File:   Model.h
 * Author: ANTOINE
 *
 * Created on 11 septembre 2016, 15:27
 */
#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "Types.h"
#include "Shader.h"
#include "Texture.h"
#include "Shape.hpp"
#include "KeyFrame.hpp"
#include "String.h"
#include "HeightMapData.h"

class Model {
public:

    Model();
    virtual ~Model();

    void load();
    void initSize();
    std::string getPath();
    float* getVerticeData() const;
    float* getNormalData() const;
    float* getTextureData() const;
    glm::mat4* getAnimationModifierData() const;
    UInt getVerticeCount() const;
    UInt getVerticeSize() const;
    UInt getNormalSize() const;
    UInt getTextureSize() const;
    UInt getAnimationModifierSize() const;
    UInt getVerticeOffset() const;
    UInt getNormalOffset() const;
    UInt getTextureOffset() const;
    UInt getAnimationModifierOffset() const;
    GLuint getVboId() const;
    void useVbo();
    void unUseVbo();
    GLuint getVaoId() const;
    void useVao();
    void unUseVao();
    void drawUsingVao(Texture* t);

protected:
    std::string m_path;
    UInt m_verticeCount;
    
    std::vector<GLuint> m_colorTextureList;
    std::vector<GLuint> m_bumpmapTextureList;
    std::vector<GLuint> m_haloTextureList;
    
    float* m_verticeData;
    float* m_normalData;
    float* m_textureData;
    glm::mat4* m_animationModifierData;

    UInt m_verticeSize;
    UInt m_normalSize;
    UInt m_textureSize;
    UInt m_animationModifierSize;

    GLuint m_vboID;
    GLuint m_vaoID;
};

class ModelObj : public Model {
public:

    ModelObj();
    ModelObj(const std::string & file);
    virtual ~ModelObj();

    void loadObject(std::string &line);
    void loadVertexLine(std::string &line);
    void loadVertexNormalLine(std::string &line);
    void loadVertexTextureLine(std::string &line);
    void loadColorTexturePathLine(std::string &line);
    void loadHaloTexturePathLine(std::string &line);
    void loadBumpmapTexturePathLine(std::string &line);
    void loadFace(std::string &line);
    bool buildModel();

private:
    KeyFrame* m_keyFrame;
    Shape* m_shape;
};

class ModelHeightMap : public Model {
public:

    ModelHeightMap(int verticeCount, int width, int height, float* verticeData);
    ModelHeightMap(HeightMapData* heightMapData);
    virtual ~ModelHeightMap();

    void loadHeightMapData(int verticeCount, unsigned int width, unsigned int height, float* verticeData);

};

class ModelListHolder {
public:
    ModelListHolder();
    ~ModelListHolder();

    std::map<std::string, Model*> modelList;
    std::vector<std::string> pathList;
};

UInt loadModel(const std::string & path);
UInt addModel(Model* model);
bool modelExists(const std::string & path);
Model* getModel(std::string path);
Model* getModel(const UInt & index);
void clearModelList();

#endif /* MODEL_H */

