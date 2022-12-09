#ifndef PLATFORMER_GAME_TILECONFIG_HPP
#define PLATFORMER_GAME_TILECONFIG_HPP

#include <functional>
#include <map>
#include <memory>

#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Scripts/FlagBehaviour.hpp"

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
    static auto Map1() -> std::map<int, std::function<GameObject(Transform)>> {
        const auto OVERWORLDPATH = "./resources/levels/mario/Tilesets/Overworld.png";
        const auto OVERWORLDSHEETSIZE = 8;

        const auto ITEMSPATH = "./resources/levels/mario/Misc/Items.png";
        const auto ITEMSSHEETROWS = 3;
        const auto ITEMSSHEETCOLUMNS = 5;

        std::map<int, std::function<GameObject(Transform)>> config {};
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
                                          spriteId, spriteNo, "overworldtile", OVERWORLDPATH,
                                          GetSheetPos(spriteNo, overworldSheet)
                                  });
            }
        }

        // add item tiles
        spriteNo = 0;
        for (int rows = 0; rows < itemsSheet.rows; ++rows) {
            ++spriteId;
            ++spriteNo;
            sprites.push_back({
                                      spriteId, spriteNo, "itemtile", ITEMSPATH,
                                      GetSheetPos(spriteNo, itemsSheet)
                              });      for (int columns = 0; columns < itemsSheet.columns; ++columns) {

            }
        }

        // add all functions to the config
        for (auto& sprite : sprites) {
            AddToConfig(config, sprite, overworldSheet, SpriteType::Tile);
        }
        return config;
    }

    static auto World1() -> std::map<int, std::function<GameObject(Transform)>> {
        std::map<int, std::function<GameObject(Transform)>> config {};

        const auto BLOCKSPATH = "./resources/levels/mario/Tilesets/blocks1.png";
        const auto BLOCKSSHEETROWS = 2;
        const auto BLOCKSSHEETCOLS = 5;

        const auto ITEMSPATH = "./resources/levels/mario/Tilesets/interactable1.png";
        const auto ITEMSSHEETROWS = 1;
        const auto ITEMSSHEETCOLS = 5;

        const auto BACKGROUNDPATH = "./resources/levels/mario/Tilesets/background1.png";
        const auto BACKGROUNDROWS = 4;
        const auto BACKGROUNDCOLS = 8;

        const auto FLAGPATH = "./resources/levels/mario/Tilesets/flag.png";
        const auto FLAGROWS = 3;
        const auto FLAGCOLS = 1;

        auto blocksSheet = SpriteSheetInfo{BLOCKSSHEETROWS, BLOCKSSHEETCOLS, TILESIZE, TILESIZE};
        auto backgroundSheet = SpriteSheetInfo{BACKGROUNDROWS, BACKGROUNDCOLS, TILESIZE, TILESIZE};
        auto itemsSheet = SpriteSheetInfo{ITEMSSHEETROWS, ITEMSSHEETCOLS, TILESIZE, TILESIZE};
        auto flagSheet = SpriteSheetInfo{FLAGROWS, FLAGCOLS, TILESIZE, TILESIZE};

        // create all info for the sprites
        auto tileSprites = std::vector<SpriteInfo> {};
        auto backgroundSprites = std::vector<SpriteInfo> {};
        auto interactableSprites = std::vector<SpriteInfo> {};
        auto flagSprites = std::vector<SpriteInfo> {};

        // add block tiles
        int spriteId = 0;
        int spriteNo = 0;
        for (int rows = 0; rows < blocksSheet.rows; ++rows) {
            for (int columns = 0; columns < blocksSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                tileSprites.push_back({
                                              spriteId, spriteNo, "overworldtile", BLOCKSPATH,
                                              GetSheetPos(spriteNo, blocksSheet)
                                      });
            }
        }

        // add background tiles
        spriteNo = 0;
        for (int rows = 0; rows < backgroundSheet.rows; ++rows) {
            for (int columns = 0; columns < backgroundSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                interactableSprites.push_back({
                                                      spriteId, spriteNo, "itemtile", BACKGROUNDPATH,
                                                      GetSheetPos(spriteNo, backgroundSheet)
                                              });
            }
        }

        // add item tiles
        spriteNo = 0;
        for (int rows = 0; rows < itemsSheet.rows; ++rows) {
            for (int columns = 0; columns < itemsSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                interactableSprites.push_back({
                                                      spriteId, spriteNo, "itemtile", ITEMSPATH,
                                                      GetSheetPos(spriteNo, itemsSheet)
                                              });
            }
        }

        // add flag tiles
        spriteNo = 0;
        for(int rows = 0; rows < flagSheet.rows; ++rows) {
            for(int columns = 0; columns < flagSheet.columns; columns++) {
                ++spriteId;
                ++spriteNo;
                flagSprites.push_back({
                    spriteId, spriteNo, "flagtile" + std::to_string(spriteId), FLAGPATH, GetSheetPos(spriteNo, flagSheet)
                });
            }
        }

        // add all functions to the config
        for (auto& sprite : tileSprites) {
            AddToConfig(config, sprite, blocksSheet, SpriteType::Tile);
        }
        for (auto& sprite : backgroundSprites) {
            AddToConfig(config, sprite, backgroundSheet, SpriteType::Backgorund);
        }
        for (auto& sprite : interactableSprites) { // TODO: change when interactable tiles are added
            AddToConfig(config, sprite, itemsSheet, SpriteType::Backgorund);
        }

        for(auto& sprite : flagSprites) {
            AddToConfig(config, sprite, flagSheet, SpriteType::Flag);
        }

        return config;
    }

private:
    enum SpriteType { Tile, Backgorund, Flag };

    static auto GetSheetPos(int sheetNo, SpriteSheetInfo spriteSheet) -> SheetPos {
        int x = (sheetNo - 1) % spriteSheet.columns;
        int y = (sheetNo - 1) / spriteSheet.columns;
        return {x * spriteSheet.tileWidth, y * spriteSheet.tileHeight};
    }

    static void AddToConfig(
            std::map<int, std::function<GameObject(Transform)>>& config,
            const SpriteInfo& sprite, const SpriteSheetInfo& spriteSheet,
            const SpriteType type
            ) {
        platformer_engine::TextureManager::GetInstance().LoadTexture(sprite.objectId, sprite.path);
        auto spriteObj = spic::Sprite(sprite.objectId, spriteSheet.tileWidth, spriteSheet.tileHeight);
        spriteObj.SetSpriteSheetPosition(sprite.sheetPos.x, sprite.sheetPos.y);
        if (type == SpriteType::Tile) {
            config.insert(
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateTile(spriteObj, transform, TILESIZE, TILESIZE);}});
        }
        else if(type == SpriteType::Flag) {
            const std::vector<std::shared_ptr<BehaviourScript>> scripts { std::make_shared<BehaviourScript>(PlatformerGame::FlagBehaviour ()) };

            config.insert(
                    {sprite.id, [spriteObj, scripts](Transform transform){ return GameObjectDirector::CreateFlag(spriteObj, transform, TILESIZE, TILESIZE, scripts );}});
        } else //SpriteType::Background
            config.insert(
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateBackgroundObject(spriteObj, transform);}});
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
