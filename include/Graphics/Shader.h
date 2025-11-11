#pragma once

#include <string>
#include <cstdint>

namespace Graphics {
    class Shader {
    private:
        std::uint32_t _programID;
        std::string loadShader(const std::string &filename);
        void createProgram(const std::string &vertexSource, const std::string &fragmentSource);
        
    public:
        Shader(const std::string &vertexSource, const std::string &fragmentSource);
        ~Shader();
        
        void use() const;
        std::uint32_t getProgramID() const;
    };
}
