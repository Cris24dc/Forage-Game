#include <Systems/RenderSystem.h>

namespace Systems {
    RenderSystem::RenderSystem(int screenWidth, int screenHeight) {
        _shader = std::make_unique<Graphics::Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
        _quadMesh = std::make_unique<Graphics::Mesh>();
        _projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    }

    void RenderSystem::draw(ECS::Registry& registry) {
        _shader->use();
        glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "uProjection"), 1, GL_FALSE, glm::value_ptr(_projection));

        for (ECS::Entity e = 0; e < ECS::MaxEntities; e++) {
            if (registry.hasComponent<Components::Transform>(e) && registry.hasComponent<Components::Sprite>(e)) {
                auto& transform = registry.getComponent<Components::Transform>(e);
                auto& sprite = registry.getComponent<Components::Sprite>(e);



                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(transform.position, 0.0f));
                model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
                glm::vec2 finalScale = transform.scale;
                if (sprite.flipX) {
                    finalScale.x *= -1.0f;
                }
                model = glm::scale(model, glm::vec3(finalScale, 1.0f));
                
                glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "uModel"), 1, GL_FALSE, glm::value_ptr(model));
                glUniform3f(glGetUniformLocation(_shader->getProgramID(), "uColorTint"), sprite.color.r, sprite.color.g, sprite.color.b);
                glUniform2f(glGetUniformLocation(_shader->getProgramID(), "uUvOffset"), sprite.uvOffset.x, sprite.uvOffset.y);
                glUniform2f(glGetUniformLocation(_shader->getProgramID(), "uUvScale"), sprite.uvScale.x, sprite.uvScale.y);

                sprite.texture->bind(GL_TEXTURE0);
                glUniform1i(glGetUniformLocation(_shader->getProgramID(), "uTexture"), 0);



                _quadMesh->draw();
            }
        }
    }
}