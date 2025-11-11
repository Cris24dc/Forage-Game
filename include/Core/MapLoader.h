#pragma once

#include <Core/Registry.h>
#include <Core/Texture.h>

#include <string>
#include <memory>

namespace Core {
    class MapLoader {
    private:
        std::shared_ptr<Texture> _tileSheet;
        int _sheetWidthInTiles; 
        int _sheetHeightInTiles;
        int _tileWidth;
        int _tileHeight;

    public:
        MapLoader(std::shared_ptr<Texture> tileSheet, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight);
        ~MapLoader() = default;

        void LoadMap(const std::string& filePath, Registry& registry);
    };
}
