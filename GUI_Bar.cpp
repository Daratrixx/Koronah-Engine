
#include "GUI.h"

GUI_Bar::GUI_Bar() : GUI() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_barMargin[GUI_MODE_COUNT] = glm::vec2(0, 0);
        m_barColor[GUI_MODE_COUNT] = glm::vec3(1, 1, 1);
    }
    m_barPercent = 0.5f;
    m_needLoadBar = true;
}

GUI_Bar::~GUI_Bar() {
}

void GUI_Bar::render(GraphicEngine* Graphic) {
    if (m_visible) {
        glDisable(GL_DEPTH_TEST);
        renderGUI(Graphic);
        renderBar(Graphic);
        renderChildren(Graphic);
        glEnable(GL_DEPTH_TEST);
    }
}

void GUI_Bar::renderBar(GraphicEngine* Graphic) {
    if (m_needLoadBar)
        loadBar();
    Graphic->m_shaderGUI->use();
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glUniform1i(glGetUniformLocation(Graphic->m_shaderGUI->getProgramID(), "hasTexture"), 0);
    glBindVertexArray(m_vaoBar[m_mode]);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    Graphic->m_shaderGUI->unUse();
}

void GUI_Bar::loadBar() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboBar[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboBar[i]);
        if (glIsVertexArray(m_vaoBar[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoBar[i]);
        float data[8];
        data[0] = ((m_position[i].x + m_barMargin[i].x) / Settings_getScreenWidth()) * 2 - 1;
        data[1] = ((m_position[i].y + m_barMargin[i].y) / Settings_getScreenHeight()) * 2 - 1;
        data[2] = (((m_size[i].x - m_barMargin[i].x * 2) * getBarPercent()) / Settings_getScreenWidth()) * 2;
        data[3] = ((m_size[i].y - m_barMargin[i].y * 2) / Settings_getScreenHeight()) * 2;
        glm::vec3 color = m_barColor[i];
        data[4] = color.x;
        data[5] = color.y;
        data[6] = color.z;
        data[7] = 1;
        // set buffer
        glGenBuffers(1, &m_vboBar[i]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboBar[i]);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof (float), 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof (float), data);
        glBindVertexArray(0);

        // set vertexArray
        glGenVertexArrays(1, &m_vaoBar[i]);
        glBindVertexArray(m_vaoBar[i]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboBar[i]);
        glVertexAttribPointer(SHADER_TEXTURE_LOCATION_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
        glVertexAttribPointer(SHADER_GUI_LOCATION_SIZE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_GUI_LOCATION_SIZE);
        glVertexAttribPointer(SHADER_GUI_LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(4 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_GUI_LOCATION_COLOR);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    m_needLoadBar = false;
}

void GUI_Bar::setBarPercent(float percent) {
    m_barPercent = percent;
    m_needLoadBar = true;
}

void GUI_Bar::setBarColor(glm::vec3 color) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++)
        m_barColor[i] = color;
    m_needLoadBar = true;
}

void GUI_Bar::setBarColor(float r, float g, float b) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++)
        m_barColor[i] = glm::vec3(r, g, b);
    m_needLoadBar = true;
}

void GUI_Bar::setBarColor(glm::vec3 color, unsigned int mode) {
    m_barColor[mode] = color;
    m_needLoadBar = true;
}

void GUI_Bar::setBarColor(float r, float g, float b, unsigned int mode) {
    m_barColor[mode] = glm::vec3(r, g, b);
    m_needLoadBar = true;
}

void GUI_Bar::setBarMargin(glm::vec2 margin) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++)
        m_barMargin[i] = margin;
    m_needLoadBar = true;
}

void GUI_Bar::setBarMargin(glm::vec2 margin, unsigned int mode) {
    m_barMargin[mode] = margin;
    m_needLoadBar = true;
}

void GUI_Bar::setBarMargin(float w, float h) {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++)
        m_barMargin[i] = glm::vec2(w, h);
    m_needLoadBar = true;
}

void GUI_Bar::setBarMargin(float w, float h, unsigned int mode) {
    m_barMargin[mode] = glm::vec2(w, h);
    m_needLoadBar = true;
}

float GUI_Bar::getBarPercent() {
    return m_barPercent;
}

glm::vec3 GUI_Bar::getBarColor() {
    return m_barColor[m_mode];
}

glm::vec3 GUI_Bar::getBarColor(unsigned int mode) {
    return m_barColor[mode];
}

glm::vec2 GUI_Bar::getBarMargin() {
    return m_barMargin[m_mode];
}

glm::vec2 GUI_Bar::getBarMargin(unsigned int mode) {
    return m_barMargin[mode];
}


