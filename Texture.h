#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef TYPES_H
#include "Types.h"
#endif

// Classe Texture

class Texture {
public:
    Texture(std::string fichierImage);
    Texture();
    Texture(Texture const &textureACopier);
    Texture& operator=(Texture const &textureACopier);
    Texture& operator=(SDL_Surface* imageSDL);
    ~Texture();
    bool charger();
    bool charger(SDL_Surface* image);
    bool chargerVide(int w, int h);
    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);
    void setBlending(bool value);
    bool getBlending() const;
    std::string getPath();
    SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

private:
    GLuint m_id;
    std::string m_fichierImage;
    bool m_hasBlending;

    int m_width, m_height;
    GLenum m_colors;
    GLenum m_format;
    bool m_isEmpty;
};

std::vector<Texture*>* getTextureList();
GLuint loadTexture(std::string path);
Texture* textureExists(std::string path);
Texture* getTexture(unsigned int index);
GLuint getTextureID(unsigned int index);
void clearTextureList();

#endif
