#include "Camera.h"

// Permet d'éviter la ré-écriture du namespace glm::
using namespace glm;

// Constructeurs et Destructeur
Camera::Camera():
m_position(0,0,0), m_targetPoint(), m_orientation(), m_verticalAxe(0, 1, 0), m_angle(0,0,0)
{
    setAngle(m_angle);
    setProjection(70, 8.0/6.0, DEFAULT_SCREEN_NEAR, DEFAULT_SCREEN_FAR);
}

Camera::Camera(double fov, double ratio):
m_position(0,0,0), m_targetPoint(), m_orientation(), m_verticalAxe(0, 1, 0), m_angle(0,0,0)
{
    setAngle(m_angle);
    setProjection(fov, ratio, DEFAULT_SCREEN_NEAR, DEFAULT_SCREEN_FAR);
}

Camera::Camera(double fov, double ratio, double close, double far):
m_position(0,0,0), m_targetPoint(), m_orientation(), m_verticalAxe(0, 1, 0), m_angle(0,0,0)
{
    setAngle(m_angle);
    setProjection(fov, ratio, close, far);
}

Camera::~Camera() {

}

// Méthodes
void Camera::lookAt(glm::mat4 &modelview) {
    // Actualisation de la vue dans la matrice
    modelview = glm::lookAt(m_position, m_targetPoint, m_verticalAxe);
}

void Camera::setProjection(double fov, double ratio, double close, double far) {
    m_projection = glm::perspective(fov, ratio, close, far);
    m_fov = fov;
    m_ratio = ratio;
    m_close = close;
    m_far = far;
}

void Camera::setAngle(glm::vec3 angle) {
    // Récupération des angles
    this->m_angle=angle;

    // Limitation de l'angle phi
    if(m_angle.x > 89.9)
        m_angle.x = 89.9;
    else if(m_angle.x < -89.9)
        m_angle.x = -89.9;

    // Conversion des angles en radian
    float phiRadian = m_angle.x * M_PI / 180;
    float thetaRadian = m_angle.y * M_PI / 180;
    
    // Calcul des coordonnées sphériques
    m_orientation.x = cos(phiRadian) * sin(thetaRadian);
    m_orientation.y = sin(phiRadian);
    m_orientation.z = cos(phiRadian) * cos(thetaRadian);

    // Calcul du point ciblé pour OpenGL
    m_targetPoint = m_position + m_orientation;
    
    lookAt(m_view);
}
void Camera::setAngle(float x, float y, float z) {
    setAngle(glm::vec3(x,y,z));
}

void Camera::setTargetPoint(glm::vec3 pointCible) {
    // Calcul du vecteur orientation
    m_orientation = m_targetPoint - m_position;
    m_orientation = normalize(m_orientation);

    // Calcul des angles
    m_angle.x = asin(m_orientation.y);
    m_angle.y = acos(m_orientation.z / cos(m_angle.x));

    if(m_orientation.z < 0)
        m_angle.y *= -1;

    // Conversion en degrés
    m_angle.x = m_angle.x * 180 / M_PI;
    m_angle.y = m_angle.y * 180 / M_PI;
    
    lookAt(m_view);
}
void Camera::setTargetPoint(float x, float y, float z) {
    setTargetPoint(glm::vec3(x,y,z));
}

void Camera::setPosition(glm::vec3 position) {
    // Mise à jour de la position
    m_position = position;

    // Actualisation du point ciblé
    setTargetPoint(m_position + m_orientation);
}
void Camera::setPosition(float x, float y, float z) {
    setPosition(glm::vec3(x,y,z));
}

glm::vec3 Camera::getPosition() const {
    return m_position;
}
glm::vec3 Camera::getAngle() const {
    return m_angle;
}
glm::mat4 Camera::getProjectionMatrice() const {
    return m_projection;
}
glm::mat4 Camera::getViewMatrice() const {
    return m_view;
}
float Camera::getFOV() const {
    return m_fov;
}
float Camera::getRatio() const {
    return m_ratio;
}
float Camera::getClose() const {
    return m_close;
}
float Camera::getFar() const {
    return m_far;
}
