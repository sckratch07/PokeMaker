#ifndef _CORE_TIMER_HPP__
#define _CORE_TIMER_HPP__

#include <chrono>

namespace Core
{
    class Timer
    {
    public:
        Timer() : m_lastTime(std::chrono::high_resolution_clock::now()) {}

        float Restart(); // retourne delta time en micro-secondes

    private:
        std::chrono::high_resolution_clock::time_point m_lastTime;
    };

} // namespace Core

#endif
