
#include "Geometry.h"

glm::vec3 getForwardVector(glm::vec3 angle) {
    float X, Y, Z;
    float phiRadian = angle.x * RADIAN;
    float thetaRadian = angle.y * RADIAN;
    X = cos(phiRadian) * cos(thetaRadian);
    Y = cos(phiRadian) * sin(thetaRadian);
    Z = sin(phiRadian);
    return glm::normalize(glm::vec3(X, Y, Z));
}

glm::vec3 getBackVector(glm::vec3 angle) {
    return -getForwardVector(angle);
}

glm::vec3 getLeftVector(glm::vec3 angle) {
    glm::vec3 left;
    glm::vec3 vertical(0, 0, 1);
    left = glm::cross(vertical, getForwardVector(angle));
    left = glm::normalize(left);
    return left;
}

glm::vec3 getRightVector(glm::vec3 angle) {
    return -getLeftVector(angle);
}

glm::vec3 getUpVector(glm::vec3 angle) {
    glm::vec3 up(glm::cross(getForwardVector(angle), getLeftVector(angle)));
    up = glm::normalize(up);
    return up;
}

glm::vec3 getDownVector(glm::vec3 angle) {
    return -getUpVector(angle);
}



bool isPointInRectangle(glm::vec2 point, glm::vec2 center, glm::vec2 size) {
    if(point.x < center.x-size.x || point.x > center.x+size.x
            || point.y < center.y-size.y || point.y > center.y+size.y)
        return false;
    return true;
}

bool isPointInCircle(glm::vec2 point, glm::vec2 center, float radius) {
    return glm::length(point-center)<radius;
}

bool isPointInPolygon(glm::vec2 tab[], unsigned int nbp, glm::vec2 P) {
    //nbp = ARRAY_SIZE((*tab));
    for (unsigned int i = 0; i < nbp; i++) {
        glm::vec2 A = tab[i];
        glm::vec2 B;
        if (i == nbp - 1) // si c'est le dernier point, on relie au premier
            B = tab[0];
        else // sinon on relie au suivant.
            B = tab[i + 1];
        glm::vec2 D, T;
        D = B - A;
        T = P - A;
        float d = D.x * T.y - D.y * T.x;
        if (d < 0)
            return false; // un point à droite et on arrête tout.
    }
    return true; // si on sort du for, c'est qu'aucun point n'est à gauche, donc c'est bon.
}

glm::vec2 positionAlongLine(glm::vec2 origin, glm::vec2 destination, float distance) {
    glm::vec2 direction = destination - origin;
    return origin + glm::normalize(direction) * distance;
}