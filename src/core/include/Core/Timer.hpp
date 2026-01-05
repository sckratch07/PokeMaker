#ifndef _CORE_TIMER_HPP__
#define _CORE_TIMER_HPP__

#include <chrono>

namespace Core
{
    class Timer
    {
    public:
        Timer() { reset(); }
        
        void tick()
        {
            auto now = clock::now();
            m_deltaTime = std::chrono::duration<float>(now - m_last).count();
            m_last = now;
        }
        
        float deltaTime() const { return m_deltaTime; }
        
        float elapsedTime() const { return std::chrono::duration<float>(clock::now() - m_start).count(); }
        
        void reset()
        {
            m_start = clock::now();
            m_last = m_start;
            m_deltaTime = 0.f;
        }

    private:
        using clock = std::chrono::high_resolution_clock;

        clock::time_point m_start;
        clock::time_point m_last;
        float m_deltaTime = 0.f;
    };
}

#endif