#ifndef PLATFORMER_GAME_TILECONFIG_HPP
#define PLATFORMER_GAME_TILECONFIG_HPP

#include <functional>
#include <map>
#include <memory>

#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectDirector.hpp"

const auto TILESIZE = 16;
struct SpriteSheetInfo {
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};
struct SheetPos {
    int x;
    int y;
};
/**
 * @brief contains information about a tile
 *      the id is the number of the sprite in the spritesheet, uses zero-based numbering like this:
 *      0 1 2
 *      3 4 5
 *      6 7 8
 */
struct SpriteInfo {
    int id;
    std::string objectId;
    std::string path;
    SheetPos sheetPos;
};

class TileConfig {
public:
    static auto Level1() -> std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> {
        std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> config {};
        auto spriteSheetInfo = SpriteSheetInfo{8, 8, 16, 16};

        auto sprite1Info = SpriteInfo{1, "floor1",
                                      "./resources/levels/mario/Tilesets/Tiles/floor1.png",
                                      GetSheetPos(1, spriteSheetInfo)};
        AddToConfig(config, sprite1Info, spriteSheetInfo);

        platformer_engine::TextureManager::GetInstance().LoadTexture("brick1", "./resources/levels/mario/Tilesets/Overworld.png");
        auto sprite4 = std::make_shared<spic::Sprite>("brick1", 1, 1, 16, 16,
                                                      platformer_engine::FLIP_NONE,
                                                      Color::Transparent(), 1.0, 3 * 16, 0);

        config.insert({4, [sprite4](Transform transform){ return GameObjectDirector::CreateTile(sprite4, transform);}});

//        auto foo = GetSheetPos(10, 8, 8, TILESIZE);
//        std::cout << foo.x << "-" << foo.y;
        // a bigger object can just have a bigger sprite-width/height, but then it cant be partially rendered

        return config;
    }
private:
    static void AddToConfig(
            std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>>& config,
            const SpriteInfo& sprite, const SpriteSheetInfo& spriteSheet) {
        platformer_engine::TextureManager::GetInstance().LoadTexture(sprite.objectId, sprite.path);
        auto spriteObj = std::make_shared<spic::Sprite>(sprite.objectId, 1, 1,
                                                        spriteSheet.tileWidth, spriteSheet.tileHeight,
                                                      platformer_engine::FLIP_NONE,
                                                      Color::Transparent(), 1.0, sprite.sheetPos.x, sprite.sheetPos.y);
        config.insert(
                {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateTile(spriteObj, transform);}});
    }

    static auto GetSheetPos(int sheetNo, SpriteSheetInfo spriteSheet) -> SheetPos {
        int x = sheetNo % spriteSheet.columns - 1;
        int y = sheetNo / spriteSheet.rows;
        return {x * spriteSheet.tileWidth, y * spriteSheet.tileHeight};
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
