#pragma once

#ifndef CUBE_H
#define CUBE_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef TEXTURE_H
#include "Texture.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

// Classe Cube
class Cube
{
    public:
    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);
    void charger();

    protected:
    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];

    GLuint m_vboID;
    int m_tailleVerticesBytes;
    int m_tailleCouleursBytes;
};


// Classe Caisse
class Caisse : public Cube
{
    public:
    Caisse(float taille, float repeat, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    ~Caisse();
    
    void afficher(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model);
    
    
    private:
    Texture m_texture;
    float m_coordTexture[72];
    int m_tailleTexturesBytes;
};

#endif
