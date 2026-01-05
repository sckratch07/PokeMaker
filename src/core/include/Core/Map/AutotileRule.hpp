#ifndef _CORE_AUTOTILE_RULE_HPP__
#define _CORE_AUTOTILE_RULE_HPP__

#include <cstdint>

namespace Core
{
    enum Direction
    {
        UP = 1 << 0,
        DOWN = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3,
        UP_LEFT = 1 << 4,
        UP_RIGHT = 1 << 5,
        DOWN_LEFT = 1 << 6,
        DOWN_RIGHT = 1 << 7,
        MAX_DIR = 1 << 8
    };

    class AutotileRule
    {
    public:
        AutotileRule() = default;

        void setRule(Direction dir, uint8_t tileIndex)
        {
            m_rules[dir] = tileIndex;
        }

        uint8_t getPosibility(Direction dir) const
        {
            return m_rules[dir];
        }
        
    private:
        uint8_t m_rules[MAX_DIR] = {0};
    };
}

#endif