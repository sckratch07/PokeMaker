#include "Core/State.hpp"
#include "Core/Core.hpp"

namespace Core
{
    State::State(CoreEngine& core)
    : m_core(core)
    {
    }

    void State::onEnter()
    {
    }

    void State::onExit()
    {
    }
}