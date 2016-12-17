#include "Shader.h"

// Constructeurs et Destructeur

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_geometrySource(), m_fragmentSource() {
}

Shader::Shader(Shader const &shaderACopier) {
    // Copie des fichiers sources
    m_vertexSource = shaderACopier.m_vertexSource;
    m_geometrySource = shaderACopier.m_geometrySource;
    m_fragmentSource = shaderACopier.m_fragmentSource;
}

Shader::~Shader() {
    clean();
    std::cout << "Shader deleted." << std::endl;
}

Shader& Shader::operator=(Shader const &shaderACopier) {
    m_vertexSource = shaderACopier.m_vertexSource;
    m_geometrySource = shaderACopier.m_geometrySource;
    m_fragmentSource = shaderACopier.m_fragmentSource;
    
    return *this;
}

void Shader::clean() {
    if (glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if (glIsShader(m_geometryID) == GL_TRUE)
        glDeleteShader(m_geometryID);

    if (glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if (glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);
}

bool Shader::compileAll() {
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource)) {
        std::cout << "Can't compile vertex shader" << std::endl;
        return false;
    }
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource)) {
        std::cout << "Can't compile geometry shader" << std::endl;
        return false;
    }
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource)) {
        std::cout << "Can't compile fragment shader" << std::endl;
        return false;
    }
    return true;
}

void Shader::loadAll() {
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);
}

bool Shader::loadTexture(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();
    
    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_TEXTURE_LOCATION_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_TEXTURE_LOCATION_NORMAL, "in_Normal");
    glBindAttribLocation(m_programID, SHADER_TEXTURE_LOCATION_TEXCOORD_0, "in_TexCoord0");

    // Linkage du programme
    return link();
}

bool Shader::loadScan(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_SCAN_LOCATION_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_SCAN_LOCATION_NORMAL, "in_Normal");
    glBindAttribLocation(m_programID, SHADER_SCAN_LOCATION_TEXCOORD_0, "in_TexCoord0");

    // Linkage du programme
    return link();
}

bool Shader::loadText(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Linkage du programme
    return link();
}

bool Shader::loadParticle(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_PARTICLE_LOCATION_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_PARTICLE_LOCATION_TEXTURE_INDEX, "in_TextureIndex");
    glBindAttribLocation(m_programID, SHADER_PARTICLE_LOCATION_OPACITY, "in_Opacity");
    glBindAttribLocation(m_programID, SHADER_PARTICLE_LOCATION_SIZE, "in_Size");

    // Linkage du programme
    return link();
}

bool Shader::loadGUI(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_GUI_LOCATION_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_GUI_LOCATION_SIZE, "in_Size");
    glBindAttribLocation(m_programID, SHADER_GUI_LOCATION_COLOR, "in_Color");

    // Linkage du programme
    return link();
}

bool Shader::loadScreen(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_SCREEN_LOCATION_POSITION, "in_Position");
    glBindAttribLocation(m_programID, SHADER_SCREEN_LOCATION_TEXCOORD_0, "in_Texture");

    // Linkage du programme
    return link();
}

bool Shader::loadSquare(std::string vertexSource, std::string geometrySource, std::string fragmentSource) {
    // Enregistrement des chemins
    m_vertexSource = vertexSource;
    m_geometrySource = geometrySource;
    m_fragmentSource = fragmentSource;
    // Destruction d'un éventuel ancien Shader
    clean();
    // Compilation des shaders
    compileAll();
    // Création du programme
    loadAll();

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_SQUARE_LOCATION_POSITION, "in_Position");

    // Linkage du programme
    return link();
}

bool Shader::link() {
    // Linkage du programme
    glLinkProgram(m_programID);

    // V�rification du linkage
    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

    // S'il y a eu une erreur
    if (erreurLink != GL_TRUE) {
        std::cout << "Erreur linkage shader " << erreurLink << std::endl;
        // R�cup�ration de la taille de l'erreur
        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de m�moire
        char *erreur = new char[tailleErreur + 1];

        // R�cup�ration de l'erreur
        glGetProgramInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        // Affichage de l'erreur
        std::cout << erreur << std::endl;

        // Lib�ration de la m�moire et retour du bool�en false
        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    } else // Sinon c'est que tout s'est bien pass�
        return true;
}

bool Shader::compile(GLuint &shader, GLenum type, std::string const &fichierSource) {
    if (fichierSource == "")
        return true; // nothing to load
    // Création du shader
    shader = glCreateShader(type);

    // Vérification du shader
    if (shader == 0) {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    // Flux de lecture
    std::ifstream fichier(fichierSource.c_str());

    // Test d'ouverture
    if (!fichier) {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);
        return false;
    }

    // Strings permettant de lire le code source
    std::string ligne;
    std::string codeSource;

    // Lecture
    while (std::getline(fichier, ligne))
        codeSource += ligne + '\n';

    // Fermeture du fichier
    fichier.close();

    // Récupération de la chaine C du code source
    const GLchar* chaineCodeSource = codeSource.c_str();

    // Envoi du code source au shader
    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compilation du shader
    glCompileShader(shader);

    // V�rification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

    // S'il y a eu une erreur
    if (erreurCompilation != GL_TRUE) {
        // Récupération de la taille de l'erreur
        std::cout << "Erreur de compilation du Shader" << std::endl;
        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de m�moire
        char *erreur = new char[tailleErreur + 1];

        // R�cup�ration de l'erreur
        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        // Affichage de l'erreur
        std::cout << erreur << std::endl;

        // Lib�ration de la m�moire et retour du bool�en false
        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }// Sinon c'est que tout s'est bien pass�
    else
        return true;
}

// Getter

GLuint Shader::getProgramID() const {
    return m_programID;
}

void Shader::use() const {
    glUseProgram(m_programID);
}

void Shader::unUse() const {
    glUseProgram(0);
}

