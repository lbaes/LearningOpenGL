#include "texture.h"
#include "glad.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(){
    ID = 0;
}

Texture::Texture(const std::string &imagePath, unsigned int color_mode){
    ID = 0;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carrega imagem 1
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // Copia data para a textura
        glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    // Libera memoria da imagem
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(0);
}

void Texture::bind(int textureUnit){
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

unsigned int Texture::getID() const{
    return ID;
}