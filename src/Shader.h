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
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);
    void clean();
    bool compileAll();
    void loadAll();
    bool loadTexture(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadScan(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadText(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadParticle(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadGUI(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadScreen(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
    bool loadSquare(std::string vertexSource, std::string geometrySource, std::string fragmentSource);
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
