/* 
 * File:   FrameBuffer.h
 * Author: ANTOINE
 *
 * Created on 29 août 2016, 19:48
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#ifndef TYPE_H
#include "Types.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

class FrameBuffer {
public:
    FrameBuffer();
    void init();
    void init(const UInt & w, const UInt & h);
    virtual ~FrameBuffer();

    void clear();
    virtual bool load();
    void use() const;
    void changeColorAttachment(const UShort & colorID) const;
    void unUse() const;

    void addColorBuffer(const UInt & w, const UInt & h);

    GLuint getFrameBufferId() const;
    GLuint getDepthBufferId() const;
    GLuint getColorBufferId(const UShort & index) const;
    Texture* getColorBuffer(const UShort & index) const;
    int getWidth() const;
    int getHeight() const;
    glm::mat4 getProjectionMatrice() const;


protected:
    GLuint m_idFrameBuffer;
    GLuint m_idDepthBuffer;
    Texture** m_colorBuffer;
    UShort m_colorBufferCount;
    UInt m_width, m_height;
    glm::mat4 m_projection;
};

class FrameBuffer_Scan : public FrameBuffer {
public:
    FrameBuffer_Scan();
    FrameBuffer_Scan(const UInt & w, const UInt & h);
    virtual ~FrameBuffer_Scan();

    virtual bool load();

    glm::vec3 getPixelColor(const UInt & x, const UInt & y);
    float getPixelDepth(const UInt & x, const UInt & y);
};

#endif /* FRAMEBUFFER_H */

