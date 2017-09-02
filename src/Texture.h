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
    bool chargerVide(const UInt & w, const UInt & h);
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

    UInt m_width, m_height;
    GLenum m_colors;
    GLenum m_format;
    bool m_isEmpty;
};

class TextureListHolder {
public:
    TextureListHolder();
    ~TextureListHolder();

    std::map<std::string, Texture*> textureList;
    std::vector<std::string> pathList;
};

GLuint loadTexture(const std::string & path);
Texture* textureExists(const std::string & path);
Texture* getTexture(const std::string & path);
Texture* getTexture(const UInt & index);
GLuint getTextureID(const std::string & path);
GLuint getTextureID(const UInt & index);
void clearTextureList();

#endif
