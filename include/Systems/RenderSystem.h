#pragma once

#include <Graphics/Shader.h>
#include <Graphics/Mesh.h>
#include <Components/Components.h>
#include <ECS/Registry.h>
#include <ECS/Entity.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace Systems {
    class RenderSystem {
    private:
        std::unique_ptr<Graphics::Shader> _shader;
        std::unique_ptr<Graphics::Mesh> _quadMesh;
        glm::mat4 _projection;

    public:
        RenderSystem(int screenWidth, int screenHeight);
        ~RenderSystem() = default;

        void draw(ECS::Registry& registry);
    };
}
