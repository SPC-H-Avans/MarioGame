
#include "Level1.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"
#include "AudioSource.hpp"
#include "Scripts/MarioBehaviour.hpp"

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene scene = builder.GetScene();
    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(scene));

    //Create Player for server
    GameObjectBuilder gameObjectBuilder{"speler"};
    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};
    int w = 15;
    int h = 17;

    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle",
                                                                 "./resources/Sprites/Mario/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk",
                                                                 "./resources/Sprites/Mario/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump",
                                                                 "./resources/Sprites/Mario/Jump.png");
    auto idleSprite = platformer_engine::AnimatedSprite("mario_idle", w, h, 1);
    auto walkSprite = platformer_engine::AnimatedSprite("mario_walk", w, h, 3);
    auto jumpSprite = platformer_engine::AnimatedSprite("mario_jump", w + 1, h - 1, 1, 1, 1, 100,
                                                        platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle_star",
                                                                 "./resources/Sprites/Mario/Star/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk_star",
                                                                 "./resources/Sprites/Mario/Star/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump_star",
                                                                 "./resources/Sprites/Mario/Star/Jump.png");
    auto idleStarSprite = platformer_engine::AnimatedSprite("mario_idle_star", w, h, 6);
    auto walkStarSprite = platformer_engine::AnimatedSprite("mario_walk_star", w, h, 6);
    auto jumpStarSprite = platformer_engine::AnimatedSprite("mario_jump_star", w + 1, h - 1, 6);

    auto transform = Transform{Point{100, 175}, 0, 1.0};
    auto animations = std::vector<platformer_engine::AnimatedSprite>{walkSprite, jumpSprite, idleStarSprite, walkStarSprite, jumpStarSprite, idleSprite}; // TODO: last loaded sprite is visible upon spawn
    auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<PlatformerGame::MarioBehaviour>()
    };
    GameObject &mario = GameObjectDirector::CreatePlayer(0, transform, w, h - 1, animations, behaviourScripts);

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