#include <Graphics/Shader.h>

#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {
    Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
        createProgram(vertexSource, fragmentSource);
    }

    Shader::~Shader() {
        glDeleteProgram(_programID);
    }

    std::string Shader::loadShader(const std::string &filename) {
        std::ifstream file(filename);
        std::stringstream stream;
        
        stream << file.rdbuf();

        file.close();
        return stream.str();
    }

    void Shader::createProgram(const std::string &vertexSource, const std::string &fragmentSource) {
        std::string vertexSourceString = loadShader(vertexSource);
        const char* GLvertexSource = vertexSourceString.c_str();
        std::string fragmentSourceString = loadShader(fragmentSource);
        const char* GLfragmentSource = fragmentSourceString.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader, 1, &GLvertexSource, nullptr);
        glShaderSource(fragmentShader, 1, &GLfragmentSource, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        _programID = glCreateProgram();
        glAttachShader(_programID, vertexShader);
        glAttachShader(_programID, fragmentShader);
        glLinkProgram(_programID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::use() const {
        glUseProgram(_programID);
    }

    std::uint32_t Shader::getProgramID() const {
        return _programID;
    }
}