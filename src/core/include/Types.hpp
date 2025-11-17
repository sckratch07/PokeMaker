#ifndef _CORE_TYPES_HPP__
#define _CORE_TYPES_HPP__

#include <cstdint>
#include <string>
#include <vector>

namespace Core
{
    struct Vector2i
    {
        int x, y;
        Vector2i() : x(0), y(0) {}
        Vector2i(int _x, int _y) : x(_x), y(_y) {}
    };

    struct Vector2f
    {
      float x, y;
      Vector2f() : x(0.f), y(0.f) {}
      Vector2f(float _x, float _y) : x(_x), y(_y) {}
    };

    using IDType = uint64_t;
} // namespace Core

#endif
