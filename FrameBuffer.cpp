
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
    m_idFrameBuffer = 0;
    m_idDepthBuffer = 0;
    m_colorBuffer = null;
    m_colorBufferCount = 0;
    m_width = DEFAULT_FRAMEBUFFER_WIDTH;
    m_height = DEFAULT_FRAMEBUFFER_HEIGHT;
    m_projection = glm::perspective(70.0, 4.0 / 3.0, 1.0, 100.0);
}

FrameBuffer::FrameBuffer(int w, int h) {
    m_idFrameBuffer = 0;
    m_idDepthBuffer = 0;
    m_colorBuffer = null;
    m_colorBufferCount = 0;
    m_width = w;
    m_height = h;
    m_projection = glm::perspective(70.0, ((double) w / (double) h), 1.0, 100.0);
}

FrameBuffer::~FrameBuffer() {
}

void FrameBuffer::clear() {
    if (glIsFramebuffer(m_idFrameBuffer) == GL_TRUE)
        glDeleteFramebuffers(1, &m_idFrameBuffer);
    std::cout << "1 clear ok" << std::endl;
    if (glIsRenderbuffer(m_idDepthBuffer) == GL_TRUE)
        glDeleteRenderbuffers(1, &m_idDepthBuffer);
    std::cout << "2 clear ok" << std::endl;
    for (unsigned int i = 0; i < m_colorBufferCount; i++) {
        delete m_colorBuffer[i];
    }
    std::cout << "3 clear ok" << std::endl;
    if (m_colorBuffer != null)
        delete[] m_colorBuffer;
}

bool FrameBuffer::load() {
    clear();
    
    std::cout << " -- clear ok" << std::endl;

    // frame buffer
    glGenFramebuffers(1, &m_idFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_idFrameBuffer);
    std::cout << " -- bind ok" << std::endl;

    // depth buffer
    glGenRenderbuffers(1, &m_idDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_idDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    std::cout << " -- depth ok" << std::endl;

    // color buffers
    addColorBuffer(m_width, m_height);
    for (unsigned int i = 0; i < m_colorBufferCount; i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorBuffer[i]->getID(), 0);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_idDepthBuffer);

    std::cout << " -- color ok" << std::endl;
    // unlock
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // check error
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        clear();
        std::cout << "Erreur : le FBO est mal construit" << std::endl;
        return false;
    }

    std::cout << "FrameBuffer ok" << std::endl;
    return true;
}

void FrameBuffer::use() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_idFrameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
}

void FrameBuffer::unUse() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addColorBuffer(int w, int h) {
    if (m_colorBufferCount < 16) {
        Texture* newTexture = new Texture();
        newTexture->chargerVide(w, h);
        Texture** temp = m_colorBuffer;
        m_colorBuffer = new Texture*[m_colorBufferCount + 1];
        for (unsigned int i = 0; i < m_colorBufferCount; i++)
            m_colorBuffer[i] = temp[i];
        m_colorBuffer[m_colorBufferCount] = newTexture;
        delete[] temp;
        m_colorBufferCount++;
    }
}

GLuint FrameBuffer::getFrameBufferId() const {
    return m_idFrameBuffer;
}

GLuint FrameBuffer::getDepthBufferId() const {
    return m_idDepthBuffer;
}

GLuint FrameBuffer::getColorBufferId(unsigned int index) const {
    if (index < m_colorBufferCount)
        return m_colorBuffer[index]->getID();
    return 0;
}

Texture* FrameBuffer::getColorBuffer(unsigned int index) const {
    if (index < m_colorBufferCount)
        return m_colorBuffer[index];
    return 0;
}

int FrameBuffer::getWidth() const {
    return m_width;
}

int FrameBuffer::getHeight() const {
    return m_height;
}

glm::mat4 FrameBuffer::getProjectionMatrice() const {
    return m_projection;
}





