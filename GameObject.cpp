
#include "GameObject.h"


int GameObject::OBJECT_COUNT = 0;

int GameObject::GET_NEXT_ID() {
    return OBJECT_COUNT++;
}

GameObject::GameObject() {
    m_parentObject = null;
    setPosition(0, 0, 0);
    setAngle(0, 0, 0);
    setScale(1, 1, 1);
    setID(GET_NEXT_ID());
    m_modelId = -1;
    m_textureId = -1;
    m_haloMapId = -1;
}
GameObject::~GameObject() {
    std::cout << "Deleted GameObject with ID " << m_objectId <<std::endl;
}

int GameObject::getID() const {
    return m_objectId;
}

void GameObject::setID(int id) {
    m_objectId = id;
}

GameObject* GameObject::getParentObject() const {
    return m_parentObject;
}

void GameObject::setParentObject(GameObject* parent) {
    m_parentObject = parent;
}

void GameObject::setPosition(float x, float y, float z) {
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}


void GameObject::setPositionX(float x) {
    m_position.x = x;
}
void GameObject::setPositionY(float y) {
    m_position.y = y;
}
void GameObject::setPositionZ(float z) {
    m_position.z = z;
}
void GameObject::setPosition(glm::vec3 pos) {
    m_position = pos;
}

glm::vec3 GameObject::getPosition() const {
    if (m_parentObject == null)
        return m_position;
    else
        return m_position + m_parentObject->getPosition();
}
float GameObject::getPositionX() const{
    return m_position.x;
}
float GameObject::getPositionY() const{
    return m_position.y;
}
float GameObject::getPositionZ() const{
    return m_position.z;
}
void GameObject::addPosition(float x, float y, float z) {
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
}

void GameObject::addPosition(glm::vec3 position) {
    m_position += position;
}

void GameObject::setAngle(float x, float y, float z) {
    m_angle.x = x;
    m_angle.y = y;
    m_angle.z = z;
    correctAngle();
}

void GameObject::setAngle(glm::vec3 angle) {
    m_angle = angle;
    correctAngle();
}

glm::vec3 GameObject::getAngle() const {
    if (m_parentObject == null)
        return m_angle;
    else
        return m_angle + m_parentObject->getAngle();
}

void GameObject::addAngle(float x, float y, float z) {
    m_angle.x += x;
    m_angle.y += y;
    m_angle.z += z;
    correctAngle();
}

void GameObject::addAngle(glm::vec3 angle) {
    m_angle += angle;
}

void GameObject::correctAngle() {
    if (m_angle.x > 89.9)
        m_angle.x = 89.9;
    else if (m_angle.x < -89.9)
        m_angle.x = -89.9;
}

void GameObject::setScale(float x, float y, float z) {
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

void GameObject::setScale(glm::vec3 size) {
    m_scale = size;
}

glm::vec3 GameObject::getScale() const {
    if (m_parentObject == null)
        return m_scale;
    else
        return m_scale * m_parentObject->getScale();
}

void GameObject::addScale(float x, float y, float z) {
    m_scale.x += x;
    m_scale.y += y;
    m_scale.z += z;
}

void GameObject::addScale(glm::vec3 scale) {
    m_scale += scale;
}

int GameObject::getModelId() const {
    return m_modelId;
}

void GameObject::setModelId(int modelId) {
    m_modelId = modelId;
}

int GameObject::getTextureId() const {
    return m_textureId;
}

void GameObject::setTextureId(int textureId) {
    m_textureId = textureId;
}

int GameObject::getHaloMapId() const {
    return m_haloMapId;
}

void GameObject::setHaloMapId(int textureId) {
    m_haloMapId = textureId;
}

glm::mat4 GameObject::getModelMatrice() {
    glm::mat4 out;
    if (m_parentObject != null)
        out = m_parentObject->getModelMatrice();
    out = glm::translate(out, m_position);
    out = glm::scale(out, m_scale);
    out = glm::rotate(out, m_angle.y, glm::vec3(0, 1, 0));
    out = glm::rotate(out, m_angle.x, glm::vec3(1, 0, 0));
    out = glm::rotate(out, m_angle.z, glm::vec3(0, 0, 1));
    return out;
}