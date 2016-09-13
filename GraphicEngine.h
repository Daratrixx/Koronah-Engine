/* 
 * File:   GraphicEngine.h
 * Author: ANTOINE
 *
 * Created on 15 février 2016, 11:27
 */
#pragma once

#ifndef GRAPHICENGINE_H
#define	GRAPHICENGINE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef CAMERA_H
#include "Camera.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

#ifndef MODEL_H
#include "Model.h"
#endif

#ifndef HEIGHTMAPDATA_H
#include "HeightMapData.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

#ifndef SORTEDKEYCHAIN_HPP
#include "SortedKeyChain.hpp"
#endif

#ifndef TEXTENGINE_H
#include "TextEngine.h"
#endif

#ifndef FRAMEBUFFER_H
#include "FrameBuffer.h"
#endif


class GraphicEngine {
public:
    GraphicEngine();
    GraphicEngine(std::string title, int width, int height);
    ~GraphicEngine();
    
    bool initWindow(int flags);
    bool initGL();
    void setLightData(float* lightData);
    void setWindowTitle(std::string title);
    void setResolution(int width, int height);
    
    int getWidth() const;
    int getHeight() const;
    float getRatio() const;

    void loadGraphicDatas();
    int createHeightMapModel(HeightMapData* data);
    
    void addToRender(GameObject* object);
    void startRender();
    void renderFrameBufferToScreen(FrameBuffer* frameBuffer, Shader* shader);
    void renderPlayGround();
    void renderObject(GameObject* object);
    void renderObjectHaloMap(GameObject* object);
    void renderModel(Model* modelData, Texture* texture, glm::mat4 &model);
    void renderModelFrameBuffer(Model* modelData, Texture* texture, glm::mat4 &model);
    void renderParticle(glm::vec3* position, float* opacity, float* size, int count);
    void renderParticle(glm::vec3* position, float* opacity, float* size, int count, Texture* texture, glm::mat4 &view);
    void sendVerticeData(Model* model);
    void sendNormalData(Model* model);
    void sendTextureData(Model* model);
    void endRender();
    
    void writeLine(std::string line, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    float getLineWidth(std::string line, GLfloat scale);
    glm::vec2 getLineSize(std::string line, GLfloat scale);
    
    void moveCamera(GameObject* object);
    float getCameraDistance(glm::vec3 position);
    
    Shader* m_shaderModel;
    Shader* m_shaderParticle;
    Shader* m_shaderGUI;
    Shader* m_shaderScreen;
    Shader* m_shaderHaloMap;
    
    GLuint vbo;
    GLuint vao;
    
private:
    std::string m_title;
    int m_width;
    int m_height;
    float m_ratio;
    SDL_Window* m_window;
    SDL_GLContext m_contexteOpenGL;
    Camera m_camera;

    
    glm::mat4 m_projectionScene, m_projectionFrameBuffer;
    
    // rendering buffer
    SortedKeyChain* m_playGroundObjectToRender;
    float* m_lightData;
    
    TextEngine* m_textEngine;
    FrameBuffer* m_frameBuffer;
};

#endif	/* GRAPHICENGINE_H */

