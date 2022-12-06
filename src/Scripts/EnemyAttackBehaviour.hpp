#ifndef PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_H
#define PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_H


#include "BehaviourScript.hpp"

namespace PlatformerGame {

    class EnemyAttackBehaviour : public spic::BehaviourScript {
    public:
        void OnUpdate() override;
    private:
    };

}  // namespace PlatformerGame


#endif //PLATFORMER_GAME_ENEMYATTACKBEHAVIOUR_H
