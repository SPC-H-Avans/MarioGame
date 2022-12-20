
#include "Level1.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"
#include "AudioSource.hpp"
#include "Scripts/MarioBehaviour.hpp"
#include "constants/Sprites.hpp"

const int DEFAULT_LAYER = 1;
const int DEFAULT_SPEED = 100;
const int DEFAULT_ROW = 1;
const int DEFAULT_PLAYER_WIDTH = 15;
const int DEFAULT_PLAYER_HEIGHT = 17;

void LoadAnimatedSprite(std::vector<platformer_engine::AnimatedSprite> &spriteList, std::string spriteId,
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

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene scene = builder.GetScene();
    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(scene));

    //Create Player for server
    GameObjectBuilder gameObjectBuilder{"speler"};
    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};

    auto animations = std::vector<platformer_engine::AnimatedSprite>();
    LoadAnimatedSprite(animations, constants::WALK_SPRITE_ID, "./resources/Sprites/Mario/Walk.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 3);
    LoadAnimatedSprite(animations, constants::JUMP_SPRITE_ID, "./resources/Sprites/Mario/Jump.png", DEFAULT_PLAYER_WIDTH + 1, DEFAULT_PLAYER_HEIGHT - 1, 1);
    LoadAnimatedSprite(animations, constants::IDLE_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Idle.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 6);
    LoadAnimatedSprite(animations, constants::WALK_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Walk.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 6);
    LoadAnimatedSprite(animations, constants::JUMP_STAR_SPRITE_ID, "./resources/Sprites/Mario/Star/Jump.png", DEFAULT_PLAYER_WIDTH + 1, DEFAULT_PLAYER_HEIGHT - 1, 6);
    LoadAnimatedSprite(animations, constants::IDLE_SPRITE_ID, "./resources/Sprites/Mario/Idle.png", DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT, 1); // TODO: last loaded sprite is visible upon spawn

    auto transform = Transform{Point{100, 175}, 0, 1.0};
    auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<PlatformerGame::MarioBehaviour>()
    };
    GameObject &mario = GameObjectDirector::CreatePlayer(0, transform, DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT - 1, animations, behaviourScripts);

    std::map<std::string, int> const audioClips = {{"jump", 50}};
    mario.AddComponent<spic::AudioSource>(std::make_shared<AudioSource>(audioClips));

    platformer_engine::AudioManager::GetInstance().SetVolume(50);

    platformer_engine::AudioManager::GetInstance().LoadMusic("overworld", "./resources/audio/music/smb_overworld_theme.mp3");
    platformer_engine::AudioManager::GetInstance().LoadSound("jump", "./resources/audio/sounds/smb_jump-small.wav");
    platformer_engine::AudioManager::GetInstance().PlayMusic("overworld", true);
    scene.AddObject(mario);

    // test Button
    const auto textureName = "startButton";
    const auto spriteSize = 16;
    const auto spriteScale = 4;

    auto buttonSprite = spic::Sprite(textureName, spriteSize, spriteSize);
    buttonSprite.SetSpriteScale(spriteScale);
    auto button = GameObjectDirector::CreateButton(
            Transform{Point{20, 20}, 0, spriteScale},
            "button1",
            buttonSprite,
            "./resources/UI/start.png",
            spriteSize * spriteScale, spriteSize * spriteScale,
            []{ std::cout << "click" << std::endl; });

    scene.AddUIObject(std::make_shared<Button>(button));
    auto fpsCounter = platformer_engine::FPSCounter(
            Transform {Point{450, 0}, 0, 1.0},
            "./resources/fonts/DefaultFont.ttf",
            48,
            Color::Yellow(),
            24, 24,
            KeyCode::F);
    scene.AddUIObject(fpsCounter.GetUIObject());

    camera.SetTarget(mario);
    scene.AddCamera(camera);

    engine.AddScene(scene);
};