#pragma once

#ifndef SHADER_H
#define SHADER_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Shader {
public:
    Shader();
    Shader(const Shader & shaderACopier);
    ~Shader();

    Shader& operator=(const Shader & shaderACopier);
    void clean();
    bool compileAll();
    void loadAll();
    bool loadTexture(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadScan(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadText(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadParticle(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadGUI(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadScreen(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool loadSquare(const std::string & vertexSource, const std::string & geometrySource, const std::string & fragmentSource);
    bool compile(GLuint & shader, const GLenum & type, const std::string & fichierSource);
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
