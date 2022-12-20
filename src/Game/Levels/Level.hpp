#ifndef PLATFORMER_GAME_LEVEL_HPP
#define PLATFORMER_GAME_LEVEL_HPP

#include "Scene.hpp"
#include "constants/Sprites.hpp"
#include "Engine/Engine.hpp"

class Level {
public:

protected:
    static const int DEFAULT_LAYER = 1;
    static const int DEFAULT_SPEED = 100;
    static const int DEFAULT_ROW = 1;
    static const int DEFAULT_PLAYER_WIDTH = 15;
    static const int DEFAULT_PLAYER_HEIGHT = 17;

    static void LoadAnimatedSprite(std::vector<platformer_engine::AnimatedSprite> &spriteList, std::string spriteId,
                            std::string path, int spriteWidth, int spriteHeight, int frameCount) {
        std::string spriteIdFlipped = spriteId + constants::HORIZONTAL_FLIP_SUFFIX;
        platformer_engine::TextureManager::GetInstance().LoadTexture(spriteId, path);
        platformer_engine::TextureManager::GetInstance().LoadTexture(spriteIdFlipped, path);
        auto idleSprite = platformer_engine::AnimatedSprite(spriteId, spriteWidth, spriteHeight, frameCount);
        auto idleSpriteFlipped = platformer_engine::AnimatedSprite(spriteIdFlipped, spriteWidth, spriteHeight, frameCount,
                                                                   DEFAULT_LAYER, DEFAULT_LAYER, DEFAULT_SPEED, DEFAULT_ROW,
                                                                   platformer_engine::FLIP_HORIZONTAL);
        spriteList.push_back(idleSpriteFlipped);
        spriteList.push_back(idleSprite); // TODO: last loaded sprite is visible upon spawn
    }
};

#endif //PLATFORMER_GAME_LEVEL_HPP