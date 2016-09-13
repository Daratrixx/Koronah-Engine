#include "Cube.h"

using namespace glm;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                ////
////                                                            CLASSE CUBE                                                         ////
////                                                                                                                                ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cube::Cube(float taille, std::string const vertexShader, std::string const fragmentShader):
m_shader(vertexShader, fragmentShader), m_vboID(0), m_tailleVerticesBytes(108 * sizeof(float)),m_tailleCouleursBytes(108 * sizeof(float))
{
    // Chargement du shader

    m_shader.loadTexture();


    // Division de la taille

    taille /= 2;


    // Vertices temporaires

    float verticesTmp[] = {
-taille, -taille, -taille, taille, -taille, -taille, taille, -taille, taille,
-taille, -taille, -taille, -taille, -taille, taille, taille, -taille, taille,

taille, taille, -taille, taille, -taille, -taille, taille, -taille, taille,
taille, taille, -taille, taille, taille, taille, taille, -taille, taille,

-taille, taille, -taille, taille, taille, -taille, taille, -taille, -taille,
-taille, taille, -taille, -taille, -taille, -taille, taille, -taille, -taille,

-taille, taille, -taille, taille, taille, -taille, taille, taille, taille,
-taille, taille, -taille, -taille, taille, taille, taille, taille, taille,

-taille, -taille, -taille, -taille, taille, -taille, -taille, taille, taille,
-taille, -taille, -taille, -taille, -taille, taille, -taille, taille, taille,

-taille, taille, taille, taille, taille, taille, taille, -taille, taille,
-taille, taille, taille, -taille, -taille, taille, taille, -taille, taille};      // Face 6


    // Couleurs temporaires

    float couleursTmp[] = {1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,           // Face 1
                           1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 1.0,           // Face 1

                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 2
                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 2

                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3
                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3

                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 4
                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 4

                           0.0, 1.0, 1.0,   0.0, 1.0, 1.0,   0.0, 1.0, 1.0,           // Face 5
                           0.0, 1.0, 1.0,   0.0, 1.0, 1.0,   0.0, 1.0, 1.0,           // Face 5

                           0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,           // Face 6
                           0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0};          // Face 6


    // Copie des valeurs dans les tableaux finaux

    for(int i(0); i < 108; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_couleurs[i] = couleursTmp[i];
    }
    
    m_tailleVerticesBytes=180*sizeof(float);
    m_tailleCouleursBytes=180*sizeof(float);
}

Cube::~Cube()
{
    // Destruction du VBO

    glDeleteBuffers(1, &m_vboID);
}

void Cube::charger()
{
    // Destruction d'un éventuel ancien VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);

    // Génération de l'ID
    glGenBuffers(1, &m_vboID);

    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        // Allocation de la mémoire vidéo
        glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);

        // Transfert des données
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_couleurs);

    // Déverrouillage de l'objet
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader
    glUseProgram(m_shader.getProgramID());

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

            // Accès aux vertices dans la mémoire vidéo
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            // Accès aux couleurs dans la mémoire vidéo
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
            glEnableVertexAttribArray(1);

        // Déverrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Désactivation des tableaux

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                ////
////                                                            CLASSE CAISSE                                                       ////
////                                                                                                                                ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Caisse::Caisse(float taille, float repeat, std::string const vertexShader, std::string const fragmentShader, std::string const texture):
                Cube(taille, vertexShader, fragmentShader),m_texture(texture)
{
    // Chargement de la texture
    m_texture.charger();

    // Coordonnées de texture temporaires
    float coordTextureTmp[] = {0, 0,   repeat, 0,   repeat, repeat,     // Face 1
                               0, 0,   0, repeat,   repeat, repeat,     // Face 1

                               0, 0,   repeat, 0,   repeat, repeat,     // Face 2
                               0, 0,   0, repeat,   repeat, repeat,     // Face 2

                               0, 0,   repeat, 0,   repeat, repeat,     // Face 3
                               0, 0,   0, repeat,   repeat, repeat,     // Face 3

                               0, 0,   repeat, 0,   repeat, repeat,     // Face 4
                               0, 0,   0, repeat,   repeat, repeat,     // Face 4

                               0, 0,   repeat, 0,   repeat, repeat,     // Face 5
                               0, 0,   0, repeat,   repeat, repeat,     // Face 5

                               0, 0,   repeat, 0,   repeat, repeat,     // Face 6
                               0, 0,   0, repeat,   repeat, repeat};    // Face 6

    // Copie des valeurs dans le tableau final
    for(int i (0); i < 72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}Caisse::Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture):
                Cube(taille, vertexShader, fragmentShader),m_texture(texture)
{
    // Chargement de la texture
    m_texture.charger();

    // Coordonnées de texture temporaires
    float coordTextureTmp[] = {
                               1, 1.0f/3.0f,   3.0f/4.0f, 1.0f/3.0f,   3.0f/4.0f, 2.0f/3.0f,
                               1, 1.0f/3.0f,   1, 2.0f/3.0f,   3.0f/4.0f, 2.0f/3.0f,
                               
                               2.0f/4.0f, 1.0f/3.0f,   3.0f/4.0f, 1.0f/3.0f,   3.0f/4.0f, 2.0f/3.0f,
                               2.0f/4.0f, 1.0f/3.0f,   2.0f/4.0f, 2.0f/3.0f,   3.0f/4.0f, 2.0f/3.0f,

                               1.0f/4.0f, 0.0f,   2.0f/4.0f, 0.0f,   2.0f/4.0f, 1.0f/3.0f, // up
                               1.0f/4.0f, 0.0f,   1.0f/4.0f, 1.0f/3.0f,   2.0f/4.0f, 1.0f/3.0f, // up

                               1.0f/4.0f, 1.0f/3.0f,   2.0f/4.0f, 1.0f/3.0f,   2.0f/4.0f, 2.0f/3.0f,
                               1.0f/4.0f, 1.0f/3.0f,   1.0f/4.0f, 2.0f/3.0f,   2.0f/4.0f, 2.0f/3.0f,

                               0, 1.0f/3.0f,   1.0f/4.0f, 1.0f/3.0f,   1.0f/4.0f, 2.0f/3.0f,
                               0, 1.0f/3.0f,   0, 2.0f/3.0f,   1.0f/4.0f, 2.0f/3.0f,
                               
                               1.0f/4.0f, 2.0f/3.0f,   2.0f/4.0f, 2.0f/3.0f,   2.0f/4.0f, 1.0f, // down
                               1.0f/4.0f, 2.0f/3.0f,   1.0f/4.0f, 1.0f,   2.0f/4.0f, 1.0f}; // down

    // Copie des valeurs dans le tableau final
    for(int i (0); i < 72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}
Caisse::~Caisse()
{

}

void Caisse::afficher(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model)
{
    glm::mat3 light[100];
    int lightCount = 0;
    // Activation du shader
    glUseProgram(m_shader.getProgramID());

        // Envoi des vertices
        glVertexAttribPointer(SHADER_INDEX_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(SHADER_INDEX_VERTEX);

        // Envoi des coordonnées de texture
        glVertexAttribPointer(SHADER_INDEX_TEXCOORD_0, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(SHADER_INDEX_TEXCOORD_0);

        // Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "model"), 1, GL_FALSE, value_ptr(model));
        glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "lightCount"), lightCount);
        glUniformMatrix3fv(glGetUniformLocation(m_shader.getProgramID(), "lightSource"), 100, GL_FALSE, (float*)light);
        //glUniformMatrix3fv(glGetUniformLocation(m_shader.getProgramID(), "lightSource"), 100, GL_FALSE, value_ptr(null));
        //glUniform4fv(glGetUniformLocation(m_shader.getProgramID(), "color"), 1, GL_FALSE, value_ptr(modelview));

        // Verrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());

        // Rendu
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Désactivation des tableaux
        glDisableVertexAttribArray(SHADER_INDEX_TEXCOORD_0);
        glDisableVertexAttribArray(SHADER_INDEX_VERTEX);


    // Désactivation du shader

    glUseProgram(0);
}
