
#include "GraphicEngine.h"

GraphicEngine::GraphicEngine() {
    m_window = null;
    m_title = "Default Window";
    m_width = DEFAULT_SCREEN_WIDTH;
    m_height = DEFAULT_SCREEN_HEIGHT;
    m_playGroundObjectToRender = new SortedKeyChain();
    m_textEngine = null;
    m_frameBuffer = new FrameBuffer(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    m_frameBufferScan = new FrameBuffer_Scan(DEFAULT_SCREEN_WIDTH / SCAN_SCALE, DEFAULT_SCREEN_HEIGHT / SCAN_SCALE);
}

GraphicEngine::GraphicEngine(std::string title, int width, int height) {
    m_window = null;
    m_title = title;
    m_width = width;
    m_height = height;
    Settings_setResolution(width, height);
    m_playGroundObjectToRender = new SortedKeyChain();
    m_textEngine = null;
    m_frameBuffer = new FrameBuffer(width, height);
    m_frameBufferScan = new FrameBuffer_Scan(width / SCAN_SCALE, height / SCAN_SCALE);
}

GraphicEngine::~GraphicEngine() {
    delete m_frameBuffer;
    delete m_frameBufferScan;
    delete m_textEngine;
    delete m_shaderScreen;
    delete m_shaderModel;
    delete m_shaderScan;
    delete m_shaderParticle;
    delete m_shaderGUI;
    delete m_shaderSquare;
    delete m_shaderHaloMap;
    delete m_playGroundObjectToRender;
    clearModelList();
    std::cout << "Model list deleted." << std::endl;
    clearTextureList();
    std::cout << "Texture list deleted." << std::endl;
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool GraphicEngine::initWindow(int flags) {
    if (m_window != null) { // re-init of window, destroy previous one
        SDL_GL_DeleteContext(m_contexteOpenGL);
        SDL_DestroyWindow(m_window);
    } else {
        // Initialisation de la SDL
        if (SDL_Init(flags) < 0) {
            std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (m_window == 0) {
        SDL_Quit();
        return false;
    }

    // Création du contexte OpenGL
    m_contexteOpenGL = SDL_GL_CreateContext(m_window);

    if (m_contexteOpenGL == 0) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GL_MakeCurrent(m_window, m_contexteOpenGL);
    return true;
}

bool GraphicEngine::initGL() {
    glewExperimental = GL_TRUE;
    // On initialise GLEW
    GLenum initialisationGLEW(glewInit());

    // Si l'initialisation a échoué :
    if (initialisationGLEW != GLEW_OK) {
        // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

        return false;
    }

    // Activation de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Activation du Depth Buffer
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.3f, 0, 0.3f, 1);
    glLineWidth(1.f);
    glPointSize(1.f);

    // Tout s'est bien passé, on retourne true
    std::cout << "initGL successful." << std::endl;
    return true;
}

void GraphicEngine::loadGraphicDatas() {
    m_frameBufferScan->load();
    m_frameBuffer->load();
    m_textEngine = new TextEngine();
    m_shaderSquare = new Shader("data/shader/square.vert", "data/shader/square.frag");
    m_shaderSquare->loadSquare();
    m_shaderScreen = new Shader("data/shader/screen.vert", "data/shader/screen.frag");
    m_shaderScreen->loadScreen();
    m_shaderHaloMap = new Shader("data/shader/haloMap.vert", "data/shader/haloMap.frag");
    m_shaderHaloMap->loadScreen();
    m_shaderModel = new Shader("data/shader/texture.vert", "data/shader/texture.frag");
    m_shaderModel->loadTexture();
    m_shaderScan = new Shader("data/shader/scan.vert", "data/shader/scan.frag");
    m_shaderScan->loadScan();
    m_shaderParticle = new Shader("data/shader/particle.vert", "data/shader/particle.geom", "data/shader/particle.frag");
    m_shaderParticle->loadParticle();
    m_shaderGUI = new Shader("data/shader/GUI.vert", "data/shader/GUI.geom", "data/shader/GUI.frag");
    m_shaderGUI->loadTexture();
    loadTexture("data/texture/noHalo.png");
    loadTexture("data/texture/Sc2wB.bmp");
    loadTexture("data/texture/spike.jpg");
    loadTexture("data/texture/boletus.png");
    loadTexture("data/texture/ShrineTexture.png");
    loadTexture("data/texture/ShrineHalo.png");
    loadTexture("data/texture/ShrineHaloGreen.png");
    loadModel("data/model/spike.obj");
    loadModel("data/model/Shrine.obj");

    m_camera.setProjection(DEFAULT_SCREEN_FOV, 4.f / 3.f, DEFAULT_SCREEN_NEAR, DEFAULT_SCREEN_FAR);
    m_camera.setPosition(0, 0, 25);
    m_camera.setTargetPoint(0, 0, -1);
    m_projectionScene = m_camera.getProjectionMatrice();

    float vertices[] = {-1, -1, 1, -1, 1, 1, // Triangle 1
        -1, -1, 1, 1, -1, 1}; // Triangle 2
    float coordTexture[] = {0, 0, 1, 0, 1, 1, // Triangle 1
        0, 0, 1, 1, 0, 1}; // Triangle 2

    int tailleVerticesBytes = 12 * sizeof (float);
    int tailleCoordTextureBytes = 12 * sizeof (float);
    // Génération du VBO
    glGenBuffers(1, &vbo);
    // Verrouillage
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Remplissage
    glBufferData(GL_ARRAY_BUFFER, tailleVerticesBytes + tailleCoordTextureBytes, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVerticesBytes, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCoordTextureBytes, coordTexture);
    // Déverrouillage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* ***** Gestion du VAO ***** */
    // Génération du VAO
    glGenVertexArrays(1, &vao);
    // Verrouillage du VAO
    glBindVertexArray(vao);
    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    // Vertex Attrib 0 (Vertices)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tailleVerticesBytes));
    glEnableVertexAttribArray(1);
    // Déverrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Déverrouillage du VAO
    glBindVertexArray(0);

    // gen vao square
    glGenVertexArrays(1, &m_squareVAO);
    glBindVertexArray(m_squareVAO);
    // gen vbo square
    glGenBuffers(1, &m_squareVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_squareVAO);
    // stuff
    glBufferData(GL_ARRAY_BUFFER, sizeof (float) * 2 * 4, NULL, GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (float) * 2 * 4, 0);
    glEnableVertexAttribArray(SHADER_SQUARE_LOCATION_POSITION);
    glVertexAttribPointer(SHADER_SQUARE_LOCATION_POSITION, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int GraphicEngine::createHeightMapModel(HeightMapData* data) {
    return addModel(new ModelHeightMap(data));
}

void GraphicEngine::setLightData(float* lightData) {
    m_lightData = lightData;
}

void GraphicEngine::addToRender(GameObject* object) {
    float maxDistance = m_camera.getFar();
    float minDistance = m_camera.getClose();
    float distance = getCameraDistance(object->getPositionXYZ());
    if (distance < maxDistance && distance > minDistance)
        m_playGroundObjectToRender->add(distance, (void*) object);
}

void GraphicEngine::startRender() {
    glClearColor(0.3f, 0, 0.3f, 1);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicEngine::renderFrameBufferToScreen(FrameBuffer* frameBuffer, Shader* shader, unsigned int colorID) {
    glViewport(0, 0, m_width, m_height);
    glDisable(GL_DEPTH_TEST);
    shader->use();
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, frameBuffer->getColorBufferId(colorID));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    shader->unUse();
    glEnable(GL_DEPTH_TEST);
}

void GraphicEngine::renderFrameBufferToScreen(FrameBuffer* frameBuffer, Shader* shader, unsigned int colorID, bool isHorizontal) {
    glDisable(GL_DEPTH_TEST);
    shader->use();
    if (isHorizontal)
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "isHorizontal"), 1);
    else
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "isHorizontal"), 0);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, frameBuffer->getColorBufferId(colorID));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    shader->unUse();
    glEnable(GL_DEPTH_TEST);
}

void GraphicEngine::renderPlayGround() {
    glClearColor(0, 0, 0, 0);
    glm::mat4 view = m_camera.getViewMatrice();
    // WORLD PASS (0)
    m_frameBuffer->use();
    // PROGRAM - MODEL
    // UNIFORMS
    m_shaderModel->use();
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel->getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    // render buffered objects
    KeyLink* current = m_playGroundObjectToRender->first;
    while (current != null) {
        renderObject((GameObject*) (current->value));
        current = current->next;
    }
    // HALO PASS (1)
    m_shaderModel->unUse();
    m_frameBuffer->unUse();
    renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 0); // add world to scren
    m_frameBuffer->use();
    m_shaderModel->use();
    // render buffered objects
    current = m_playGroundObjectToRender->first;
    glUniform3f(glGetUniformLocation(m_shaderModel->getProgramID(), "modelColor"), 1, 1, 1);
    while (current != null) {
        renderObjectHaloMap((GameObject*) (current->value));
        current = current->next;
    }
    m_shaderModel->unUse();
    m_frameBuffer->unUse();
    // HALO PASS (1 to 2)
    //m_frameBuffer->changeColorAttachment(2);
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderHaloMap, 0, true);
    // HALO PASS (2 to 3)
    //m_frameBuffer->changeColorAttachment(3);
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderHaloMap, 0, false);

    // screen render
    renderFrameBufferToScreen(m_frameBuffer, m_shaderHaloMap, 0); // add world to scren
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 1); // add halo to scree
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 2); // add halo to screem
    //renderFrameBufferToScreen(m_frameBuffer, m_shaderScreen, 3); // add halo to screem
}

void GraphicEngine::renderSquare(glm::vec2 start, glm::vec2 end) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    m_shaderSquare->use();
    GLfloat vertices[4 * 2] = {
        (start.x / m_width) * 2 - 1, (start.y / m_height) * 2 - 1,
        (end.x / m_width) * 2 - 1, (start.y / m_height) * 2 - 1,
        (end.x / m_width) * 2 - 1, (end.y / m_height) * 2 - 1,
        (start.x / m_width) * 2 - 1, (end.y / m_height) * 2 - 1
    };
    glBindVertexArray(m_squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_squareVAO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    m_shaderSquare->unUse();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GraphicEngine::renderObject(GameObject* object) {
    int idModel(object->getModelId());
    int idTexture(object->getTextureId());
    if (idModel > -1 && idTexture > -1) {
        glm::mat4 model = object->getModelMatrice();
        Model* modelData = getModel(idModel);
        Texture* textureData = getTexture(idTexture);
        if (modelData != null && textureData != null) {
            glUniform3f(glGetUniformLocation(m_shaderModel->getProgramID(), "modelColor"), object->getColor().x, object->getColor().y, object->getColor().z);
            renderModel(modelData, textureData, model);
        }
    }
}

void GraphicEngine::renderObjectHaloMap(GameObject* object) {
    int idModel(object->getModelId());
    int idHaloMap(object->getHaloMapId());
    if (idModel > -1 && idHaloMap > -1) {
        glm::mat4 model = object->getModelMatrice();
        Model* modelData = getModel(idModel);
        Texture* textureData = getTexture(idHaloMap);
        if (modelData != null && textureData != null) {
            glUniform3f(glGetUniformLocation(m_shaderModel->getProgramID(), "modelColor"), object->getTeamColor().x, object->getTeamColor().y, object->getTeamColor().z);
            renderModel(modelData, textureData, model);
        }
    }
}

void GraphicEngine::renderModel(Model* modelData, Texture* textureData, glm::mat4 &model) {
    glUniformMatrix4fv(glGetUniformLocation(m_shaderModel->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    modelData->drawUsingVao(m_shaderModel, textureData);
}

void GraphicEngine::renderParticle(glm::vec3* position, float* opacity, float* size, int count) {
    glm::mat4 view = m_camera.getViewMatrice();
    renderParticle(position, opacity, size, count, getTexture(4), view);
}

void GraphicEngine::renderParticle(glm::vec3* position, float* opacity, float* size, int count, Texture* texture, glm::mat4 &view) {

    // PROGRAM
    m_shaderParticle->use();

    // PRIMITIVES
    glVertexAttribPointer(SHADER_TEXTURE_LOCATION_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, position);
    glEnableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
    glVertexAttribPointer(SHADER_PARTICLE_LOCATION_OPACITY, 1, GL_FLOAT, GL_FALSE, 0, opacity);
    glEnableVertexAttribArray(SHADER_PARTICLE_LOCATION_OPACITY);
    glVertexAttribPointer(SHADER_PARTICLE_LOCATION_SIZE, 1, GL_FLOAT, GL_FALSE, 0, size);
    glEnableVertexAttribArray(SHADER_PARTICLE_LOCATION_SIZE);

    // UNIFORMS
    glUniformMatrix4fv(glGetUniformLocation(m_shaderParticle->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionScene));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderParticle->getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    //TEXTURE
    if (texture != null)
        glBindTexture(GL_TEXTURE_2D, texture->getID());

    //RENDER
    glDrawArrays(GL_POINTS, 0, count);

    if (texture != null)
        glBindTexture(GL_TEXTURE_2D, 0);

    // Désactivation des tableaux
    glDisableVertexAttribArray(SHADER_PARTICLE_LOCATION_SIZE);
    glDisableVertexAttribArray(SHADER_PARTICLE_LOCATION_OPACITY);
    glDisableVertexAttribArray(SHADER_TEXTURE_LOCATION_VERTEX);
    // Désactivation du shader
    m_shaderParticle->unUse();
}

void GraphicEngine::endRender() {
    SDL_GL_SwapWindow(m_window);
    m_playGroundObjectToRender->clear();
}

void GraphicEngine::writeLine(std::string line, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
    if (m_textEngine != null)
        m_textEngine->writeLine(line, x, y, scale, color);
}

float GraphicEngine::getLineWidth(std::string line, GLfloat scale) {
    if (m_textEngine != null)
        return m_textEngine->getLineWidth(line, scale);
    return 0;
}

glm::vec2 GraphicEngine::getLineSize(std::string line, GLfloat scale) {
    if (m_textEngine != null)
        return m_textEngine->getLineSize(line, scale);
    return glm::vec2(0, 0);
}

void GraphicEngine::moveCamera(GameObject* object) {
    m_camera.setPosition(object->getPositionXYZ());
    m_camera.setAngle(object->getAngle());
}

float GraphicEngine::getCameraDistance(glm::vec3 position) {
    return glm::length(m_camera.getPosition() - position);
}

void GraphicEngine::setResolution(int w, int h) {
    Settings_setResolution(w, h);
    m_width = w;
    m_height = h;
    m_ratio = (float) w / (float) h;
    m_camera.setProjection(70, m_ratio, DEFAULT_SCREEN_NEAR, DEFAULT_SCREEN_FAR);
    SDL_SetWindowSize(m_window, m_width, m_height);
    m_projectionScene = m_camera.getProjectionMatrice();
}

int GraphicEngine::getWidth() const {
    return m_width;
}

int GraphicEngine::getHeight() const {
    return m_height;
}

float GraphicEngine::getRatio() const {
    return m_ratio;
}

void GraphicEngine::setWindowTitle(std::string title) {
    m_title = title;
    SDL_SetWindowTitle(m_window, m_title.c_str());
}