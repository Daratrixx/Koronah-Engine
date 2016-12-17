
#include "GraphicEngine.h"

void GraphicEngine::renderScanStart() {
    glm::mat4 view = m_camera.getViewMatrice();
    glClearColor(0, 0, 1, 1);
    m_frameBufferScan->use();
    m_shaderScan->use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderScan->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderScan->getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
}

void GraphicEngine::renderObjectScan(GameObject* object, int unitId) {
    int idModel(object->getModelId());
    int idTexture(object->getTextureId());
    if (idModel > -1 && idTexture > -1) {
        glm::mat4 model = object->getVertexMatrice();
        Model* modelData = getModel(idModel);
        if (modelData != null) {
            glUniformMatrix4fv(glGetUniformLocation(m_shaderScan->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(glGetUniformLocation(m_shaderScan->getProgramID(), "unitId"), unitId);
            modelData->drawUsingVao(m_shaderScan, null);
        }
    }
}

int GraphicEngine::getScanId(unsigned int x, unsigned int y) {
    glm::vec3 color = m_frameBufferScan->getPixelColor(x, y);
    if (color.z > 1)
        return -1;
    std::cout << color.x << " " << color.y << " " << color.z << std::endl;
    return color.x * 255 + color.y;
}

float GraphicEngine::getScanZ(unsigned int x, unsigned int y) {
    return m_frameBufferScan->getPixelDepth(x, y);
}

glm::vec3 GraphicEngine::getUnprojectedPosition(unsigned int x, unsigned int y) {
    glm::vec3 pos(x, y, m_frameBufferScan->getPixelDepth(x, y));
    glm::vec4 viewport(0, 0, m_width, m_height);
    
    return glm::unProject(pos, m_camera.getViewMatrice(), m_camera.getProjectionMatrice(), viewport);
}

void GraphicEngine::renderScanEnd() {
    m_shaderScan->unUse();
    m_frameBufferScan->unUse();
    renderFrameBufferToScreen(m_frameBufferScan, m_shaderScreen, 0); // add world to screnm
}

