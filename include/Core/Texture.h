#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>

namespace Core {
    class Texture {
    private:
        GLuint _id;
        int _width;
        int _height;
        int _nrChannels;

    public:
        Texture(const std::string& filepath);
        ~Texture();

        void bind(GLenum textureUnit = GL_TEXTURE0) const;
        void unbind() const;
    };
}
