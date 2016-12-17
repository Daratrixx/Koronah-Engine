/* 
 * File:   FrameBuffer.h
 * Author: ANTOINE
 *
 * Created on 29 août 2016, 19:48
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

#ifndef TYPE_H
#include "Types.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

class FrameBuffer {
public:
    FrameBuffer();
    FrameBuffer(int w, int h);
    virtual ~FrameBuffer();
    
    void clear();
    virtual bool load();
    void use() const;
    void changeColorAttachment(unsigned int colorID) const;
    void unUse() const;
    
    void addColorBuffer(int w, int h);
    
    GLuint getFrameBufferId() const;
    GLuint getDepthBufferId() const;
    GLuint getColorBufferId(unsigned int index) const;
    Texture* getColorBuffer(unsigned int index) const;
    int getWidth() const;
    int getHeight() const;
    glm::mat4 getProjectionMatrice() const;

    
protected:
    GLuint m_idFrameBuffer;
    GLuint m_idDepthBuffer;
    Texture** m_colorBuffer;
    unsigned int m_colorBufferCount;
    int m_width, m_height;
    glm::mat4 m_projection;
};

class FrameBuffer_Scan : public FrameBuffer {
public:
    FrameBuffer_Scan();
    FrameBuffer_Scan(int w, int h);
    virtual ~FrameBuffer_Scan();
    
    virtual bool load();
    
    glm::vec3 getPixelColor(int x, int y);
    float getPixelDepth(int x, int y);
};

#endif	/* FRAMEBUFFER_H */

