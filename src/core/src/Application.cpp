#include "Core/Application.hpp"

namespace Core
{
void Application::setUpdateCallback(std::function<void(double)> cb)
{
    m_updateCallback = std::move(cb);
}

void Application::setRenderCallback(std::function<void(double)> cb)
{
    m_renderCallback = std::move(cb);
}

void Application::run()
{
    m_running = true;

    Clock::time_point previous = Clock::now();
    double accumulator = 0.0;

    while (m_running) {
        Clock::time_point now = Clock::now();
        Duration frameTime = now - previous;
        previous = now;

        double dt = frameTime.count();

        if (m_fixedTimestep > 0.0) {
            accumulator += dt;
            while (accumulator >= m_fixedTimestep) {
                if (m_updateCallback) m_updateCallback(m_fixedTimestep);
                accumulator -= m_fixedTimestep;
            }
            // On peut fournir un interpolation delta au rendu (ici on passe m_fixedTimestep)
            if (m_renderCallback) m_renderCallback(m_fixedTimestep);
        } else {
            if (m_updateCallback) m_updateCallback(dt);
            if (m_renderCallback) m_renderCallback(dt);
        }
    }
}

void Application::stop()
{
    m_running = false;
}

void Application::setFixedTimestep(double timestep)
{
    m_fixedTimestep = timestep;
}

bool Application::isRunning() const noexcept
{
    return m_running;
}

} // namespace Core
