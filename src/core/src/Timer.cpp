#include "Timer.hpp"

namespace Core
{
    float Timer::Restart()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = now - m_lastTime;
        m_lastTime = now;
        return delta.count();
    }
} // namespace Core
