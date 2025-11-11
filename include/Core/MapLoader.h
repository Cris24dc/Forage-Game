#pragma once

#include <ECS/Registry.h>
#include <Graphics/Texture.h>

#include <string>
#include <memory>

namespace Core {
    class MapLoader {
    private:
        std::shared_ptr<Graphics::Texture> _tileSheet;
        int _sheetWidthInTiles; 
        int _sheetHeightInTiles;
        int _tileWidth;
        int _tileHeight;

    public:
        MapLoader(std::shared_ptr<Graphics::Texture> tileSheet, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight);
        ~MapLoader() = default;

        void LoadMap(const std::string& filePath, ECS::Registry& registry);
    };
}
