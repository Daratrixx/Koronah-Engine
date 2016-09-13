#include "Shader.h"

// Constructeurs et Destructeur

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_geometrySource(), m_fragmentSource() {
}

Shader::Shader(Shader const &shaderACopier) {
    // Copie des fichiers sources
    m_vertexSource = shaderACopier.m_vertexSource;
    m_geometrySource = shaderACopier.m_geometrySource;
    m_fragmentSource = shaderACopier.m_fragmentSource;

    // Chargement du nouveau shader
    loadTexture();
}

Shader::Shader(std::string vertexSource, std::string fragmentSource)
: m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(vertexSource), m_fragmentSource(fragmentSource) {
    m_geometrySource = "";
}

Shader::Shader(std::string vertexSource, std::string geometrySource, std::string fragmentSource)
: m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(vertexSource), m_geometrySource(geometrySource), m_fragmentSource(fragmentSource) {
}

Shader::~Shader() {
    // Destruction du shader
    clean();
    std::cout << "Shader deleted." << std::endl;
}


// M�thodes

Shader& Shader::operator=(Shader const &shaderACopier) {
    // Copie des fichiers sources
    m_vertexSource = shaderACopier.m_vertexSource;
    m_geometrySource = shaderACopier.m_geometrySource;
    m_fragmentSource = shaderACopier.m_fragmentSource;

    // Retour du pointeur this
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

bool Shader::loadTexture() {
    // Destruction d'un �ventuel ancien Shader
    clean();
    // Compilation des shaders
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource))
        return false;
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Cr�ation du programme
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_INDEX_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_INDEX_NORMAL, "in_Normal");
    glBindAttribLocation(m_programID, SHADER_INDEX_TEXCOORD_0, "in_TexCoord0");
    //glBindAttribLocation(m_programID, SHADER_INDEX_TEXCOORD_1, "in_TexCoord1");
    //glBindAttribLocation(m_programID, SHADER_INDEX_TEXCOORD_2, "in_TexCoord2");

    // Linkage du programme
    return link();
}
bool Shader::loadText() {
    // Destruction d'un �ventuel ancien Shader
    clean();
    // Compilation des shaders
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource))
        return false;
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Cr�ation du programme
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);

    // Linkage du programme
    return link();
}

bool Shader::loadParticle() {
    // Destruction d'un �ventuel ancien Shader
    clean();
    // Compilation des shaders
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource))
        return false;
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Cr�ation du programme
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_INDEX_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_INDEX_TEXTURE_INDEX, "in_TextureIndex");
    glBindAttribLocation(m_programID, SHADER_INDEX_OPACITY, "in_Opacity");
    glBindAttribLocation(m_programID, SHADER_INDEX_SIZE, "in_Size");

    // Linkage du programme
    return link();
}

bool Shader::loadGUI() {
    // Destruction d'un �ventuel ancien Shader
    clean();
    // Compilation des shaders
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource))
        return false;
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Cr�ation du programme
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, SHADER_INDEX_VERTEX, "in_Vertex");
    glBindAttribLocation(m_programID, SHADER_INDEX_GUI_SIZE, "in_Size");
    glBindAttribLocation(m_programID, SHADER_INDEX_GUI_COLOR, "in_Color");

    // Linkage du programme
    return link();
}

bool Shader::loadScreen() {
    // Destruction d'un �ventuel ancien Shader
    clean();
    // Compilation des shaders
    if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometrySource))
        return false;
    if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Cr�ation du programme
    m_programID = glCreateProgram();

    // Association des shaders
    if (glIsShader(m_vertexID) == GL_TRUE)
        glAttachShader(m_programID, m_vertexID);
    if (glIsShader(m_geometryID) == GL_TRUE)
        glAttachShader(m_programID, m_geometryID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glAttachShader(m_programID, m_fragmentID);
    
    // Verrouillage des entr�es shader
    glBindAttribLocation(m_programID, 0, "in_Position");
    glBindAttribLocation(m_programID, 1, "in_Texture");

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
        // R�cup�ration de la taille de l'erreur
        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de m�moire
        char *erreur = new char[tailleErreur + 1];

        // R�cup�ration de l'erreur
        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
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
        return true; // nothing to lad
    // Cr�ation du shader
    shader = glCreateShader(type);

    // V�rification du shader
    if (shader == 0) {
        std::ofstream FILE("log.txt");
        FILE << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    // Flux de lecture
    std::ifstream fichier(fichierSource.c_str());

    // Test d'ouverture
    if (!fichier) {
        std::ofstream FILE("log.txt");
        FILE << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
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

    // R�cup�ration de la chaine C du code source
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
        // R�cup�ration de la taille de l'erreur
        std::ofstream FILE("log.txt", std::ofstream::out | std::ofstream::app);
        FILE << "Erreur de compilation du Shader" << std::endl;
        FILE.close();
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
    }
        // Sinon c'est que tout s'est bien pass�
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

