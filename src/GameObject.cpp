
#include "GameObject.h"


UInt GameObject::OBJECT_COUNT = 0;

UInt GameObject::GET_NEXT_ID() {
    return OBJECT_COUNT++;
}

GameObject::GameObject() {
    setPositionXYZ(0, 0, 0);
    setAngle(0, 0, 0);
    setScale(1, 1, 1);
    setColor(1, 1, 1);
    setID(GET_NEXT_ID());
    m_modelId = -1;
    m_textureId = -1;
    m_haloMapId = -1;
    m_teamColor = COLOR_WHITE;
    m_selectionCircleDisplayed = false;
    m_selectionCircleColor = glm::vec3(0, 1, 0);
    m_selectionCircleRadius = 2;
}

GameObject::GameObject(GameObject* o) {
    m_depth = o->m_depth;
    m_scale = o->m_scale;
    m_color = o->m_color;
    m_modelId = o->m_modelId;
    m_textureId = o->m_textureId;
    m_haloMapId = o->m_haloMapId;
    setID(GET_NEXT_ID());
    m_selectionCircleDisplayed = false;
    m_selectionCircleColor = glm::vec3(0, 1, 0);
    m_selectionCircleRadius = 2;
}

GameObject::~GameObject() {
}

bool GameObject::writeInFile(std::ofstream & fout) {
    /*unsigned addr = (unsigned)this;
    unsigned size = sizeof(this);
    fout.write((char*) &addr, sizeof(unsigned));
    fout.write((char*) &size, sizeof(unsigned));
    fout.write((char*) this, size);*/
    return true;
}

bool GameObject::readFromFile(std::ifstream & fin) {
    fin.read((char*) this, sizeof(this));
    return true;
}

UInt GameObject::getID() const {
    return m_objectId;
}

void GameObject::setID(const UInt & id) {
    m_objectId = id;
}

void GameObject::setPositionXYZ(const float & x, const float & y, const float & z) {
    m_position.x = x;
    m_position.y = y;
    m_depth = z;
}

void GameObject::setPositionXYZ(const glm::vec3 & pos) {
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_depth = pos.z;
}

void GameObject::setPositionXY(const float & x, const float & y) {
    m_position.x = x;
    m_position.y = y;
}

void GameObject::setPositionXY(const glm::vec2 & pos) {
    m_position.x = pos.x;
    m_position.y = pos.y;
}

void GameObject::setPositionX(const float & x) {
    m_position.x = x;
}

void GameObject::setPositionY(const float & y) {
    m_position.y = y;
}

void GameObject::setPositionZ(const float & z) {
    m_depth = z;
}

glm::vec3 GameObject::getPositionXYZ() const {
    return glm::vec3(m_position.x, m_position.y, m_depth);
}

glm::vec2 GameObject::getPositionXY() const {
    return m_position;
}

float GameObject::getPositionX() const {
    return m_position.x;
}

float GameObject::getPositionY() const {
    return m_position.y;
}

float GameObject::getPositionZ() const {
    return m_depth;
}

void GameObject::addPositionXYZ(const float & x, const float & y, const float & z) {
    m_position.x += x;
    m_position.y += y;
    m_depth += z;
}

void GameObject::addPositionXYZ(const glm::vec3 & position) {
    m_position.x += position.x;
    m_position.y += position.y;
    m_depth += position.z;
}

void GameObject::addPositionXY(const float & x, const float & y) {
    m_position.x += x;
    m_position.y += y;
}

void GameObject::addPositionXY(const glm::vec2 & position) {
    m_position.x += position.x;
    m_position.y += position.y;
}

void GameObject::setAngle(const float & x, const float & y, const float & z) {
    m_angle.x = x;
    m_angle.y = y;
    m_angle.z = z;
    correctAngle();
}

void GameObject::setAngle(const glm::vec3 & angle) {
    m_angle = angle;
    correctAngle();
}

glm::vec3 GameObject::getAngle() const {
    return m_angle;
}

void GameObject::addAngle(const float & x, const float & y, const float & z) {
    m_angle.x += x;
    m_angle.y += y;
    m_angle.z += z;
    correctAngle();
}

void GameObject::addAngle(const glm::vec3 & angle) {
    m_angle += angle;
    correctAngle();
}

void GameObject::correctAngle() {
    if (m_angle.x > 89.9)
        m_angle.x = 89.9;
    else if (m_angle.x < -89.9)
        m_angle.x = -89.9;
}

void GameObject::setScale(const float & x, const float & y, const float & z) {
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

void GameObject::setScale(const glm::vec3 & size) {
    m_scale = size;
}

glm::vec3 GameObject::getScale() const {
    return m_scale;
}

void GameObject::addScale(const float & x, const float & y, const float & z) {
    m_scale.x += x;
    m_scale.y += y;
    m_scale.z += z;
}

void GameObject::addScale(const glm::vec3 & scale) {
    m_scale += scale;
}

void GameObject::setColor(const float & r, const float & g, const float & b) {
    m_color.x = r;
    m_color.y = g;
    m_color.z = b;
}

void GameObject::setColor(const glm::vec3 & color) {
    m_color = color;
}

glm::vec3 GameObject::getColor() const {
    return m_color;
}

void GameObject::setTeamColor(const float & r, const float & g, const float & b) {
    m_teamColor.x = r;
    m_teamColor.y = g;
    m_teamColor.z = b;
}

void GameObject::setTeamColor(const glm::vec3 & color) {
    m_teamColor = color;
}

glm::vec3 GameObject::getTeamColor() const {
    return m_teamColor;
}

UInt GameObject::getModelId() const {
    return m_modelId;
}

void GameObject::setModelId(const UInt & modelId) {
    m_modelId = modelId;
}

UInt GameObject::getTextureId() const {
    return m_textureId;
}

void GameObject::setTextureId(const UInt & textureId) {
    m_textureId = textureId;
}

UInt GameObject::getHaloMapId() const {
    return m_haloMapId;
}

void GameObject::setHaloMapId(const UInt & textureId) {
    m_haloMapId = textureId;
}

glm::mat4 GameObject::getVertexMatrice() {
    glm::mat4 out;
    out = glm::translate(out, getPositionXYZ());
    out = glm::scale(out, m_scale);
    out = glm::rotate(out, m_angle.z, glm::vec3(0, 0, 1));
    out = glm::rotate(out, m_angle.x, glm::vec3(1, 0, 0));
    out = glm::rotate(out, m_angle.y, glm::vec3(0, 1, 0));
    return out;
}

glm::mat4 GameObject::getCircleMatrice() {
    glm::mat4 out;
    out = glm::translate(out, getPositionXYZ());
    glm::vec3 circle(m_selectionCircleRadius, m_selectionCircleRadius, m_selectionCircleRadius);
    out = glm::scale(out, circle);
    return out;
}
