/* 
 * File:   GraphicEngine.h
 * Author: ANTOINE
 *
 * Created on 15 février 2016, 11:27
 */
#pragma once

#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "Types.h"
#include "Settings.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "HeightMapData.h"
#include "GameObject.h"
#include "SortedKeyChain.hpp"
#include "TextEngine.h"
#include "FrameBuffer.h"
#include "Geometry.h"

class GraphicEngine {
public:
    GraphicEngine();
    void init();
    void init(const std::string & title);
    ~GraphicEngine();

    bool initWindow(const int & flags);
    bool initGL();
    void setLightData(float* lightData);
    void setWindowTitle(const std::string & title);
    void setResolution(const UInt & width, const UInt & height);

    UInt getWidth() const;
    UInt getHeight() const;
    float getRatio() const;

    void loadGraphicDatas();
    int createHeightMapModel(HeightMapData* data);

    void addToRender(GameObject* object);
    void startRender();
    void renderFrameBufferToScreen(FrameBuffer & frameBuffer, Shader & shader, unsigned int colorID);
    void renderFrameBufferToScreen(FrameBuffer & frameBuffer, Shader & shader, unsigned int colorID, bool isHorizontal);
    void renderPlayGround();
    void doColorPass();
    void doNormalPass();
    void doHaloPass();
    void doComposePass();

    // scan part
    void renderScanStart();
    void renderObjectScan(GameObject* object, int id);
    int getScanId(unsigned int x, unsigned int y);
    float getScanZ(unsigned int x, unsigned int y);
    glm::vec3 getUnprojectedPosition(unsigned int x, unsigned int y);
    void renderScanEnd();

    void renderSquare(glm::vec2 start, glm::vec2 end);
    void renderObjectTexture(GameObject* object);
    void renderObjectNormal(GameObject* object);
    void renderObjectHaloMap(GameObject* object);
    void renderModelTexture(Model* modelData, Texture* texture, glm::mat4 &model);
    void renderModelNormal(Model* modelData, glm::mat4 &model);
    void renderModelFrameBuffer(Model* modelData, Texture* texture, glm::mat4 &model);
    void renderParticle(glm::vec3* position, float* opacity, float* size, int count);
    void renderParticle(glm::vec3* position, float* opacity, float* size, int count, Texture* texture, glm::mat4 &view);
    void sendVerticeData(Model* model);
    void sendNormalData(Model* model);
    void sendTextureData(Model* model);
    void endRender();

    void writeLine(const std::string & line, const GLfloat & x, const GLfloat & y, const GLfloat & scale, const glm::vec3 & color);
    float getLineWidth(const std::string & line, const GLfloat & scale);
    glm::vec2 getLineSize(const std::string & line, const GLfloat & scale);

    void moveCamera(GameObject* object);
    float getCameraDistance(glm::vec3 position);

    Shader m_shaderModel;
    Shader m_shaderScan;
    Shader m_shaderParticle;
    Shader m_shaderGUI;
    Shader m_shaderSquare;
    Shader m_shaderScreen;
    Shader m_shaderHaloMap;
    Shader m_shaderNormal;

    GLuint m_screenVBO;
    GLuint m_screenVOA;

private:
    std::string m_title;
    UInt m_width;
    UInt m_height;
    float m_ratio;
    SDL_Window* m_window;
    SDL_GLContext m_contexteOpenGL;
    Camera m_camera;


    glm::mat4 m_projectionScene, m_projectionFrameBuffer;

    // rendering buffer
    SortedKeyChain m_playGroundObjectToRender;
    float* m_lightData;

    TextEngine* m_textEngine;
    FrameBuffer m_frameBufferColor;
    FrameBuffer m_frameBufferNormal;
    FrameBuffer m_frameBufferHalo;
    FrameBuffer_Scan m_frameBufferScan;

    GLuint m_squareVAO;
    GLuint m_squareVBO;
};


GraphicEngine* getGraphicEngine();

void setWindowTitle(const std::string & title);
void setResolution(const UInt & width, const UInt & height);
    
UInt getWidth();
UInt getHeight();
float getRatio();

void moveCamera(GameObject* object);
float getCameraDistance(glm::vec3 position);

void addToRender(GameObject* object);
void startRender();

#endif /* GRAPHICENGINE_H */

