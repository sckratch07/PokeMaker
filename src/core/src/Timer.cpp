#include "Core/Timer.hpp"

namespace Core
{
    Timer::Timer()
    {
        reset();
    }

    void Timer::reset()
    {
        m_start = clock::now();
        m_last = m_start;
        m_deltaTime = 0.f;
    }

    void Timer::tick()
    {
        auto now = clock::now();
        m_deltaTime = std::chrono::duration<float>(now - m_last).count();
        m_last = now;
    }

    float Timer::deltaTime() const
    {
        return m_deltaTime;
    }

    float Timer::elapsedTime() const
    {
        return std::chrono::duration<float>(clock::now() - m_start).count();
    }
}