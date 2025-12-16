#ifndef _CORE_INPUTCOMPONENT_HPP__
#define _CORE_INPUTCOMPONENT_HPP__

#include <SFML/Graphics.hpp>

namespace Core
{
	enum KeyState { IDLE, PRESS, HOLD, RELEASE };

    struct InputComponent
    {
		InputComponent() { m_keys.resize(sf::Keyboard::ScancodeCount); }

		void updateKey()
		{
			for (int keyID = 0; keyID < sf::Keyboard::ScancodeCount; keyID++)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(keyID)))
					m_keys[keyID] = m_keys[keyID] == IDLE ? PRESS : HOLD;
				else if (m_keys[keyID] == HOLD || m_keys[keyID] == PRESS)
					m_keys[keyID] = RELEASE;
				else
					m_keys[keyID] = IDLE;
			}
		}

    	std::vector<KeyState> m_keys;
    };
}

#endif