#include "Level1.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"

#include "Scripts/EnemyAttackBehaviour.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Physics/ForceDrivenEntity.hpp"

const int DEFAULT_GOOMBA_WIDTH = 16;
const int DEFAULT_GOOMBA_HEIGHT = 16;

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                         const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter,
                         const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter) {

    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    Scene scene = builder.GetScene();
    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(coinCounter));
    scene.AddUIObject(coinCounter->GetUIObject());
    scene.AddUIObject(fpsCounter->GetUIObject());
    scene.SetNextScene("level2");

    platformer_engine::AudioManager::GetInstance().SetVolume(50);

    platformer_engine::AudioManager::GetInstance().LoadMusic("overworld", "./resources/audio/music/smb_overworld_theme.mp3");
    platformer_engine::AudioManager::GetInstance().LoadSound("jump", "./resources/audio/sounds/smb_jump-small.wav");
    platformer_engine::AudioManager::GetInstance().PlayMusic("overworld", true);


    // Create goomba
    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_idle",
                                                                 "./resources/Sprites/Goomba/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_walk",
                                                                 "./resources/Sprites/Goomba/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_jump",
                                                                 "./resources/Sprites/Goomba/Jump.png");

    auto goombaIdleSprite = platformer_engine::AnimatedSprite("goomba_idle", DEFAULT_GOOMBA_WIDTH, DEFAULT_GOOMBA_HEIGHT, 1);
    auto goombaWalkSprite = platformer_engine::AnimatedSprite("goomba_walk", DEFAULT_GOOMBA_WIDTH, DEFAULT_GOOMBA_HEIGHT, 3);
    auto goombaJumpSprite = platformer_engine::AnimatedSprite("goomba_jump", DEFAULT_GOOMBA_WIDTH, DEFAULT_GOOMBA_HEIGHT, 1, 1, 1, 100,
                                                              platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip
    auto goombaAnimations = std::vector<platformer_engine::AnimatedSprite>{goombaIdleSprite, goombaWalkSprite, goombaJumpSprite};
    auto goombaBehaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<EnemyAttackBehaviour>(),
            std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(goombaIdleSprite, goombaWalkSprite, goombaJumpSprite)
    };

    auto goombaTransform = Transform { Point {20, 200}, 0, 1.0 };
    auto goomba = GameObjectFactory::CreateEnemy(goombaTransform, DEFAULT_GOOMBA_WIDTH, DEFAULT_GOOMBA_HEIGHT, goombaAnimations, goombaBehaviourScripts);
    auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(goomba.GetComponent<platformer_engine::ForceDrivenEntity>());

    auto mario = AddPlayer(scene, 100, 175, viewWidth, viewHeight);

    if(forceDrivenEntity != nullptr) {
        auto marioShared = GameObject::Find(mario.GetName());
        const double followRange = 100;
        forceDrivenEntity->SetFollowing(marioShared, followRange);
    }

    scene.AddObject(goomba);
    engine.AddScene(scene);
};