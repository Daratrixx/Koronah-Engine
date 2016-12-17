
#include "GraphicEngine.h"

GraphicEngine::GraphicEngine() {
    m_window = null;
    m_title = "Default Window";
    m_width = DEFAULT_SCREEN_WIDTH;
    m_height = DEFAULT_SCREEN_HEIGHT;
    m_playGroundObjectToRender = new SortedKeyChain();
    m_textEngine = null;
    m_frameBufferColor = new FrameBuffer(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    m_frameBufferNormal = new FrameBuffer(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    m_frameBufferHalo = new FrameBuffer(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    m_frameBufferScan = new FrameBuffer_Scan(DEFAULT_SCREEN_WIDTH / SCAN_SCALE, DEFAULT_SCREEN_HEIGHT / SCAN_SCALE);
}

GraphicEngine::GraphicEngine(std::string title) {
    m_window = null;
    m_title = title;
    m_width = getGraphicSetting()->screenWidth;
    m_height = getGraphicSetting()->screenHeight;
    m_playGroundObjectToRender = new SortedKeyChain();
    m_textEngine = null;
    m_frameBufferColor = new FrameBuffer(m_width, m_height);
    m_frameBufferNormal = new FrameBuffer(m_width, m_height);
    m_frameBufferHalo = new FrameBuffer(m_width, m_height);
    m_frameBufferScan = new FrameBuffer_Scan(m_width / getGraphicSetting()->scanDivisor, m_height / getGraphicSetting()->scanDivisor);
}

GraphicEngine::~GraphicEngine() {
    delete m_frameBufferColor;
    delete m_frameBufferScan;
    delete m_textEngine;
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

    unsigned windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if(getGraphicSetting()->fullScreen)
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    
    // Création de la fenêtre
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, windowFlags);
    if (m_window == 0) {
        SDL_Quit();
        return false;
    }
    SDL_Surface* icon = IMG_Load("koronah.png");
    SDL_SetWindowIcon(m_window, icon);
    SDL_FreeSurface(icon);
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
    m_frameBufferColor->load();
    m_frameBufferNormal->load();
    m_frameBufferHalo->load();
    m_textEngine = new TextEngine();
    m_shaderSquare.loadSquare("data/shader/square.vert", "", "data/shader/square.frag");
    m_shaderScreen.loadScreen("data/shader/screen.vert", "", "data/shader/screen.frag");
    m_shaderHaloMap.loadScreen("data/shader/haloMap.vert", "", "data/shader/haloMap.frag");
    m_shaderModel.loadTexture("data/shader/texture.vert", "", "data/shader/texture.frag");
    m_shaderScan.loadScan("data/shader/scan.vert", "", "data/shader/scan.frag");
    m_shaderGUI.loadTexture("data/shader/GUI.vert", "data/shader/GUI.geom", "data/shader/GUI.frag");
    m_shaderNormal.loadTexture("data/shader/normal.vert", "", "data/shader/normal.frag");
    loadTexture("data/texture/noHalo.png"); //0
    loadTexture("data/texture/Sc2wB.bmp");
    loadTexture("data/texture/metal.jpg");
    loadTexture("data/texture/boletus.jpg");
    loadTexture("data/texture/ShrineTexture.png");
    loadTexture("data/texture/ShrineHalo.png"); // 5
    loadTexture("data/texture/ShrineHaloGreen.png");
    loadTexture("data/texture/halo.png");
    loadTexture("data/texture/selectionCircle.png"); // 8
    loadModel("data/model/spike.obj"); // 0
    loadModel("data/model/Shrine.obj");
    loadModel("data/model/boletus.obj");
    loadModel("data/model/flatsquare.obj"); // 3

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
    glGenBuffers(1, &m_screenVBO);
    // Verrouillage
    glBindBuffer(GL_ARRAY_BUFFER, m_screenVBO);
    // Remplissage
    glBufferData(GL_ARRAY_BUFFER, tailleVerticesBytes + tailleCoordTextureBytes, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVerticesBytes, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCoordTextureBytes, coordTexture);
    // Déverrouillage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* ***** Gestion du VAO ***** */
    // Génération du VAO
    glGenVertexArrays(1, &m_screenVOA);
    // Verrouillage du VAO
    glBindVertexArray(m_screenVOA);
    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_screenVBO);
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
    m_width = w;
    m_height = h;
    getGraphicSetting()->screenWidth = m_width;
    getGraphicSetting()->screenHeight = m_height;
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