
#include "GraphicEngine.h"

void GraphicEngine::addToRender(GameObject* object) {
    float maxDistance = m_camera.getFar();
    float minDistance = m_camera.getClose();
    float distance = getCameraDistance(object->getPositionXYZ());
    if (distance < maxDistance && distance > minDistance)
        m_playGroundObjectToRender->add(distance, (void*) object);
}

void GraphicEngine::startRender() {
    glClearColor(0.3f, 0, 0.3f, 1);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicEngine::renderFrameBufferToScreen(FrameBuffer* frameBuffer, Shader* shader, unsigned int colorID) {
    glViewport(0, 0, m_width, m_height);
    glDisable(GL_DEPTH_TEST);
    shader->use();
    glBindVertexArray(m_screenVOA);
    glBindTexture(GL_TEXTURE_2D, frameBuffer->getColorBufferId(colorID));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    shader->unUse();
    glEnable(GL_DEPTH_TEST);
}

void GraphicEngine::renderFrameBufferToScreen(FrameBuffer* frameBuffer, Shader* shader, unsigned int colorID, bool isHorizontal) {
    glDisable(GL_DEPTH_TEST);
    shader->use();
    if (isHorizontal)
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "isHorizontal"), 1);
    else
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "isHorizontal"), 0);
    glBindVertexArray(m_screenVOA);
    glBindTexture(GL_TEXTURE_2D, frameBuffer->getColorBufferId(colorID));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    shader->unUse();
    glEnable(GL_DEPTH_TEST);
}

void GraphicEngine::renderPlayGround() {
    // CLEAR SCREEN
    glClearColor(0, 0, 0, 0);
    
    // COLOR PASS (0)
    doColorPass();
    
    // NORMAL PASS (0)
    doNormalPass();
    
    // HALO PASS (1)
    doHaloPass();
    // HALO PASS (1 to 2)
    //m_frameBuffer->changeColorAttachment(2);
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderHaloMap, 0, true);
    // HALO PASS (2 to 3)
    //m_frameBuffer->changeColorAttachment(3);
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderHaloMap, 0, false);

    // screen render
    doComposePass();
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 1); // add halo to scree
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 2); // add halo to screem
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 3); // add halo to screem
}

void GraphicEngine::renderSquare(glm::vec2 start, glm::vec2 end) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    m_shaderSquare->use();
    GLfloat vertices[4 * 2] = {
        (start.x / m_width) * 2 - 1, (start.y / m_height) * 2 - 1,
        (end.x / m_width) * 2 - 1, (start.y / m_height) * 2 - 1,
        (end.x / m_width) * 2 - 1, (end.y / m_height) * 2 - 1,
        (start.x / m_width) * 2 - 1, (end.y / m_height) * 2 - 1
    };
    glBindVertexArray(m_squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_squareVAO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    m_shaderSquare->unUse();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GraphicEngine::renderObjectTexture(GameObject* object) {
    int idModel(object->getModelId());
    int idTexture(object->getTextureId());
    if (idModel > -1 && idTexture > -1) {
        glm::mat4 model = object->getVertexMatrice();
        Model* modelData = getModel(idModel);
        Texture* textureData = getTexture(idTexture);
        if (modelData != null && textureData != null) {
            glUniform3f(glGetUniformLocation(m_shaderModel->getProgramID(), "modelColor"), object->getColor().x, object->getColor().y, object->getColor().z);
            renderModelTexture(modelData, textureData, model);
        }
    }
}

void GraphicEngine::renderObjectNormal(GameObject* object) {
    int idModel(object->getModelId());
    if (idModel > -1) {
        glm::mat4 model = object->getVertexMatrice();
        glm::mat4 normal = object->getNormalMatrice();
        Model* modelData = getModel(idModel);
        if (modelData != null) {
            renderModelNormal(modelData, model, normal);
        }
    }
}

void GraphicEngine::renderObjectHaloMap(GameObject* object) {
    int idModel(object->getModelId());
    int idHaloMap(object->getHaloMapId());
    if (idModel > -1 && idHaloMap > -1) {
        glm::mat4 model = object->getVertexMatrice();
        Model* modelData = getModel(idModel);
        Texture* textureData = getTexture(idHaloMap);
        if (modelData != null && textureData != null) {
            glUniform3f(glGetUniformLocation(m_shaderModel->getProgramID(), "modelColor"), object->getTeamColor().x, object->getTeamColor().y, object->getTeamColor().z);
            renderModelTexture(modelData, textureData, model);
        }
    }
}

void GraphicEngine::renderModelTexture(Model* modelData, Texture* textureData, glm::mat4 &model) {
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    modelData->drawUsingVao(m_shaderModel, textureData);
}

void GraphicEngine::renderModelNormal(Model* modelData, glm::mat4 &model, glm::mat4 &normal) {
    glUniformMatrix4fv(glGetUniformLocation(m_shaderNormal->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderNormal->getProgramID(), "normal"), 1, GL_FALSE, glm::value_ptr(normal));
    modelData->drawUsingVao(m_shaderNormal, null);
}

void GraphicEngine::renderParticle(glm::vec3* position, float* opacity, float* size, int count) {
    glm::mat4 view = m_camera.getViewMatrice();
    renderParticle(position, opacity, size, count, getTexture(4), view);
}

void GraphicEngine::renderParticle(glm::vec3* position, float* opacity, float* size, int count, Texture* texture, glm::mat4 &view) {

    // PROGRAM
    m_shaderParticle->use();

    // PRIMITIVES
    glVertexAttribPointer(SHADER_TEXTURE_LOCATION_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, position);
    glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
    glVertexAttribPointer(SHADER_PARTICLE_LOCATION_OPACITY, 1, GL_FLOAT, GL_FALSE, 0, opacity);
    glEnableVertexAttribArray(SHADER_PARTICLE_LOCATION_OPACITY);
    glVertexAttribPointer(SHADER_PARTICLE_LOCATION_SIZE, 1, GL_FLOAT, GL_FALSE, 0, size);
    glEnableVertexAttribArray(SHADER_PARTICLE_LOCATION_SIZE);

    // UNIFORMS
    glUniformMatrix4fv(glGetUniformLocation(m_shaderParticle->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderParticle->getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    //TEXTURE
    if (texture != null)
        glBindTexture(GL_TEXTURE_2D, texture->getID());

    //RENDER
    glDrawArrays(GL_POINTS, 0, count);

    if (texture != null)
        glBindTexture(GL_TEXTURE_2D, 0);

    // Désactivation des tableaux
    glDisableVertexAttribArray(SHADER_PARTICLE_LOCATION_SIZE);
    glDisableVertexAttribArray(SHADER_PARTICLE_LOCATION_OPACITY);
    glDisableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
    // Désactivation du shader
    m_shaderParticle->unUse();
}

void GraphicEngine::endRender() {
    SDL_GL_SwapWindow(m_window);
    m_playGroundObjectToRender->clear();
}
