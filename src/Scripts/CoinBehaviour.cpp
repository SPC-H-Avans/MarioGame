#include <iostream>
#include <utility>
#include "CoinBehaviour.hpp"
#include "Engine/Engine.hpp"

PlatformerGame::CoinBehaviour::CoinBehaviour(std::shared_ptr<PlatformerGame::CoinCounter> counter)
    : _counter(std::move(counter)) {}

void PlatformerGame::CoinBehaviour::OnTriggerEnter2D(Collision collision) {
    std::cout << "+Coin" << std::endl;
    _counter->AddCoin();

    // after being picked up, remove the coin from the scene and destroy it
    auto coinObj = GetGameObject().lock();
    platformer_engine::Engine::GetInstance().GetActiveScene().RemoveObject(coinObj->GetName());
    coinObj->Destroy(coinObj);
}
BOOST_CLASS_EXPORT(PlatformerGame::CoinBehaviour);