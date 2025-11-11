#include <Graphics/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <iostream>

namespace Graphics {
    Texture::Texture(const std::string& filepath) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load(filepath.c_str(), &_width, &_height, &_nrChannels, 0);

        GLenum format = (_nrChannels == 4) ? GL_RGBA : GL_RGB;
        GLenum internalFormat = (_nrChannels == 4) ? GL_RGBA8 : GL_RGB8;

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_id);
    }

    void Texture::bind(GLenum textureUnit) const {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
