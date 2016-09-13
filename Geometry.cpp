
#include "Geometry.h"

glm::vec3 getForwardVector(glm::vec3 angle) {
    float X,Y,Z;
    float phiRadian = angle.x * RADIAN;
    float thetaRadian = angle.y * RADIAN;
    X = cos(phiRadian) * sin(thetaRadian);
    Y = sin(phiRadian);
    Z = cos(phiRadian) * cos(thetaRadian);
    return glm::normalize(glm::vec3(X,Y,Z));
}

glm::vec3 getBackVector(glm::vec3 angle) {
    return -getForwardVector(angle);
}

glm::vec3 getLeftVector(glm::vec3 angle) {
    glm::vec3 left;
    glm::vec3 vertical(0,1,0);
    left = glm::cross(vertical,getForwardVector(angle));
    left = glm::normalize(left);
    return left;
}


glm::vec3 getRightVector(glm::vec3 angle) {
    return -getLeftVector(angle);
}

glm::vec3 getUpVector(glm::vec3 angle) {
    glm::vec3 up(glm::cross(getForwardVector(angle),getLeftVector(angle)));
    up = glm::normalize(up);
    return up;
}
glm::vec3 getDownVector(glm::vec3 angle) {
    return -getUpVector(angle);
}