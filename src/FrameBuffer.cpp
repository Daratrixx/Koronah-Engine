
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
}

void FrameBuffer::init() {
    m_idFrameBuffer = 0;
    m_idDepthBuffer = 0;
    m_colorBuffer = null;
    m_colorBufferCount = 0;
    m_width = DEFAULT_FRAMEBUFFER_WIDTH;
    m_height = DEFAULT_FRAMEBUFFER_HEIGHT;
    m_projection = glm::perspective(70.0, 4.0 / 3.0, 1.0, 100.0);
}
void FrameBuffer::init(const UInt & w, const UInt & h) {
    m_idFrameBuffer = 0;
    m_idDepthBuffer = 0;
    m_colorBuffer = null;
    m_colorBufferCount = 0;
    m_width = w;
    m_height = h;
    m_projection = glm::perspective(70.0, ((double) w / (double) h), 1.0, 100.0);
}

FrameBuffer::~FrameBuffer() {
    clear();
}

void FrameBuffer::clear() {
    if (glIsFramebuffer(m_idFrameBuffer) == GL_TRUE)
        glDeleteFramebuffers(1, &m_idFrameBuffer);
    if (glIsRenderbuffer(m_idDepthBuffer) == GL_TRUE)
        glDeleteRenderbuffers(1, &m_idDepthBuffer);
    for (unsigned int i = 0; i < m_colorBufferCount; i++) {
        delete m_colorBuffer[i];
    }
    if (m_colorBuffer != null)
        delete[] m_colorBuffer;
}

bool FrameBuffer::load() {
    clear();

    // frame buffer
    glGenFramebuffers(1, &m_idFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_idFrameBuffer);

    // depth buffer
    glGenRenderbuffers(1, &m_idDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_idDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // color buffers
    addColorBuffer(m_width, m_height); // world pass
    addColorBuffer(m_width, m_height); // bloom base pass
    addColorBuffer(m_width, m_height); // bloom H pass
    addColorBuffer(m_width, m_height); // bloom V pass
    for (unsigned int i = 0; i < m_colorBufferCount; i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorBuffer[i]->getID(), 0);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_idDepthBuffer);

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
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::changeColorAttachment(const UShort & colorID) const {
    GLenum drawBuffers0[] = {GL_COLOR_ATTACHMENT0};
    GLenum drawBuffers1[] = {GL_COLOR_ATTACHMENT1};
    GLenum drawBuffers2[] = {GL_COLOR_ATTACHMENT2};
    GLenum drawBuffers3[] = {GL_COLOR_ATTACHMENT3};
    GLenum drawBuffers4[] = {GL_COLOR_ATTACHMENT4};
    if (colorID < m_colorBufferCount) {
        switch (colorID) {
            case 1:
                glDrawBuffers(1, drawBuffers1);
                break;
            case 2:
                glDrawBuffers(1, drawBuffers2);
                break;
            case 3:
                glDrawBuffers(1, drawBuffers3);
                break;
            case 0:
                glDrawBuffers(1, drawBuffers4);
                break;
            default:
                glDrawBuffers(1, drawBuffers0);
                break;

        }
    } else {
        glDrawBuffers(1, drawBuffers0);
    }
}

void FrameBuffer::unUse() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addColorBuffer(const UInt & w, const UInt & h) {
    if (m_colorBufferCount < 16) {
        Texture* newTexture = new Texture();
        newTexture->chargerVide(w, h);
        Texture** temp = m_colorBuffer;
        m_colorBuffer = new Texture*[m_colorBufferCount + 1];
        for (UShort i = 0; i < m_colorBufferCount; i++)
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

GLuint FrameBuffer::getColorBufferId(const UShort & index) const {
    if (index < m_colorBufferCount)
        return m_colorBuffer[index]->getID();
    std::cout << "no color buffer at index " << index << std::endl;
    return m_colorBuffer[0]->getID();
}

Texture* FrameBuffer::getColorBuffer(const UShort & index) const {
    if (index < m_colorBufferCount)
        return m_colorBuffer[index];
    return null;
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





