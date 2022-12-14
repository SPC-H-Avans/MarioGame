#include "TimerScript.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"
#include "future"

namespace PlatformerGame {

    TimerScript::TimerScript(int milliseconds, std::function<void()> action) : _sleepMilliSeconds(milliseconds), _action(action) {}

    void TimerScript::OnStart() {
        std::thread thread ([this]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(_sleepMilliSeconds));
            _action();

        });
        thread.detach();
    }

}