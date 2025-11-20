#include "Core/InputManager.hpp"

namespace Core
{

void InputManager::setKeyState(int code, bool down)
{
    std::lock_guard lock(m_mutex);
    m_keyStates[code] = down;
}

bool InputManager::isKeyDown(int code) const
{
    std::lock_guard lock(m_mutex);
    auto it = m_keyStates.find(code);
    if (it == m_keyStates.end()) return false;
    return it->second;
}

void InputManager::clear()
{
    std::lock_guard lock(m_mutex);
    m_keyStates.clear();
}

} // namespace Core
 