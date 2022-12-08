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

        auto blocksSheet = SpriteSheetInfo{BLOCKSSHEETROWS, BLOCKSSHEETCOLS, TILESIZE, TILESIZE};
        auto backgroundSheet = SpriteSheetInfo{BACKGROUNDROWS, BACKGROUNDCOLS, TILESIZE, TILESIZE};
        auto itemsSheet = SpriteSheetInfo{ITEMSSHEETROWS, ITEMSSHEETCOLS, TILESIZE, TILESIZE};

        // create all info for the sprites
        auto tileSprites = std::vector<SpriteInfo> {};
        auto backgroundSprites = std::vector<SpriteInfo> {};
        auto interactableSprites = std::vector<SpriteInfo> {};

        // add block tiles
        int spriteId = 0;
        int spriteNo = 0;
        for (int rows = 0; rows < blocksSheet.rows; ++rows) {
            for (int columns = 0; columns < blocksSheet.columns; ++columns) {
                ++spriteId;
                ++spriteNo;
                tileSprites.push_back({
                                              spriteId, spriteNo, "overworldtile" + std::to_string(spriteId), BLOCKSPATH,
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
                backgroundSprites.push_back({
                                                      spriteId, spriteNo, "itemtile" + std::to_string(spriteId), BACKGROUNDPATH,
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
                                                      spriteId, spriteNo, "itemtile" + std::to_string(spriteId), ITEMSPATH,
                                                      GetSheetPos(spriteNo, itemsSheet)
                                              });
            }
        }

        // add all functions to the config
        for (auto& sprite : tileSprites) {
            AddToConfig(config, sprite, blocksSheet);
        }
        for (auto& sprite : backgroundSprites) {
            AddToConfig(config, sprite, backgroundSheet, true);
        }
//        for (auto& sprite : interactableSprites) {
//           AddToConfig(config, sprite, itemsSheet, true);
//        }

        // TODO: mushroom
        // TODO: extra life
        // TODO: flower
        // TODO: star
        // coin
        auto coinSprite = interactableSprites[4];
        platformer_engine::TextureManager::GetInstance().LoadTexture(coinSprite.objectId, coinSprite.path);
        auto coinSpriteObj = spic::Sprite(coinSprite.objectId, itemsSheet.tileWidth, itemsSheet.tileHeight);
        coinSpriteObj.SetSpriteSheetPosition(coinSprite.sheetPos.x, coinSprite.sheetPos.y);
        config.insert(
                {coinSprite.id, [coinSpriteObj](Transform transform){
                    // TODO: gameDirector CreateInteractable that does not block movement and has a behaviourscript (or multiple)
                    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
                    auto builder =
                            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                                    .AddSprite(coinSpriteObj)
                    ;
                    auto obj = builder.GetGameObject();
                    obj->SetTransform(transform);

                    // collider
                    auto collider = BoxCollider();
                    collider.Width(TILESIZE);
                    collider.Height(TILESIZE);
                    collider.SetObstructsMovement(false);
                    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

                    scene.AddObject(obj);
                    return *obj;
                }});

        return config;
    }

private:
    static auto GetSheetPos(int sheetNo, SpriteSheetInfo spriteSheet) -> SheetPos {
        int x = (sheetNo - 1) % spriteSheet.columns;
        int y = (sheetNo - 1) / spriteSheet.columns;
        return {x * spriteSheet.tileWidth, y * spriteSheet.tileHeight};
    }

    static void AddToConfig(
            std::map<int, std::function<GameObject(Transform)>>& config,
            const SpriteInfo& sprite, const SpriteSheetInfo& spriteSheet,
            const bool isBackground = false
            ) {
        platformer_engine::TextureManager::GetInstance().LoadTexture(sprite.objectId, sprite.path);
        auto spriteObj = spic::Sprite(sprite.objectId, spriteSheet.tileWidth, spriteSheet.tileHeight);
        spriteObj.SetSpriteSheetPosition(sprite.sheetPos.x, sprite.sheetPos.y);
        if (!isBackground)
            config.insert(
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateTile(spriteObj, transform, TILESIZE, TILESIZE);}});
        else
            config.insert(
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectDirector::CreateBackgroundObject(spriteObj, transform);}});
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
