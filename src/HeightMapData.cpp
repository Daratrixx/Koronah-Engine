
#include "HeightMapData.h"

Uint32 getPixelColor(SDL_Surface* surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *) p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *) p;

        default:
            return 0;
    }
}

HeightMapData::HeightMapData(std::string img) : GameObject() {
    loadHeightMapData(SDL_LoadBMP(img.c_str()));
}

HeightMapData::~HeightMapData() {
    delete m_pixel;
    //delete m_vertice;
    std::cout << "Deleted HeightMapData with ID " << m_objectId << std::endl;
}

void HeightMapData::loadHeightMapData(SDL_Surface *map) {
    float *temp(0);
    int i, j;
    Uint8 red, green, blue;
    Uint32 infopixel;

    m_x = map->w;
    m_y = map->h;
    m_pixel = new float[(m_x)*(m_y)];
    for (j = 0; j < m_y; j++) {
        for (i = 0; i < m_x; i++) {
            infopixel = getPixelColor(map, i, j);
            SDL_GetRGB(infopixel, map->format, &red, &green, &blue);
            setPixel(i, j, (red + green + blue) / 9);
        }
    }
    m_verticeCount = (m_x)*(m_y)*6;
    std::cout << "HeightMapData with " << m_verticeCount << " vertice." << std::endl;
    temp = new float[m_verticeCount * 3];
    float xStrafe, zStrafe;
    xStrafe = ((float) m_x) / -2.f;
    zStrafe = ((float) m_y) / -2.f;
    m_vertice = temp;
    for (j = 0; j < m_y; j++) {
        for (i = 0; i < m_x; i++) {
            *(temp) = i + xStrafe;
            *(temp + 1) = j + zStrafe;
            *(temp + 2) = getPixel(i, j);

            *(temp + 3) = i + 1.0 + xStrafe;
            *(temp + 4) = j + 1.0 + zStrafe;
            *(temp + 5) = getPixel(i + 1, j + 1);

            *(temp + 6) = i + xStrafe;
            *(temp + 7) = j + 1.0 + zStrafe;
            *(temp + 8) = getPixel(i, j + 1);

            *(temp + 9) = i + xStrafe;
            *(temp + 10) = j + zStrafe;
            *(temp + 11) = getPixel(i, j);

            *(temp + 12) = i + 1.0 + xStrafe;
            *(temp + 13) = j + zStrafe;
            *(temp + 14) = getPixel(i + 1, j);

            *(temp + 15) = i + 1.0 + xStrafe;
            *(temp + 16) = j + 1.0 + zStrafe;
            *(temp + 17) = getPixel(i + 1, j + 1);

            temp = temp + 18;
        }
    }
    SDL_FreeSurface(map);
}

int HeightMapData::getX() {
    return m_x;
}

int HeightMapData::getY() {
    return m_y;
}

int HeightMapData::getVerticeCount() {
    return m_verticeCount;
}

float HeightMapData::getPixel(int X, int Y) {
    if (X < 0 || X >= m_x || Y < 0 || Y >= m_y)
        return 0;
    return *(m_pixel + X + Y * m_x);
}

void HeightMapData::setPixel(int X, int Y, float value) {
    if (X >= 0 || X < m_x || Y >= 0 || Y < m_y)
        *(m_pixel + X + Y * m_x) = value;
    else
        std::cout << "Error generating heightmap setting point (" << X << "," << Y << ")" << std::endl;
}

float* HeightMapData::getVertice() {
    return m_vertice;
}

float HeightMapData::collision(glm::vec3 p) {
    glm::vec3 diff = p - getPositionXYZ();
    float x = diff.x + ((float) m_x) / 2;
    float y = diff.y + ((float) m_y) / 2;

    int ix = (int) x;
    int iy = (int) y;

    float dx = x - ix;
    float dy = y - iy;
    return ((1 - dx) * getPixel(ix, iy) + dx * getPixel(ix + 1, iy)) * (1 - dy)
            + ((1 - dx) * getPixel(ix, iy + 1) + dx * getPixel(ix + 1, iy + 1)) * dy;
}
