#ifndef PLATFORMER_GAME_TILECONFIG_HPP
#define PLATFORMER_GAME_TILECONFIG_HPP

#include <functional>
#include <map>
#include <memory>

#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectDirector.hpp"

const auto OVERWORLDPATH = "./resources/levels/mario/Tilesets/Overworld.png";
const auto OVERWORLDSHEETSIZE = 8;
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
 *      1 2 3
 *      4 5 6
 *      7 8 9
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
        auto spriteSheetInfo = SpriteSheetInfo{OVERWORLDSHEETSIZE, OVERWORLDSHEETSIZE, TILESIZE, TILESIZE};

        // create all info for the sprites
        auto sprites = std::vector<SpriteInfo> {};

        int spriteId = 0;
        // add overworld tiles
        for (int rows = 0; rows < spriteSheetInfo.rows; ++rows) {
            for (int columns = 0; columns < spriteSheetInfo.columns; ++columns) {
                ++spriteId;
                sprites.push_back({
                       spriteId, "overworldtile" + std::to_string(spriteId), OVERWORLDPATH,
                       GetSheetPos(spriteId, spriteSheetInfo)
                });
            }
        }

        // add all functions to the config
        for (auto& sprite : sprites) {
            AddToConfig(config, sprite, spriteSheetInfo);
        }
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
        // dont cut off the last tile in column
        int x = (sheetNo - 1) % spriteSheet.columns;
        int y = (sheetNo - 1) / spriteSheet.rows;
        return {x * spriteSheet.tileWidth, y * spriteSheet.tileHeight};
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
