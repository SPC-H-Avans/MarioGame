#ifndef PLATFORMER_GAME_FPSCOUNTER_HPP
#define PLATFORMER_GAME_FPSCOUNTER_HPP

#include <memory>

#include "GameObject.hpp"

namespace PlatformerGame {
    class FPSCounter {
    public:
        /**
         * @brief Constructor
         */
        FPSCounter(spic::Transform transform, std::string fontPath, int fontSize,
                   spic::Color fontColor, int width, int height);

    private:
        std::shared_ptr<spic::GameObject> _obj;
    };
} // namespace PlatformerGame

#endif //PLATFORMER_GAME_FPSCOUNTER_HPP
