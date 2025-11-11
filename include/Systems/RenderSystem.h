#pragma once

#include <Graphics/Shader.h>
#include <Graphics/Mesh.h>
#include <ECS/Registry.h>

#include <memory>
#include <glm/glm.hpp>

namespace Systems {
    class RenderSystem {
    private:
        std::unique_ptr<Graphics::Shader> _shader;
        std::unique_ptr<Graphics::Mesh> _quadMesh;
        glm::mat4 _projection;

    public:
        RenderSystem();
        
        void Init(int screenWidth, int screenHeight);
        void Draw(ECS::Registry& registry);
    };
}
