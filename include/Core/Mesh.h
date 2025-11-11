#pragma once

#include <cstdint>

namespace Core {
    class Mesh {
    private:
        std::uint32_t _vao, _vbo, _ebo;
        
    public:
        Mesh();
        ~Mesh();

        void draw() const;
    };
}
