#ifndef PLATFORMER_GAME_FPSCOUNTERBEHAVIOUR_HPP
#define PLATFORMER_GAME_FPSCOUNTERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Color.hpp"

namespace PlatformerGame {
    class FPSCounterBehaviour : public spic::BehaviourScript {
    public:
        FPSCounterBehaviour(std::string textId, std::string fontPath, int fontSize, spic::Color fontColor);

        void OnUpdate() override;

    private:
        int _lastFPS = 0;
        bool _active = true;

        const std::string _textId;
        const std::string _fontPath;
        const int _fontSize;
        const spic::Color _fontColor;
    };
} // namespace PlatformerGame

#endif //PLATFORMER_GAME_FPSCOUNTERBEHAVIOUR_HPP
