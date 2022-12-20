#ifndef PLATFORMER_GAME_LEVEL_HPP
#define PLATFORMER_GAME_LEVEL_HPP

#include "Scene.hpp"
#include "constants/Sprites.hpp"
#include "Engine/Engine.hpp"
#include "UI/FPSCounter.hpp"
#include "Utility/InputEnum.hpp"
#include "AudioSource.hpp"
#include "Scripts/MarioBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Behaviour/CollisionBehaviour.hpp"

class Level {
public:

protected:
    static const int DEFAULT_LAYER = 1;
    static const int DEFAULT_SPEED = 100;
    static const int DEFAULT_ROW = 1;
    static const int DEFAULT_PLAYER_WIDTH = 15;
    static const int DEFAULT_PLAYER_HEIGHT = 17;
    static const int DEFAULT_FONT_SIZE = 50;
    inline static const std::string DEFAULT_FONT_PATH = "./resources/fonts/DefaultFont.ttf";
    inline static const Color DEFAULT_FONT_COLOUR = Color::Yellow();

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

    static auto LoadAnimations() -> std::vector<platformer_engine::AnimatedSprite> {
        auto animations = std::vector<platformer_engine::AnimatedSprite>();
        LoadAnimatedSprite(animations, constants::WALK_SPRITE_ID, "./resources/Sprites/Mario/Walk.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 3);
        LoadAnimatedSprite(animations, constants::JUMP_SPRITE_ID, "./resources/Sprites/Mario/Jump.png", DEFAULT_PLAYER_WIDTH + 1, DEFAULT_PLAYER_HEIGHT - 1, 1);
        LoadAnimatedSprite(animations, constants::IDLE_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Idle.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 6);
        LoadAnimatedSprite(animations, constants::WALK_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Walk.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 6);
        LoadAnimatedSprite(animations, constants::JUMP_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Jump.png", DEFAULT_PLAYER_WIDTH + 1, DEFAULT_PLAYER_HEIGHT - 1, 6);
        LoadAnimatedSprite(animations, constants::IDLE_SPRITE_ID, "./resources/Sprites/Mario/Idle.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 1); // TODO: last loaded sprite is visible upon spawn
        return animations;
    }

    static void AddPlayer(Scene &scene, double xPos, double yPos, double viewWidth, double viewHeight) {
        //Create Player for server
        GameObjectBuilder gameObjectBuilder{"speler"};
        Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), viewWidth, viewHeight};

        auto transform = Transform{Point{100, 175}, 0, 1.0};
        auto animations = LoadAnimations();
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::MarioBehaviour>()
        };
        GameObject &mario = GameObjectDirector::CreatePlayer(0, transform, DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT - 1, animations, behaviourScripts);

        std::map<std::string, int> const audioClips = {{"jump", 50}};
        mario.AddComponent<spic::AudioSource>(std::make_shared<AudioSource>(audioClips));

        scene.AddObject(mario);

        camera.SetTarget(mario);
        scene.AddCamera(camera);
    }

    static void AddFPSCounter(Scene &scene, double xPos, double yPos) {
        auto fpsCounter = platformer_engine::FPSCounter(
                Transform {Point{xPos, yPos}, 0, 1.0},
                DEFAULT_FONT_PATH,
                DEFAULT_FONT_SIZE,
                DEFAULT_FONT_COLOUR,
                DEFAULT_FONT_SIZE / 2, DEFAULT_FONT_SIZE / 2,
                KeyCode::F);
        scene.AddUIObject(fpsCounter.GetUIObject());
    }
};

#endif //PLATFORMER_GAME_LEVEL_HPP