
#include "Level1.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"
#include "AudioSource.hpp"
#include "Scripts/MarioBehaviour.hpp"
#include "Scripts/EnemyAttackBehaviour.hpp"
#include "Physics/ForceDrivenEntity.hpp"

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene scene = builder.GetScene();
    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(scene));

    //Create Player for server
    GameObjectBuilder gameObjectBuilder{"speler"};
    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};
    const int marioWidth = 15;
    const int marioHeight = 17;


    const int goombaWidth = 24;
    const int goombaHeight = 24;

    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle",
                                                                 "./resources/Sprites/Mario/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk",
                                                                 "./resources/Sprites/Mario/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump",
                                                                 "./resources/Sprites/Mario/Jump.png");
    auto idleSprite = platformer_engine::AnimatedSprite("mario_idle", marioWidth, marioHeight, 1);
    auto walkSprite = platformer_engine::AnimatedSprite("mario_walk", marioWidth, marioHeight, 3);
    auto jumpSprite = platformer_engine::AnimatedSprite("mario_jump", marioWidth + 1, marioHeight - 1, 1, 1, 1, 100,
                                                        platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_idle",
                                                                 "./resources/Sprites/Goomba/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_walk",
                                                                 "./resources/Sprites/Goomba/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_jump",
                                                                 "./resources/Sprites/Goomba/Jump.png");

    auto goombaIdleSprite = platformer_engine::AnimatedSprite("goomba_idle", goombaWidth, goombaHeight, 1);
    auto goombaWalkSprite = platformer_engine::AnimatedSprite("goomba_walk", goombaWidth, goombaHeight, 3);
    auto goombaJumpSprite = platformer_engine::AnimatedSprite("goomba_jump", goombaWidth + 1, goombaHeight - 1, 1, 1, 1, 100,
                                                              platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip
    auto transform = Transform{Point{100, 250}, 0, 1.0};
    auto marioAnimations = std::vector<platformer_engine::AnimatedSprite>{idleSprite, walkSprite, jumpSprite};
    auto goombaAnimations = std::vector<platformer_engine::AnimatedSprite>{goombaIdleSprite, goombaWalkSprite, goombaJumpSprite};
    auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<PlatformerGame::PlayerInputBehaviour>(),
            std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(idleSprite, walkSprite, jumpSprite),
            std::make_shared<PlatformerGame::MarioBehaviour>()
    };
    GameObject &mario = GameObjectDirector::CreatePlayer(0, transform, marioWidth, marioHeight - 1, marioAnimations, behaviourScripts);

    std::map<std::string, int> const audioClips = {{"jump", 50}};
    mario.AddComponent<spic::AudioSource>(std::make_shared<AudioSource>(audioClips));

    auto goombaBehaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<EnemyAttackBehaviour>(),
            std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(goombaIdleSprite, goombaWalkSprite, goombaJumpSprite)
    };

    auto goombaTransform = Transform { Point {20, 200}, 0, 1.0 };
    auto goomba = GameObjectDirector::CreateEnemy(goombaTransform, goombaWidth, goombaHeight - 1, goombaAnimations, goombaBehaviourScripts);
    auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(goomba.GetComponent<platformer_engine::ForceDrivenEntity>());

    if(forceDrivenEntity != nullptr) {
        auto marioShared = GameObject::Find(mario.GetName());
        const double followRange = 100;
        forceDrivenEntity->SetFollowing(marioShared, followRange);
    }


    platformer_engine::AudioManager::GetInstance().SetVolume(50);

    platformer_engine::AudioManager::GetInstance().LoadMusic("overworld", "./resources/audio/music/smb_overworld_theme.mp3");
    platformer_engine::AudioManager::GetInstance().LoadSound("jump", "./resources/audio/sounds/smb_jump-small.wav");
    platformer_engine::AudioManager::GetInstance().PlayMusic("overworld", true);
    scene.AddObject(mario);

    // test Text
    auto textId = "coins";
    auto text = "text test";
    auto fontPath = "./resources/fonts/DefaultFont.ttf";
    auto fontSize = 40;
    auto color = Color::Yellow();
    auto uiText = GameObjectDirector::CreateText(
            Transform{Point{150, 0}, 0, 1.0},
            textId,
            text,
            fontPath,
            100, 50,
            fontSize, color);
    // test update text
    text = "TEST TEXT";
    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(textId, fontPath, text, fontSize, color);

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
    scene.AddUIObject(std::make_shared<Text>(uiText));
    auto fpsCounter = platformer_engine::FPSCounter(
            Transform {Point{460, 0}, 0, 1.0},
            "./resources/UI/DefaultFont.ttf",
            48,
            Color::Yellow(),
            16, 16,
            KeyCode::F);
    scene.AddUIObject(fpsCounter.GetUIObject());

    camera.SetTarget(mario);
    scene.AddCamera(camera);

    engine.AddScene(scene);
};