#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "../TileConfig.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "../Scripts/PlayerInputBehaviour.hpp"
#include "../Scripts/DynamicAnimationBehaviour.hpp"
#include "RigidBody.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"


const bool FULLSCREEN = false;

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan(), FULLSCREEN);

        Camera camera = Camera{"camera1", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                               static_cast<double>(viewHeight)};


        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
        engine.AddScene(builder.GetScene());
        engine.SetActiveScene("level1");
        Scene &scene = engine.GetActiveScene();

//        Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Map1());
//        Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::Map1());
        Scene::ImportLevel("map1", "./resources/levels/mario/", "w1-1.tmx", TileConfig::World1());

        GameObjectBuilder gameObjectBuilder{"speler"};
        const int marioWidth = 15;
        const int marioHeight = 17;

        const int goombaWidth = 24;
        const int goombaHeight = 24;

        // Load sprites
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle",
                                                                     "./resources/Sprites/Mario/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk",
                                                                     "./resources/Sprites/Mario/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump",
                                                                     "./resources/Sprites/Mario/Jump.png");


        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_idle",
                                                                     "./resources/Sprites/Goomba/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_walk",
                                                                     "./resources/Sprites/Goomba/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba_jump",
                                                                     "./resources/Sprites/Goomba/Jump.png");

        auto marioIdleSprite = platformer_engine::AnimatedSprite("mario_idle", marioWidth, marioHeight, 1);
        auto marioWalkSprite = platformer_engine::AnimatedSprite("mario_walk", marioWidth, marioHeight, 3);
        auto marioJumpSprite = platformer_engine::AnimatedSprite("mario_jump", marioWidth + 1, marioHeight - 1, 1, 1, 1, 100,
                                                            platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

        auto goombaIdleSprite = platformer_engine::AnimatedSprite("goomba_idle", goombaWidth, goombaHeight, 1);
        auto goombaWalkSprite = platformer_engine::AnimatedSprite("goomba_walk", goombaWidth, goombaHeight, 3);
        auto goombaJumpSprite = platformer_engine::AnimatedSprite("goomba_jump", goombaWidth + 1, goombaHeight - 1, 1, 1, 1, 100,
                                                            platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

        auto transform = Transform{Point{260, 130}, 0, 1.0};
        auto marioAnimations = std::vector<platformer_engine::AnimatedSprite>{marioIdleSprite, marioWalkSprite, marioJumpSprite};
        auto goombaAnimations = std::vector<platformer_engine::AnimatedSprite>{goombaIdleSprite, goombaWalkSprite, goombaJumpSprite};
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::PlayerInputBehaviour>(),
                std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(marioIdleSprite, marioWalkSprite, marioJumpSprite)
        };

        auto enemyBehaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(goombaIdleSprite, goombaWalkSprite, goombaJumpSprite)
        };

        auto mario = GameObjectDirector::CreatePlayer(transform, marioWidth, marioHeight - 1, marioAnimations, behaviourScripts);

        camera.SetTarget(mario);

        scene.AddCamera(camera);

        auto enemyTransform = Transform { Point {20, 200}, 0, 1.0 };
        auto enemy = GameObjectDirector::CreateEnemy(enemyTransform, goombaWidth, goombaHeight - 1, goombaAnimations, enemyBehaviourScripts);
        auto enemyBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(enemy.GetComponent<RigidBody>());

        if(enemyBody != nullptr) {
            auto marioShared = GameObject::Find(mario.GetName());
            const double followRange = 100;
            enemyBody->SetFollowing(marioShared, followRange);
        }

        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame