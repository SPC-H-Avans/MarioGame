#ifndef PLATFORMER_GAME_TILECONFIG_HPP
#define PLATFORMER_GAME_TILECONFIG_HPP

#include <functional>
#include <map>
#include <memory>

#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectDirector.hpp"

const auto TILESIZE = 16;
struct SheetPos {
    int x;
    int y;
};

class TileConfig {
public:
    static auto Level1() -> std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> {
        platformer_engine::TextureManager::GetInstance().LoadTexture("floor1", "./resources/levels/mario/Tilesets/Tiles/floor1.png");
        auto sprite1 = std::make_shared<spic::Sprite>("floor1", 1, 1, TILESIZE, TILESIZE);

        platformer_engine::TextureManager::GetInstance().LoadTexture("brick1", "./resources/levels/mario/Tilesets/Overworld.png");
        auto sprite4 = std::make_shared<spic::Sprite>("brick1", 1, 1, 16, 16,
                                                      platformer_engine::FLIP_NONE,
                                                      Color::Transparent(), 1.0, 3 * 16, 0);
        auto foo = GetSheetPos(10, 8, 8, TILESIZE);
        std::cout << foo.x << "-" << foo.y;
        // a bigger object can just have a bigger width/height

        return {
                {1, [sprite1](Transform transform){ return GameObjectDirector::CreateTile(sprite1, transform);}}, // 1 is normal floor
                {4, [sprite4](Transform transform){ return GameObjectDirector::CreateTile(sprite4, transform);}}, // 4 is breakable block
        };
    }
private:
    /**
     * @brief gets the right x and y position in pixels on the spritesheet
     * @param sheetRows is the number of rows the spritesheet has
     * @param sheetCols is the number of columns the spritesheet has
     * @param tileSize is the size of a sprite in the spriteSheet
     * @param sheetNo is the position of the sprite on the spritesheet, uses zero-based numbering
     *      like this:
     *      0 1 2
     *      3 4 5
     *      6 7 8
     */
    static auto GetSheetPos(int sheetNo, int sheetRows, int sheetCols, int tileSize) -> SheetPos {
        int x = sheetNo % sheetCols - 1;
        int y = sheetNo / sheetRows;
        return {x * tileSize, y * tileSize};
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
