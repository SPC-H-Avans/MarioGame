#ifndef PLATFORMER_GAME_TILECONFIG_HPP
#define PLATFORMER_GAME_TILECONFIG_HPP

#include <functional>
#include <map>
#include <memory>

#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Scripts/CoinBehaviour.hpp"
#include "Scripts/FlagBehaviour.hpp"
#include "Scripts/StarBehaviour.hpp"
#include "UI/CoinCounter.hpp"
#include "Scripts/EnemyAttackBehaviour.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Physics/ForceDrivenEntity.hpp"

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
    static auto World1(const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter) -> std::map<int, std::function<GameObject(Transform)>> {
        std::map<int, std::function<GameObject(Transform)>> config {};

        const auto BLOCKSPATH = "./resources/levels/mario/Tilesets/blocks1.png";
        const auto BLOCKSSHEETROWS = 2;
        const auto BLOCKSSHEETCOLS = 5;

        const auto BACKGROUNDPATH = "./resources/levels/mario/Tilesets/background1.png";
        const auto BACKGROUNDROWS = 4;
        const auto BACKGROUNDCOLS = 8;

        const auto ITEMSPATH = "./resources/levels/mario/Tilesets/interactable1.png";
        const auto ITEMSSHEETROWS = 1;
        const auto ITEMSSHEETCOLS = 5;

        const auto FLAGPATH = "./resources/levels/mario/Tilesets/flag.png";
        const auto FLAGROWS = 3;
        const auto FLAGCOLS = 1;

        const auto ENEMIESPATH = "./resources/levels/mario/Tilesets/enemies.png";
        const auto ENEMIESROWS = 2;
        const auto ENEMIESCOLS = 1;

        auto blocksSheet = SpriteSheetInfo{BLOCKSSHEETROWS, BLOCKSSHEETCOLS, TILESIZE, TILESIZE};
        auto backgroundSheet = SpriteSheetInfo{BACKGROUNDROWS, BACKGROUNDCOLS, TILESIZE, TILESIZE};
        auto itemsSheet = SpriteSheetInfo{ITEMSSHEETROWS, ITEMSSHEETCOLS, TILESIZE, TILESIZE};
        auto flagSheet = SpriteSheetInfo{FLAGROWS, FLAGCOLS, TILESIZE, TILESIZE};
        auto enemiesSheet = SpriteSheetInfo{ENEMIESROWS, ENEMIESCOLS, TILESIZE, TILESIZE};

        // create all info for the sprites
        auto tileSprites = std::vector<SpriteInfo> {};
        auto backgroundSprites = std::vector<SpriteInfo> {};
        auto interactableSprites = std::vector<SpriteInfo> {};
        auto flagSprites = std::vector<SpriteInfo> {};
        auto enemySprites = std::vector<SpriteInfo> {};

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
                backgroundSprites.push_back({
                                                      spriteId, spriteNo, "backgroundtile", BACKGROUNDPATH,
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

        // add enemy tiles
        spriteNo = 0;
        for(int rows = 0; rows < enemiesSheet.rows; ++rows) {
            for(int columns = 0; columns < enemiesSheet.columns; columns++) {
                ++spriteId;
                ++spriteNo;
                enemySprites.push_back({
                                              spriteId, spriteNo, "enemytile" + std::to_string(spriteId), ENEMIESPATH, GetSheetPos(spriteNo, enemiesSheet)
                                      });
            }
        }

        // add all functions to the config
        for (auto& sprite : tileSprites) {
            AddToConfig(config, sprite, blocksSheet, SpriteType::Tile);
        }
        for (auto& sprite : backgroundSprites) {
            AddToConfig(config, sprite, backgroundSheet, SpriteType::Background);
        }
        for(auto& sprite : flagSprites) {
            AddToConfig(config, sprite, flagSheet, SpriteType::Flag);
        }

        // TODO: make a generic method to avoid repetition
        // TODO: mushroom
        // TODO: extra life
        // TODO: flower
        // star
        auto starSprite = interactableSprites[3];
        platformer_engine::TextureManager::GetInstance().LoadTexture(starSprite.objectId, starSprite.path);
        auto starSpriteObj = spic::Sprite(starSprite.objectId, itemsSheet.tileWidth, itemsSheet.tileHeight);
        starSpriteObj.SetSpriteSheetPosition(starSprite.sheetPos.x, starSprite.sheetPos.y);
        config.insert(
                {starSprite.id, [starSpriteObj](Transform transform){
                    std::vector<std::shared_ptr<BehaviourScript>> coinScripts = {std::make_shared<PlatformerGame::StarBehaviour>()};
                    return GameObjectFactory::CreateScriptedTile("coin", starSpriteObj, transform, TILESIZE, TILESIZE, false, coinScripts);
                }});

        // coin
        auto coinSprite = interactableSprites[4];
        platformer_engine::TextureManager::GetInstance().LoadTexture(coinSprite.objectId, coinSprite.path);
        auto coinSpriteObj = spic::Sprite(coinSprite.objectId, itemsSheet.tileWidth, itemsSheet.tileHeight);
        coinSpriteObj.SetSpriteSheetPosition(coinSprite.sheetPos.x, coinSprite.sheetPos.y);
        config.insert(
                {coinSprite.id, [coinSpriteObj, coinCounter](Transform transform){
                    std::vector<std::shared_ptr<BehaviourScript>> coinScripts = {std::make_shared<PlatformerGame::CoinBehaviour>(coinCounter)};
                    return GameObjectFactory::CreateScriptedTile("coin", coinSpriteObj, transform, TILESIZE, TILESIZE, false, coinScripts);
                }});

        // enemies
        // goomba, uses custom animated sprites instead of spritesheet sprite
        auto goombaSprite = enemySprites[0];
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_idle", "./resources/Sprites/Goomba/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_walk", "./resources/Sprites/Goomba/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_jump", "./resources/Sprites/Goomba/Fly.png");

        auto goombaIdleSprite = platformer_engine::AnimatedSprite("goomba_idle", TILESIZE, TILESIZE, 1);
        auto goombaWalkSprite = platformer_engine::AnimatedSprite("goomba_walk", TILESIZE, TILESIZE, 3);
        auto goombaJumpSprite = platformer_engine::AnimatedSprite("goomba_jump", TILESIZE, TILESIZE, 4);
        config.insert(
                {goombaSprite.id, [goombaIdleSprite, goombaWalkSprite, goombaJumpSprite](Transform transform){
                    auto goombaAnimations = std::vector<platformer_engine::AnimatedSprite>{goombaIdleSprite, goombaWalkSprite, goombaJumpSprite};
                    auto goombaBehaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                            std::make_shared<platformer_engine::CollisionBehaviour>(),
                            std::make_shared<EnemyAttackBehaviour>(),
                            std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(goombaIdleSprite, goombaWalkSprite, goombaJumpSprite)
                    };
                    auto goomba = GameObjectFactory::CreateEnemy(transform, TILESIZE, TILESIZE, goombaAnimations, goombaBehaviourScripts);

                    std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(goomba.GetComponent<platformer_engine::ForceDrivenEntity>());

                    return goomba;
                }});

        // TODO: koopa

        return config;
    }

private:
    enum SpriteType { Tile, Background, Flag };

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
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectFactory::CreateTile("tile", spriteObj, transform, TILESIZE, TILESIZE);}});
        }
        else if(type == SpriteType::Flag) {
            const std::vector<std::shared_ptr<BehaviourScript>> scripts { std::make_shared<PlatformerGame::FlagBehaviour>() };

            config.insert(
                    {sprite.id, [spriteObj, scripts](Transform transform){ return GameObjectFactory::CreateScriptedTile("flag", spriteObj, transform, TILESIZE, TILESIZE, true, scripts);}});
        } else //SpriteType::Background
            config.insert(
                    {sprite.id, [spriteObj](Transform transform){ return GameObjectFactory::CreateBackgroundObject("tile", spriteObj, transform);}});
    }
};
#endif //PLATFORMER_GAME_TILECONFIG_HPP
