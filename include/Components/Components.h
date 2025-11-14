#pragma once

#include <Graphics/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace Components {
    struct Transform {
    public:
        glm::vec2 position{0.0f, 0.0f};
        glm::vec2 scale{1.0f, 1.0f};
        float rotation{0.0f};
        uint32_t sortingOrder{0};
    };

    struct Sprite {
    private:
    void updateUVs() {
        uvScale = glm::vec2(1.0f / columns, 1.0f / rows);
        uvOffset = glm::vec2(currentColumn * uvScale.x, currentRow * uvScale.y);
    }

    public:
        std::shared_ptr<Graphics::Texture> texture{nullptr};
        glm::vec3 color{1.0f, 1.0f, 1.0f};
        glm::vec2 uvScale{1.0f, 1.0f};
        glm::vec2 uvOffset{0.0f, 0.0f};
        bool flipX{false};

        int rows{1};
        int columns{1};
        int currentRow{0};
        int currentColumn{0};

        void setSpriteSheetCell(int row, int col) {
            currentRow = row;
            currentColumn = col;
            updateUVs();
        }
    };
}
