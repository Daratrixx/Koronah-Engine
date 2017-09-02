/* 
 * File:   TextEngine.h
 * Author: ANTOINE
 *
 * Created on 7 août 2016, 20:30
 */

#ifndef TEXTENGINE_H
#define	TEXTENGINE_H

#include "Types.h"
#include "Settings.h"
#include "Shader.h"
#include "Settings.h"


typedef struct {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
} Character;

class TextEngine {
public:
    TextEngine();
    ~TextEngine();
    void writeLine(const std::string & line, const GLfloat & x, const GLfloat & y, const GLfloat & scale, const glm::vec3 & color);
    float getLineWidth(const std::string & line, const GLfloat & scale);
    glm::vec2 getLineSize(const std::string & line, const GLfloat & scale);
    
private:
    FT_Library ft;
    FT_Face face;
    GLuint VAO, VBO;
    std::map<GLchar, Character> characters;
    Shader s;
};


TextEngine* getTextEngine();
void writeLine(const std::string & line, const GLfloat & x, const GLfloat & y, const GLfloat & scale, const glm::vec3 & color);
float getLineWidth(const std::string & line, const GLfloat & scale);
glm::vec2 getLineSize(const std::string & line, const GLfloat & scale);

#endif	/* TEXTENGINE_H */

