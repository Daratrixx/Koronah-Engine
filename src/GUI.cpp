
#include "GUI.h"

GUI::GUI() {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i] = glm::vec2(0, 0);
        m_size[i] = glm::vec2(0, 0);
        m_color[i] = glm::vec4(1, 1, 1, 1);

        m_vboGUI[i] = 0;
        m_vaoGUI[i] = 0;
    }
    m_parent = null;
    m_children = null;
    m_childrenCount = 0;
    m_textureID = 0;
    m_time = 0;
    m_visible = true;
    m_displayColor = true;
    m_mode = GUI_NORMAL;
    m_positionType = GUI_POSITION_FIXED;
    m_sizeType = GUI_SIZE_FIXED;
}

GUI::~GUI() {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboGUI[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboGUI[i]);
        if (glIsVertexArray(m_vaoGUI[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoGUI[i]);
    }
    clearChildren();
}

void GUI::render(GraphicEngine* Graphic) {
    if (m_visible) {
        glDisable(GL_DEPTH_TEST);
        renderGUI(Graphic);
        renderChildren(Graphic);
        glEnable(GL_DEPTH_TEST);
    }
}

void GUI::renderGUI(GraphicEngine* Graphic) {
    if (m_displayColor) {
        if (m_needLoadGUI)
            loadGUI();
        Graphic->m_shaderGUI.use();
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        if (m_textureID != 0)
            glUniform1i(glGetUniformLocation(Graphic->m_shaderGUI.getProgramID(), "hasTexture"), 1);
        else
            glUniform1i(glGetUniformLocation(Graphic->m_shaderGUI.getProgramID(), "hasTexture"), 0);
        glBindVertexArray(m_vaoGUI[m_mode]);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        Graphic->m_shaderGUI.unUse();
    }
}

void GUI::renderChildren(GraphicEngine* Graphic) const {
    for (UShort i = 0; i < m_childrenCount; i++) {
        GUI* c = getChildAt(i);
        if (c != null)
            c->render(Graphic);
    }
}

void GUI::loadGUI() {
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        if (glIsBuffer(m_vboGUI[i]) == GL_TRUE)
            glDeleteBuffers(1, &m_vboGUI[i]);
        if (glIsVertexArray(m_vaoGUI[i]) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoGUI[i]);
        glm::vec2 position = getPosition(i);
        glm::vec2 size = getSize(i);
        float data[8];
        data[0] = (position.x / (float) getGraphicSetting()->screenWidth) * 2.f - 1;
        data[1] = (position.y / (float) getGraphicSetting()->screenHeight) * 2.f - 1;
        data[2] = (size.x / (float) getGraphicSetting()->screenWidth) * 2.f;
        data[3] = (size.y / (float) getGraphicSetting()->screenHeight) * 2.f;
        data[4] = m_color[i].x;
        data[5] = m_color[i].y;
        data[6] = m_color[i].z;
        data[7] = m_color[i].w;
        // set buffer
        glGenBuffers(1, &m_vboGUI[i]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboGUI[i]);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof (float), 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof (float), data);
        glBindVertexArray(0);

        // set vertexArray
        glGenVertexArrays(1, &m_vaoGUI[i]);
        glBindVertexArray(m_vaoGUI[i]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboGUI[i]);
        glVertexAttribPointer(SHADER_GUI_LOCATION_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(SHADER_GUI_LOCATION_VERTEX);
        glVertexAttribPointer(SHADER_GUI_LOCATION_SIZE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_GUI_LOCATION_SIZE);
        glVertexAttribPointer(SHADER_GUI_LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(4 * sizeof (float)));
        glEnableVertexAttribArray(SHADER_GUI_LOCATION_COLOR);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    m_needLoadGUI = false;
}

void GUI::addChild(GUI* child) {
    if (child != null) {
        GUI** temp = m_children;
        m_children = new GUI*[m_childrenCount + 1];
        for (UShort i = 0; i < m_childrenCount; i++)
            m_children[i] = temp[i];
        m_children[m_childrenCount] = child;
        delete[] temp;
        m_childrenCount++;
        child->setParent(this);
    }
}

void GUI::removeChild(GUI* child) {
    if (m_childrenCount > 0 && child != null) {
        for (UShort i = 0; i < m_childrenCount; i++) {
            if (m_children[i] == child) {
                removeChildAt(i);
                break;
            }
        }
    }
}

void GUI::removeChildAt(const UShort & index) {
    if (index < m_childrenCount) {
        GUI** temp = m_children;
        m_children = new GUI*[m_childrenCount - 1];
        UShort offset = 0;
        for (UShort i = 0; i < m_childrenCount - 1; i++) {
            if (i == index) {
                temp[i]->setParent(null);
                offset = 1;
            }
            m_children[i] = temp[i + offset];
        }
        delete[] temp;
        m_childrenCount--;
    }
}

void GUI::clearChildren() {
    for (UShort i = 0; i < m_childrenCount; i++)
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

GUI* GUI::getChildAt(const UShort & index) const {
    if (index < m_childrenCount) {
        return m_children[index];
    }
    return null;
}

UShort GUI::getChildrenCount() const {
    return m_childrenCount;
}

glm::vec2 GUI::getPosition() const {
    if (m_parent != null) {
        if (m_positionType == GUI_POSITION_RELATIVE)
            return m_position[m_mode] + m_parent->getPosition();
    }
    return m_position[m_mode];
}

glm::vec2 GUI::getPosition(const UShort & mode) const {
    if (m_parent != null) {
        if (m_positionType == GUI_POSITION_RELATIVE)
            return m_position[mode] + m_parent->getPosition();
    }
    return m_position[mode];
}

glm::vec2 GUI::getSize() const {
    if (m_parent != null) {
        if (m_sizeType == GUI_SIZE_RELATIVE)
            return m_size[m_mode] * m_parent->getSize();
    }
    return m_size[m_mode];
}

glm::vec2 GUI::getSize(const UShort & mode) const {
    if (m_parent != null) {
        if (m_sizeType == GUI_SIZE_RELATIVE)
            return m_size[mode] * m_parent->getSize();
    }
    return m_size[mode];
}

glm::vec4 GUI::getColor() const {
    return m_color[m_mode];
}

glm::vec4 GUI::getColor(const UShort & mode) const {
    return m_color[mode];
}

GLuint GUI::getTextureID() const {
    return m_textureID;
}

UShort GUI::getMode() const {
    return m_mode;
}

bool GUI::getVisible() const {
    return m_visible;
}

bool GUI::getDisplayColor() const {
    return m_displayColor;
}

void GUI::setParent(GUI* parent) {
    m_parent = parent;
    if (m_positionType != GUI_POSITION_FIXED || m_sizeType != GUI_POSITION_FIXED)
        m_needLoadGUI = true;
}

void GUI::setChildren(GUI** children) {
    m_children = children;
}

void GUI::setPosition(const glm::vec2 & pos) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i] = pos;
    }
}

void GUI::setPosition(const glm::vec2 & pos, const UShort & mode) {
    m_needLoadGUI = true;
    m_position[mode] = pos;
}

void GUI::setPosition(const float & x, const float & y) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_position[i].x = x;
        m_position[i].y = y;
    }
}

void GUI::setPosition(const float & x, const float & y, const UShort & mode) {
    m_needLoadGUI = true;
    m_position[mode].x = x;
    m_position[mode].y = y;
}

void GUI::setSize(const glm::vec2 & size) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_size[i] = size;
    }
}

void GUI::setSize(const glm::vec2 & size, const UShort & mode) {
    m_needLoadGUI = true;
    m_size[mode] = size;
}

void GUI::setSize(const float & w, const float & h) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_size[i].x = w;
        m_size[i].y = h;
    }
}

void GUI::setSize(const float & w, const float & h, const UShort & mode) {
    m_needLoadGUI = true;
    m_size[mode].x = w;
    m_size[mode].y = h;
}

void GUI::setColor(const glm::vec4 & color) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_color[i] = color;
    }
}

void GUI::setColor(const glm::vec4 & color, const UShort & mode) {
    m_needLoadGUI = true;
    m_color[mode] = color;
}

void GUI::setColor(const float & r, const float & g, const float & b, const float & a) {
    m_needLoadGUI = true;
    for (UShort i = 0; i < GUI_MODE_COUNT; i++) {
        m_color[i].x = r;
        m_color[i].y = g;
        m_color[i].z = b;
        m_color[i].w = a;
    }
}

void GUI::setColor(const float & r, const float & g, const float & b, const float & a, const UShort & mode) {
    m_needLoadGUI = true;
    m_color[mode].x = r;
    m_color[mode].y = g;
    m_color[mode].z = b;
    m_color[mode].w = a;
}

void GUI::setTextureID(const GLuint & textureID) {
    m_textureID = textureID;
}

void GUI::setMode(const UShort & mode) {
    m_mode = mode;
}

void GUI::setVisible(const bool & visible) {
    m_visible = visible;
}

void GUI::setDisplayColor(const bool & display) {
    m_displayColor = display;
}

void GUI::setPositionType(const UShort & type) {
    m_positionType = type;
}

void GUI::setSizeType(const UShort & type) {
    m_sizeType = type;
}

void GUI::update(const float & time) {
    m_time += time;
    for (UShort i = 0; i < m_childrenCount; i++) {
        m_children[i]->update(time);
    }
}

GUI* GUI::tryActive(const float & x, const float & y) {
    if (cursorPositionIn(x, y)) {
        GUI* child = tryActiveChildren(x, y);
        if (child == null) {
            m_mode = GUI_ACTIVE;
            return this;
        } else
            return child;
    } else
        return null;
}

GUI* GUI::tryActive(const glm::vec2 & pos) {
    return tryClick(pos.x, pos.y);
}

GUI* GUI::tryActiveChildren(const float & x, const float & y) {
    for (UShort i = 0; i < m_childrenCount; i++) {
        GUI* child = getChildAt(m_childrenCount - (i + 1))->tryActive(x, y);
        if (child != null)
            return child;
    }
    return null;
}

GUI* GUI::tryActiveChildren(const glm::vec2 & pos) {
    return tryActiveChildren(pos.x, pos.y);
}

GUI* GUI::tryClick(const float & x, const float & y) {
    GUI* child = tryClickChildren(x, y);
    if (child == null && m_mode == GUI_ACTIVE) {
        m_mode = GUI_NORMAL;
        tryHover(x, y);
        if (cursorPositionIn(x, y)) {
            onClick();
            return this;
        } else
            return null;
    }
    m_mode = GUI_NORMAL;
    tryHover(x, y);
    return child;
}

GUI* GUI::tryClick(const glm::vec2 & pos) {
    return tryClick(pos.x, pos.y);
}

GUI* GUI::tryClickChildren(const float & x, const float & y) {
    for (UShort i = 0; i < m_childrenCount; i++) {
        GUI* child = getChildAt(m_childrenCount - (i + 1))->tryClick(x, y);
        if (child != null)
            return child;
    }
    return null;
}

GUI* GUI::tryClickChildren(const glm::vec2 & pos) {
    return tryClickChildren(pos.x, pos.y);
}

void GUI::tryHover(const float & x, const float & y) {
    if (cursorPositionIn(x, y)) {
        if (m_mode == GUI_NORMAL) {
            onCursorEnter();
            m_mode = GUI_HOVER;
        }
    } else {
        if (m_mode == GUI_HOVER) {
            onCursorLeave();
            m_mode = GUI_NORMAL;
        }
    }
    tryHoverChildren(x, y);
}

void GUI::tryHover(const glm::vec2 & pos) {
    tryHover(pos.x, pos.y);
}

void GUI::tryHoverChildren(const float & x, const float & y) {
    for (UShort i = 0; i < m_childrenCount; i++) {
        getChildAt(m_childrenCount - (i + 1))->tryHover(x, y);
    }
}

void GUI::tryHoverChildren(const glm::vec2 & pos) {
    tryHoverChildren(pos.x, pos.y);
}

bool GUI::cursorPositionIn(const float & x, const float & y) {
    if (!m_visible)
        return false;
    glm::vec2 pos = getPosition();
    glm::vec2 size = getSize();
    glm::vec2 start(pos.x, pos.y), end(pos.x + size.x, pos.y + size.y);
    return !(x < start.x || x > end.x || y < start.y || y > end.y);
}

bool GUI::cursorPositionIn(const glm::vec2 & pos) {
    return cursorPositionIn(pos.x, pos.y);
}

void GUI::onClick() {
    /*std::cout << "CLICK " << this;
    std::cout << " R " << (int) (m_color[m_mode].x * 255);
    std::cout << " G " << (int) (m_color[m_mode].y * 255);
    std::cout << " B " << (int) (m_color[m_mode].z * 255) << std::endl;*/
}

void GUI::onCursorEnter() {
    m_mode = GUI_HOVER;
}

void GUI::onCursorLeave() {
    m_mode = GUI_NORMAL;
}