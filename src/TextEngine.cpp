
#include "TextEngine.h"
#include "Settings.h"

TextEngine::TextEngine() {
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(ft, "data/font/courbd.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 36);
    s.loadText("data/shader/text.vert", "", "data/shader/text.frag");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character;
        character.TextureID = texture;
        character.Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.Advance = face->glyph->advance.x;
        characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextEngine::~TextEngine() {
    if (glIsBuffer(VBO) == GL_TRUE)
        glDeleteBuffers(1, &VAO);
    if (glIsVertexArray(VAO) == GL_TRUE)
        glDeleteVertexArrays(1, &VAO);
    std::cout << "TextEngine deleted." << std::endl;
}

void TextEngine::writeLine(std::string line, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
    // Activate corresponding render state
    glm::mat4 projection = glm::ortho(0.0f, (float) getGraphicSetting()->screenWidth, 0.0f, (float) getGraphicSetting()->screenHeight);
    s.use();

    glUniformMatrix4fv(glGetUniformLocation(s.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(s.getProgramID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = line.begin(); c != line.end(); c++) {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos, ypos + h, 0.0, 0.0},
            { xpos, ypos, 0.0, 1.0},
            { xpos + w, ypos, 1.0, 1.0},

            { xpos, ypos + h, 0.0, 0.0},
            { xpos + w, ypos, 1.0, 1.0},
            { xpos + w, ypos + h, 1.0, 0.0}
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    s.unUse();
}

float TextEngine::getLineWidth(std::string line, GLfloat scale) {
    float x = 0;
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = line.begin(); c != line.end(); c++) {
        Character ch = characters[*c];
        x += (ch.Advance >> 6) * scale;
    }
    return x;
}

glm::vec2 TextEngine::getLineSize(std::string line, GLfloat scale) {
    glm::vec2 out(0, 0); //(x,y)
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = line.begin(); c != line.end(); c++) {
        Character ch = characters[*c];
        out.y = std::max(out.y, ch.Size.y * scale);
        out.x += (ch.Advance >> 6) * scale;
    }
    return out;
}