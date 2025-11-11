#pragma once

namespace Core {
    class Timer {
    private:
        float _lastFrameTime;
    public:
        Timer();

        float Tick();
    };
}