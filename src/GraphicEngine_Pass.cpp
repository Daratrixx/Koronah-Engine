
#include "GraphicEngine.h"

void GraphicEngine::doColorPass() {
    glm::mat4 view = m_camera.getViewMatrice();
    m_frameBufferColor->use();
    m_shaderModel.use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel.getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    // render buffered objects
    KeyLink* current = m_playGroundObjectToRender->first;
    while (current != null) {
        renderObjectTexture((GameObject*) (current->value));
        current = current->next;
    }
    m_shaderModel.unUse();
    m_frameBufferColor->unUse();
}

void GraphicEngine::doNormalPass() {
    glm::mat4 view = m_camera.getViewMatrice();
    m_frameBufferNormal->use();
    m_shaderNormal.use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderNormal.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderNormal.getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    // render buffered objects
    KeyLink* current = m_playGroundObjectToRender->first;
    while (current != null) {
        renderObjectNormal((GameObject*) (current->value));
        current = current->next;
    }
    m_shaderNormal.unUse();
    m_frameBufferNormal->unUse();
}

void GraphicEngine::doHaloPass() {
    glm::mat4 view = m_camera.getViewMatrice();
    m_frameBufferHalo->use();
    m_shaderModel.use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel.getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    // render buffered objects
    KeyLink* current = m_playGroundObjectToRender->first;
    current = m_playGroundObjectToRender->first;
    glUniform3f(glGetUniformLocation(m_shaderModel.getProgramID(), "modelColor"), 1, 1, 1);
    while (current != null) {
        renderObjectHaloMap((GameObject*) (current->value));
        current = current->next;
    }
    m_shaderModel.unUse();
    m_frameBufferHalo->unUse();
}

void GraphicEngine::doComposePass() {
    renderFrameBufferToScreen(m_frameBufferColor, m_shaderScreen, 0); // add colors to screen
    renderFrameBufferToScreen(m_frameBufferNormal, m_shaderScreen, 0); // add normals to screen
    renderFrameBufferToScreen(m_frameBufferHalo, m_shaderHaloMap, 0); // add halos to screen
}



