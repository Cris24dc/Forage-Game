#include <Core/MapLoader.h>
#include <ECS/Components.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Core {
    MapLoader::MapLoader(std::shared_ptr<Graphics::Texture> tileSheet, int sheetWidth, int sheetHeight, int tileWidth, int tileHeight)
    : _tileSheet(tileSheet),
        _sheetWidthInTiles(sheetWidth),
        _sheetHeightInTiles(sheetHeight),
        _tileWidth(tileWidth),
        _tileHeight(tileHeight) {}

    void MapLoader::LoadMap(const std::string& filePath, ECS::Registry& registry) {
        std::ifstream file(filePath);
        std::string line;
        
        std::vector<std::vector<int>> mapData;

        while (std::getline(file, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            int tileID;
            while (ss >> tileID) {
                row.push_back(tileID);
            }
            mapData.push_back(row);
        }
        file.close();

        glm::vec2 uvScale = { 
            1.0f / (float)_sheetWidthInTiles, 
            1.0f / (float)_sheetHeightInTiles 
        };

        for (int y = 0; y < mapData.size(); ++y) {
            for (int x = 0; x < mapData[y].size(); ++x) {
                
                int tileID = mapData[y][x];

                float worldX = (float)x * _tileWidth + (_tileWidth / 2.0f);
                float worldY = (float)(mapData.size() - 1 - y) * _tileHeight + (_tileHeight / 2.0f);

                int uv_x = tileID % _sheetWidthInTiles;
                int uv_y = tileID / _sheetWidthInTiles;
                
                glm::vec2 uvOffset = {
                    (float)uv_x * uvScale.x,
                    (float)uv_y * uvScale.y
                };

                Entity tileEntity = registry.CreateEntity();

                registry.AddTransform(tileEntity, TransformComponent{
                    .position = { worldX, worldY },
                    .scale = { (float)_tileWidth, (float)_tileHeight }
                });

                registry.AddSprite(tileEntity, SpriteComponent{
                    .texture = _tileSheet,
                    .color = {1.0f, 1.0f, 1.0f, 1.0f},
                    .uvOffset = uvOffset,
                    .uvScale = uvScale,
                    .layer = 0,
                    .flipX = false,
                });
            }
        }
    }
}