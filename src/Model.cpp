#include "Model.h"

Model::Model() {
    m_verticeCount = 0;
    m_verticeData = null;
    m_normalData = null;
    m_textureData = null;
    m_animationModifierData = null;
    m_vboID = 0;
    m_vaoID = 0;
}

Model::~Model() {
    delete m_verticeData;
    delete m_normalData;
    delete m_textureData;
    delete m_animationModifierData;
    if (glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);
    if (glIsVertexArray(m_vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &m_vaoID);
}

void Model::load() {
    // clean mVRAM
    if (glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);
    if (glIsVertexArray(m_vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &m_vaoID);

    // compute buffer size
    initSize();

    // set buffer
    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, m_verticeSize + m_normalSize + m_textureSize + m_animationModifierSize, 0, GL_STATIC_DRAW);
    //std::cout << "Created GL_ARRAY BUFFER (" << m_vboID << ") with " << (m_verticeSize + m_normalSize + m_textureSize + m_animationModifierSize) << " bytes capacity" << std::endl;
    glBufferSubData(GL_ARRAY_BUFFER, getVerticeOffset(), m_verticeSize, getVerticeData());
    //std::cout << "Uploaded " << m_verticeSize << " bytes for vertice" << std::endl;
    glBufferSubData(GL_ARRAY_BUFFER, getNormalOffset(), m_normalSize, getNormalData());
    //std::cout << "Uploaded " << m_normalSize << " bytes for normal" << std::endl;
    glBufferSubData(GL_ARRAY_BUFFER, getTextureOffset(), m_textureSize, getTextureData());
    //std::cout << "Uploaded " << m_textureSize << " bytes for texture" << std::endl;
    glBufferSubData(GL_ARRAY_BUFFER, getAnimationModifierOffset(), m_animationModifierSize, getAnimationModifierData());
    //std::cout << "Uploaded " << m_animationModifierSize << " bytes for animation modifier" << std::endl;
    glBindVertexArray(0);

    // set vertexArray
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glVertexAttribPointer(SHADER_TEXTURE_LOCATION_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(getVerticeOffset()));
    glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
    glVertexAttribPointer(SHADER_TEXTURE_LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(getNormalOffset()));
    glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_NORMAL);
    glVertexAttribPointer(SHADER_TEXTURE_LOCATION_TEXCOORD_0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(getTextureOffset()));
    glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_TEXCOORD_0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::initSize() {
    // vertice
    if (m_verticeData != null)
        m_verticeSize = 3 * sizeof (float) * m_verticeCount;
    else
        m_verticeSize = 0;
    // normal
    if (m_normalData != null)
        m_normalSize = 3 * sizeof (float) * m_verticeCount;
    else
        m_normalSize = 0;
    // texture
    if (m_textureData != null)
        m_textureSize = 2 * sizeof (float) * m_verticeCount;
    else
        m_textureSize = 0;
    // animation modifier
    if (m_animationModifierData != null)
        m_animationModifierSize = sizeof (glm::mat4) * m_verticeCount;
    else
        m_animationModifierSize = 0;
}

float* Model::getVerticeData() const {
    return m_verticeData;
}

float* Model::getNormalData() const {
    return m_normalData;
}

float* Model::getTextureData() const {
    return m_textureData;
}

glm::mat4* Model::getAnimationModifierData() const {
    return m_animationModifierData;
}

int Model::getVerticeCount() const {
    return m_verticeCount;
}

int Model::getVerticeSize() const {
    return m_verticeSize;
}

int Model::getNormalSize() const {
    return m_normalSize;
}

int Model::getTextureSize() const {
    return m_verticeSize;
}

int Model::getAnimationModifierSize() const {
    return m_normalSize;
}

int Model::getVerticeOffset() const {
    return 0;
}

int Model::getNormalOffset() const {
    return m_verticeSize;
}

int Model::getTextureOffset() const {
    return getNormalOffset() + m_normalSize;
}

int Model::getAnimationModifierOffset() const {
    return getTextureOffset() + m_textureSize;
}

GLuint Model::getVboId() const {
    return m_vboID;
}

void Model::useVbo() {
    if (m_vboID != 0 && m_vaoID == 0)
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
}

void Model::unUseVbo() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Model::getVaoId() const {
    return m_vaoID;
}

void Model::useVao() {
    if (m_vaoID != 0)
        glBindVertexArray(m_vaoID);
}

void Model::unUseVao() {
    glBindVertexArray(0);
}

void Model::drawUsingVao(Texture* t) {
    useVao();
    if (t != null)
        glBindTexture(GL_TEXTURE_2D, t->getID());
    glDrawArrays(GL_TRIANGLES, 0, getVerticeCount());
    if (t != null)
        glBindTexture(GL_TEXTURE_2D, 0);
    unUseVao();
}

std::vector<Model*>* getModelList() {
    static std::vector<Model*>* MODEL_LIST = new std::vector<Model*>();
    return MODEL_LIST;
}

unsigned int addModel(Model* model) {
    std::vector<Model*>* MODEL_LIST = getModelList();
    MODEL_LIST->push_back(model);
    return MODEL_LIST->size() - 1;
}

Model* modelExists(std::string path) {
    std::vector<Model*>* MODEL_LIST = getModelList();
    for (unsigned int i = 0; i < MODEL_LIST->size(); i++)
        return (*MODEL_LIST)[i];
    //std::cout << "can load model " << path << std::endl;
    return null;
}

Model* getModel(unsigned int index) {
    std::vector<Model*>* MODEL_LIST = getModelList();
    if (index < MODEL_LIST->size())
        return (*MODEL_LIST)[index];
    //std::cout << "no model at index " << index << " (" << MODEL_LIST->size() << ")" << std::endl;
    return null;
}

void clearModelList() {
    std::vector<Model*>* MODEL_LIST = getModelList();
    for (unsigned int i = 0; i < MODEL_LIST->size(); i++)
        delete (*MODEL_LIST)[i];
    MODEL_LIST->clear();
}

