#pragma once

#include <Core/Shader.h>
#include <Core/Mesh.h>
#include <Core/Registry.h>

#include <memory>
#include <glm/glm.hpp>

namespace Core {
    class RenderSystem {
    private:
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<Mesh> _quadMesh;
        glm::mat4 _projection;

    public:
        RenderSystem();
        
        void Init(int screenWidth, int screenHeight);
        void Draw(Registry& registry);
    };
}
