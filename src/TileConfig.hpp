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

const auto ITEMSPATH = "./resources/levels/mario/Misc/Items.png";
const auto ITEMSSHEETROWS = 3;
const auto ITEMSSHEETCOLUMNS = 5;

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
 * the id is the key through which the tile create method is accessed
 * the numberInSheet is the number of the sprite in the spritesheet, like this:
 *      1 2 3
 *      4 5 6
 *      7 8 9
 */
struct SpriteInfo {
    int id;
    int numberInSheet;
    std::string objectId;
    std::string path;
    SheetPos sheetPos;
};

class TileConfig {
public:
    static auto Level1() -> std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> {
        std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> config {};
        // TODO: we could even add the sheets to a vector to iterate over them
        auto overworldSheet = SpriteSheetInfo{OVERWORLDSHEETSIZE, OVERWORLDSHEETSIZE, TILESIZE, TILESIZE};
        auto itemsSheet = SpriteSheetInfo{ITEMSSHEETROWS, ITEMSSHEETCOLUMNS, TILESIZE, TILESIZE};

        // create all info for the sprites
        auto sprites = std::vector<SpriteInfo> {};

        // add overworld tiles
        int spriteId = 0;
        int spriteNo = 0;
        for (int rows = 0; rows < overworldSheet.rows; ++rows) {
            for (int columns = 0; columns < overworldSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                sprites.push_back({
                       spriteId, spriteNo, "overworldtile" + std::to_string(spriteId), OVERWORLDPATH,
                       GetSheetPos(spriteNo, overworldSheet)
                });
            }
        }

        // add item tiles
        spriteNo = 0;
        for (int rows = 0; rows < itemsSheet.rows; ++rows) {
            for (int columns = 0; columns < itemsSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                sprites.push_back({
                       spriteId, spriteNo, "itemtile" + std::to_string(spriteId), ITEMSPATH,
                       GetSheetPos(spriteNo, itemsSheet)
                });
            }
        }

        // add all functions to the config
        for (auto& sprite : sprites) {
            AddToConfig(config, sprite, overworldSheet);
        }
        return config;
    }

private:
    static auto GetSheetPos(int sheetNo, SpriteSheetInfo spriteSheet) -> SheetPos {
        int x = (sheetNo - 1) % spriteSheet.columns;
        int y = (sheetNo - 1) / spriteSheet.columns;
        return {x * spriteSheet.tileWidth, y * spriteSheet.tileHeight};
    }

    static void AddToConfig(
            std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>>& config,
            const SpriteInfo& sprite, const SpriteSheetInfo& spriteSheet) {
        platformer_engine::TextureManager::GetInstance().LoadTexture(sprite.objectId, sprite.path);
        auto spriteObj = spic::Sprite(sprite.objectId, spriteSheet.tileWidth, spriteSheet.tileHeight);
        spriteObj.SetSpriteSheetPosition(sprite.sheetPos.x, sprite.sheetPos.y);
        config.insert(
                {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateTile(spriteObj, transform, TILESIZE, TILESIZE);}});
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
