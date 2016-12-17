/* 
 * File:   Model.h
 * Author: ANTOINE
 *
 * Created on 11 septembre 2016, 15:27
 */
#pragma once

#ifndef MODEL_H
#define	MODEL_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

#ifndef SHAPE_HPP
#include "Shape.hpp"
#endif

#ifndef KEYFRAME_HPP
#include "KeyFrame.hpp"
#endif

#ifndef STRING_H
#include "String.h"
#endif

#ifndef HEIGHTMAPDATA_H
#include "HeightMapData.h"
#endif

class Model {
public:

    Model();

    virtual ~Model();

    void load();
    void initSize();
    float* getVerticeData() const;
    float* getNormalData() const;
    float* getTextureData() const;
    glm::mat4* getAnimationModifierData() const;
    int getVerticeCount() const;
    int getVerticeSize() const;
    int getNormalSize() const;
    int getTextureSize() const;
    int getAnimationModifierSize() const;
    int getVerticeOffset() const;
    int getNormalOffset() const;
    int getTextureOffset() const;
    int getAnimationModifierOffset() const;
    GLuint getVboId() const;
    void useVbo();
    void unUseVbo();
    GLuint getVaoId() const;
    void useVao();
    void unUseVao();
    void drawUsingVao(Texture* t);
    
protected:
    int m_verticeCount;

    float* m_verticeData;
    float* m_normalData;
    float* m_textureData;
    glm::mat4* m_animationModifierData;

    int m_verticeSize;
    int m_normalSize;
    int m_textureSize;
    int m_animationModifierSize;

    GLuint m_vboID;
    GLuint m_vaoID;
};

class ModelObj : public Model {
public:

    ModelObj();
    ModelObj(std::string file);
    virtual ~ModelObj();

    void loadObject(std::string &line);
    void loadVertexLine(std::string &line);
    void loadNormalLine(std::string &line);
    void loadTextureLine(std::string &line);
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

std::vector<Model*>* getModelList();
unsigned int loadModel(std::string path);
unsigned int addModel(Model* model);
Model* modelExists(std::string path);
Model* getModel(unsigned int index);
void clearModelList();

#endif	/* MODEL_H */

