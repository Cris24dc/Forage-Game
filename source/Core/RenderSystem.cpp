#include <Core/RenderSystem.h>
#include <Core/Components.h>

#include <glm/gtc/type_ptr.hpp>

namespace Core {
    RenderSystem::RenderSystem() {
        _shader = std::make_unique<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
        _quadMesh = std::make_unique<Mesh>();
    }

    void RenderSystem::Init(int screenWidth, int screenHeight) {
        _projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    }

    void RenderSystem::Draw(Registry& registry) {
        _shader->use();
        
        glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "uProjection"), 1, GL_FALSE, glm::value_ptr(_projection));

        const int maxLayers = 3;

        for (int layer = 0; layer < maxLayers; layer++) {
            for (Entity e = 0; e < MAX_ENTITIES; e++) {

                if (registry.HasTransform(e) && registry.HasSprite(e)) {
                    auto& sprite = registry.GetSprite(e);
                    auto& transform = registry.GetTransform(e);
                    
                    if (sprite.layer != layer) {
                        continue;
                    }

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(transform.position, 0.0f));
                    model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
                    glm::vec2 finalScale = transform.scale;
                    if (sprite.flipX) {
                        finalScale.x *= -1.0f;
                    }
                    model = glm::scale(model, glm::vec3(finalScale, 1.0f));
                    
                    glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "uModel"), 1, GL_FALSE, glm::value_ptr(model));
                    glUniform4f(glGetUniformLocation(_shader->getProgramID(), "uColorTint"), sprite.color.r, sprite.color.g, sprite.color.b, sprite.color.a);
                    glUniform2f(glGetUniformLocation(_shader->getProgramID(), "uUvOffset"), sprite.uvOffset.x, sprite.uvOffset.y);
                    glUniform2f(glGetUniformLocation(_shader->getProgramID(), "uUvScale"), sprite.uvScale.x, sprite.uvScale.y);

                    sprite.texture->bind(GL_TEXTURE0);
                    glUniform1i(glGetUniformLocation(_shader->getProgramID(), "uTexture"), 0);

                    _quadMesh->draw();
                }
            }
        }
    }
}