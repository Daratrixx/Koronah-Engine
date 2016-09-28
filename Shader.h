#pragma once

#ifndef SHADER_H
#define SHADER_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Shader {
public:
    Shader();
    Shader(Shader const &shaderACopier);
    Shader(std::string vertexSource, std::string fragmentSource);
    Shader(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);
    void clean();
    bool compileAll();
    void loadAll();
    bool loadTexture();
    bool loadScan();
    bool loadText();
    bool loadParticle();
    bool loadGUI();
    bool loadScreen();
    bool loadSquare();
    bool compile(GLuint &shader, GLenum type, std::string const &fichierSource);
    bool link();
    GLuint getProgramID() const;
    void use() const;
    void unUse() const;

private:
    GLuint m_vertexID;
    GLuint m_geometryID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_geometrySource;
    std::string m_fragmentSource;
};


#endif
