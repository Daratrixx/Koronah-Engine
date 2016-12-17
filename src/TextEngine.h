/* 
 * File:   TextEngine.h
 * Author: ANTOINE
 *
 * Created on 7 août 2016, 20:30
 */

#ifndef TEXTENGINE_H
#define	TEXTENGINE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef SETTINGS_H
#include "Settings.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif


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
    void writeLine(std::string line, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    float getLineWidth(std::string line, GLfloat scale);
    glm::vec2 getLineSize(std::string line, GLfloat scale);
    
private:
    FT_Library ft;
    FT_Face face;
    GLuint VAO, VBO;
    std::map<GLchar, Character> characters;
    Shader* s;
};

#endif	/* TEXTENGINE_H */

