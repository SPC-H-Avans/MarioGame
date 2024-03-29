#ifndef PLATFORMER_GAME_COINBEHAVIOUR_HPP
#define PLATFORMER_GAME_COINBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "../UI/CoinCounter.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace PlatformerGame {
    class CoinBehaviour : public spic::BehaviourScript {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<BehaviourScript, CoinBehaviour>(*this);
            boost::serialization::void_cast_register<CoinBehaviour, BehaviourScript>();
            ar & _counter;
        }

        CoinBehaviour() = default;

        explicit CoinBehaviour(std::shared_ptr<CoinCounter> counter);

        void OnTriggerEnter2D(Collision collision) override;

    private:
        std::shared_ptr<CoinCounter> _counter;
    };
}

#endif //PLATFORMER_GAME_COINBEHAVIOUR_HPP
