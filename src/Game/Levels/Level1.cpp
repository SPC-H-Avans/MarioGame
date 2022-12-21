#include "Level1.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"

#include "Scripts/EnemyAttackBehaviour.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Physics/ForceDrivenEntity.hpp"

const auto ENEMY_RANGE = 100;

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                         const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter,
                         const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter) {

    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    Scene scene = builder.GetScene();

    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(coinCounter));

    auto player = AddPlayer(scene, 100, 175, viewWidth, viewHeight);

    for (auto &enemy : scene.GetObjectsByTag("enemy")) {
        auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(enemy->GetComponent<platformer_engine::ForceDrivenEntity>());

        if(forceDrivenEntity != nullptr) {
            auto marioShared = GameObject::Find(player.GetName());
            const double followRange = ENEMY_RANGE;
            forceDrivenEntity->SetFollowing(marioShared, followRange);
        }
    }

    scene.AddUIObject(coinCounter->GetUIObject());
    scene.AddUIObject(fpsCounter->GetUIObject());
    scene.SetNextScene("level2");

    platformer_engine::AudioManager::GetInstance().SetVolume(50);

    platformer_engine::AudioManager::GetInstance().LoadMusic("overworld", "./resources/audio/music/smb_overworld_theme.mp3");
    platformer_engine::AudioManager::GetInstance().LoadSound("jump", "./resources/audio/sounds/smb_jump-small.wav");
    platformer_engine::AudioManager::GetInstance().PlayMusic("overworld", true);

    engine.AddScene(scene);
};