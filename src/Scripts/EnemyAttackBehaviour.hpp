#ifndef PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_HPP
#define PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_HPP


#include "BehaviourScript.hpp"

class EnemyAttackBehaviour : public spic::BehaviourScript {
public:
    template<typename archive>
    void serialize(archive &ar, const unsigned /*version*/) {
        ar & boost::serialization::base_object<Component, EnemyAttackBehaviour>(*this);
        boost::serialization::void_cast_register<EnemyAttackBehaviour, Component>();
    }

    void OnUpdate() override;
};


#endif //PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_HPP
