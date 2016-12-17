#include "Texture.h"

// Constructeur

Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage), m_hasBlending(false) {
    charger();
}

Texture::Texture() : m_id(0), m_fichierImage(""), m_hasBlending(false) {
}

Texture::Texture(Texture const &textureACopier) : m_hasBlending(false) {
    m_fichierImage = textureACopier.m_fichierImage;
    charger();
}

Texture& Texture::operator=(Texture const &textureACopier) {
    m_fichierImage = textureACopier.m_fichierImage;
    charger();
    return *this;
}

Texture& Texture::operator=(SDL_Surface* imageSDL) {
    // Copie de la texture
    charger(imageSDL);

    // Retour du pointeur *this
    return *this;
}
// Destructeur

Texture::~Texture() {
    // Destruction de la texture
    if (glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);
}

// Méthodes

bool Texture::charger() {
    // Chargement de l'image dans une surface SDL
    SDL_Surface *imageSDL = IMG_Load(m_fichierImage.c_str());
    if (imageSDL == 0) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        return false;
    }

    // Inversion de l'image
    SDL_Surface *imageInversee = inverserPixels(imageSDL);
    SDL_FreeSurface(imageSDL);

    // Destruction d'une éventuelle ancienne texture
    if (glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);

    // Génération de l'ID
    glGenTextures(1, &m_id);

    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Format de l'image
    GLenum formatInterne(0);
    GLenum format(0);

    // Détermination du format et du format interne pour les images à 3 composantes
    if (imageInversee->format->BytesPerPixel == 3) {
        // Format interne
        formatInterne = GL_RGB;

        // Format
        if (imageInversee->format->Rmask == 0xff)
            format = GL_RGB;
        else
            format = GL_BGR;
    }        // Détermination du format et du format interne pour les images à 4 composantes
    else if (imageInversee->format->BytesPerPixel == 4) {
        // Format interne
        formatInterne = GL_RGBA;

        // Format
        if (imageInversee->format->Rmask == 0xff)
            format = GL_RGBA;
        else
            format = GL_BGRA;
    }// Dans les autres cas, on arrête le chargement
    else {
        std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
        SDL_FreeSurface(imageInversee);
        return false;
    }

    // Copie des pixels
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);

    // Application des filtres
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);

    // Fin de la méthode
    SDL_FreeSurface(imageInversee);
    return true;
}

bool Texture::charger(SDL_Surface* imageSDL) {
    if (imageSDL == 0) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        return false;
    }

    // Inversion de l'image
    SDL_Surface *imageInversee = imageSDL;
    //SDL_Surface *imageInversee = inverserPixels(imageSDL);
    //SDL_FreeSurface(imageSDL);

    // Destruction d'une éventuelle ancienne texture
    if (glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);

    // Génération de l'ID
    glGenTextures(1, &m_id);

    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Format de l'image
    GLenum formatInterne(0);
    GLenum format(0);

    formatInterne = GL_RGB;
    // Format
    if (imageInversee->format->Rmask == 0xff)
        format = GL_RGB;
    else
        format = GL_BGR;

    // Copie des pixels
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);

    // Application des filtres
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);

    // Fin de la méthode
    SDL_FreeSurface(imageInversee);
    return true;
}

bool Texture::chargerVide(int w, int h) {
    m_width = w;
    m_height = h;
    // Destruction d'une éventuelle ancienne texture
    if (glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);

    // Génération de l'ID
    glGenTextures(1, &m_id);

    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Format de l'image
    GLenum formatInterne(GL_RGBA);
    GLenum format(GL_RGBA);

    // Copie des pixels
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, 0);

    // Application des filtres
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

GLuint Texture::getID() const {
    return m_id;
}

void Texture::setFichierImage(const std::string &fichierImage) {
    m_fichierImage = fichierImage;
}

void Texture::setBlending(bool value) {
    m_hasBlending = value;
}

bool Texture::getBlending() const {
    return m_hasBlending;
}

std::string Texture::getPath() {
    return m_fichierImage;
}

SDL_Surface* Texture::inverserPixels(SDL_Surface *imageSource) const {
    // Copie conforme de l'image source sans les pixels
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
            imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);

    // Tableau intermédiaires permettant de manipuler les pixels
    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;

    // Inversion des pixels
    for (int i = 0; i < imageSource->h; i++) {
        for (int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }

    // Retour de l'image inversée
    return imageInversee;
}

// static

std::vector<Texture*>* getTextureList() {
    static std::vector<Texture*>* TEXTURE_LIST = new std::vector<Texture*>();
    return TEXTURE_LIST;
}

GLuint loadTexture(std::string path) {
    Texture* texture = textureExists(path);
    if (texture == null) { // does not exist
        std::vector<Texture*>* TEXTURE_LIST = getTextureList();
        texture = new Texture(path);
        TEXTURE_LIST->push_back(texture);
        //std::cout << "loaded texture " << path << std::endl;
    }
    if(texture != null)
        return texture->getID();
    return 0;
}

Texture* textureExists(std::string path) {
    std::vector<Texture*>* TEXTURE_LIST = getTextureList();
    for (unsigned int i = 0; i < TEXTURE_LIST->size(); i++)
        if ((*TEXTURE_LIST)[i]->getPath() == path)
            return (*TEXTURE_LIST)[i];
    //std::cout << "can load texture " << path << std::endl;
    return null;
}

Texture* getTexture(unsigned int index) {
    std::vector<Texture*>* TEXTURE_LIST = getTextureList();
    if (index < TEXTURE_LIST->size())
        return (*TEXTURE_LIST)[index];
    //std::cout << "no texture at index " << index << " (" << TEXTURE_LIST->size() << ")" << std::endl;
    return null;
}

GLuint getTextureID(unsigned int index) {
    std::vector<Texture*>* TEXTURE_LIST = getTextureList();
    if (index < TEXTURE_LIST->size())
        return (*TEXTURE_LIST)[index]->getID();
    //std::cout << "no texture at index " << index << " (" << TEXTURE_LIST->size() << ")" << std::endl;
    return 0;
}

void clearTextureList() {
    std::vector<Texture*>* TEXTURE_LIST = getTextureList();
    for (unsigned int i = 0; i < TEXTURE_LIST->size(); i++)
        delete (*TEXTURE_LIST)[i];
    TEXTURE_LIST->clear();
}