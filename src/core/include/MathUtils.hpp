#ifndef _CORE_MATH_UTILS_HPP__
#define _CORE_MATH_UTILS_HPP__

#include <algorithm>

namespace Core
{
    inline float clamp(float value, float minVal, float maxVal)
    {
        return std::max(minVal, std::min(value, maxVal));
    }

    inline float lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

} // namespace Core

#endif
