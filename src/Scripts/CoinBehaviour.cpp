#include <iostream>
#include "CoinBehaviour.hpp"
#include "Engine/Engine.hpp"

void CoinBehaviour::OnTriggerEnter2D(Collision collision) {
    std::cout << "+Coin" << std::endl;
    // after being picked up, remove the coin from the scene and destroy it
    auto coinObj = GetGameObject().lock();
    platformer_engine::Engine::GetInstance().GetActiveScene().RemoveObject(coinObj->GetName());
    coinObj->Destroy(coinObj);
}
