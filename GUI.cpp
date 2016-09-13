
#include "GUI.h"

GUI::GUI() {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i] = glm::vec2(0, 0);
        m_size[i] = glm::vec2(0, 0);
        m_color[i] = glm::vec4(1, 1, 1, 1);

        m_vboID[i] = 0;
        m_vaoID[i] = 0;
    }
    m_parent = null;
    m_children = null;
    m_childrenCount = 0;
    m_textureID = 0;
    m_time = 0;
    m_visible = true;
    m_mode = 0;
}

GUI::~GUI() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboID[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboID[i]);
        if (glIsVertexArray(m_vaoID[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoID[i]);
    }
    clearChildren();
}

void GUI::render(GraphicEngine* Graphic) {
    if (m_visible) {
        glDisable(GL_DEPTH_TEST);
        renderGUI(Graphic->m_shaderGUI);
        renderChildren(Graphic);
        glEnable(GL_DEPTH_TEST);
    }
}

void GUI::renderGUI(Shader* shader) {
    if (m_needLoadVRAM)
        load();
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    shader->use();
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    if(m_textureID != 0)
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "hasTexture"), 1);
    else
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "hasTexture"), 0);
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(m_vaoID[m_mode]);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shader->unUse();
}

void GUI::renderChildren(GraphicEngine* Graphic) const {
    for (unsigned int i = 0; i < m_childrenCount; i++) {
        GUI* c = getChildAt(i);
        if (c != null)
            c->render(Graphic);
    }
}

void GUI::load() {
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboID[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboID[i]);
        if (glIsVertexArray(m_vaoID[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoID[i]);
        float data[8];
        data[0] = m_position[i].x;
        data[1] = m_position[i].y;
        data[2] = m_size[i].x;
        data[3] = m_size[i].y;
        data[4] = m_color[i].x;
        data[5] = m_color[i].y;
        data[6] = m_color[i].z;
        data[7] = m_color[i].w;
        // set buffer
        glGenBuffers(1, &m_vboID[i]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[i]);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof (float), 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof (float), data);
        glBindVertexArray(0);

        // set vertexArray
        glGenVertexArrays(1, &m_vaoID[i]);
        glBindVertexArray(m_vaoID[i]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[i]);
        glVertexAttribPointer(SHADER_INDEX_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(SHADER_INDEX_VERTEX);
        glVertexAttribPointer(SHADER_INDEX_GUI_SIZE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_INDEX_GUI_SIZE);
        glVertexAttribPointer(SHADER_INDEX_GUI_COLOR, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(4 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_INDEX_GUI_COLOR);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    m_needLoadVRAM = false;
}

void GUI::addChild(GUI* child) {
    if (child != null) {
        GUI** temp = m_children;
        m_children = new GUI*[m_childrenCount + 1];
        for (unsigned int i = 0; i < m_childrenCount; i++)
            m_children[i] = temp[i];
        m_children[m_childrenCount] = child;
        delete[] temp;
        m_childrenCount++;
    }
}

void GUI::removeChild(GUI* child) {
    if (m_childrenCount > 0 && child != null) {
        for (unsigned int i = 0; i < m_childrenCount; i++) {
            if (m_children[i] == child) {
                removeChildAt(i);
                break;
            }
        }
    }
}

void GUI::removeChildAt(unsigned int index) {
    if (index < m_childrenCount) {
        GUI** temp = m_children;
        m_children = new GUI*[m_childrenCount - 1];
        int offset = 0;
        for (unsigned int i = 0; i < m_childrenCount - 1; i++) {
            if (i == index)
                index = 1;
            m_children[i] = temp[i + offset];
        }
        delete[] temp;
        m_childrenCount--;
    }
}

void GUI::clearChildren() {
    for (unsigned int i = 0; i < m_childrenCount; i++)
        delete m_children[i];
    delete[] m_children;
    m_children = null;
    m_childrenCount = 0;
}

GUI* GUI::getParent() const {
    return m_parent;
}

GUI** GUI::getChildren() const {
    return m_children;
}

GUI* GUI::getChildAt(unsigned int index) const {
    if (index < m_childrenCount) {
        return m_children[index];
    }
    return null;
}

int GUI::getChildrenCount() const {
    return m_childrenCount;
}

glm::vec2 GUI::getPosition() const {
    return m_position[m_mode];
}

glm::vec2 GUI::getPosition(unsigned int mode) const {
    return m_position[mode];
}

glm::vec2 GUI::getSize() const {
    return m_size[m_mode];
}

glm::vec2 GUI::getSize(unsigned int mode) const {
    return m_size[mode];
}

glm::vec4 GUI::getColor() const {
    return m_color[m_mode];
}

glm::vec4 GUI::getColor(unsigned int mode) const {
    return m_color[mode];
}

GLuint GUI::getTextureID() const {
    return m_textureID;
}

bool GUI::getVisible() const {
    return m_visible;
}

void GUI::setParent(GUI* parent) {
    m_parent = parent;
}

void GUI::setChildren(GUI** children) {
    m_children = children;
}

void GUI::setPosition(glm::vec2 pos) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i] = pos;
    }
}

void GUI::setPosition(glm::vec2 pos, unsigned int mode) {
    m_needLoadVRAM = true;
    m_position[mode] = pos;
}

void GUI::setPosition(float x, float y) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i].x = x;
        m_position[i].y = y;
    }
}

void GUI::setPosition(float x, float y, unsigned int mode) {
    m_needLoadVRAM = true;
    m_position[mode].x = x;
    m_position[mode].y = y;
}

void GUI::setSize(glm::vec2 size) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_size[i] = size;
    }
}

void GUI::setSize(glm::vec2 size, unsigned int mode) {
    m_needLoadVRAM = true;
    m_size[mode] = size;
}

void GUI::setSize(float w, float h) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_size[i].x = w;
        m_size[i].y = h;
    }
}

void GUI::setSize(float w, float h, unsigned int mode) {
    m_needLoadVRAM = true;
    m_size[mode].x = w;
    m_size[mode].y = h;
}

void GUI::setColor(glm::vec4 color) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_color[i] = color;
    }
}

void GUI::setColor(glm::vec4 color, unsigned int mode) {
    m_needLoadVRAM = true;
    m_color[mode] = color;
}

void GUI::setColor(float r, float g, float b, float a) {
    m_needLoadVRAM = true;
    for (unsigned int i = 0; i < GUI_MODE_COUNT; i++) {
        m_color[i].x = r;
        m_color[i].y = g;
        m_color[i].z = b;
        m_color[i].w = a;
    }
}

void GUI::setColor(float r, float g, float b, float a, unsigned int mode) {
    m_needLoadVRAM = true;
    m_color[mode].x = r;
    m_color[mode].y = g;
    m_color[mode].z = b;
    m_color[mode].w = a;
}

void GUI::setTextureID(GLuint textureID) {
    m_textureID = textureID;
}

void GUI::setVisible(bool visible) {
    m_visible = visible;
}


void GUI::update(float time) {
    m_time += time;
    for(unsigned int i = 0; i < m_childrenCount; i++) {
        m_children[i]->update(time);
    }
}

GUI* GUI::tryClick(float x, float y) {
    if (cursorPositionIn(x, y)) {
        GUI* child = tryClickChildren(x, y);
        if (child == null) {
            onClick();
            return this;
        } else
            return child;
    } else
        return null;
}

GUI* GUI::tryClick(glm::vec2 pos) {
    return tryClick(pos.x, pos.y);
}

GUI* GUI::tryClickChildren(float x, float y) {
    for (unsigned int i = 0; i < m_childrenCount; i++) {
        GUI* child = getChildAt(i)->tryClick(x, y);
        if (child != null)
            return child;
    }
    return null;
}

GUI* GUI::tryClickChildren(glm::vec2 pos) {
    return tryClickChildren(pos.x, pos.y);
}

void GUI::tryHover(float x, float y) {
    if (cursorPositionIn(x, y)) {
        if (m_mode == GUI_NORMAL) {
            onCursorEnter();
            m_mode = GUI_HOVER;
        }
    } else {
        if (m_mode != GUI_NORMAL) {
            onCursorLeave();
            m_mode = GUI_NORMAL;
        }
    }
    tryHoverChildren(x, y);
}

void GUI::tryHover(glm::vec2 pos) {
    tryHover(pos.x, pos.y);
}

void GUI::tryHoverChildren(float x, float y) {
    for (unsigned int i = 0; i < m_childrenCount; i++) {
        getChildAt(i)->tryHover(x, y);
    }
}

void GUI::tryHoverChildren(glm::vec2 pos) {
    tryHoverChildren(pos.x, pos.y);
}

bool GUI::cursorPositionIn(float x, float y) {
    glm::vec2 start(m_position[m_mode].x, m_position[m_mode].y), end(m_position[m_mode].x + m_size[m_mode].x, m_position[m_mode].y + m_size[m_mode].y);
    return !(x < start.x || x > end.x || y < start.y || y > end.y);
}

bool GUI::cursorPositionIn(glm::vec2 pos) {
    return cursorPositionIn(pos.x, pos.y);
}

void GUI::onClick() {
    std::cout << "CLICK " << this;
    std::cout << " R " << (int) (m_color[m_mode].x * 255);
    std::cout << " G " << (int) (m_color[m_mode].y * 255);
    std::cout << " B " << (int) (m_color[m_mode].z * 255) << std::endl;
}

void GUI::onCursorEnter() {
    m_mode = GUI_HOVER;
}

void GUI::onCursorLeave() {
    m_mode = GUI_NORMAL;
}