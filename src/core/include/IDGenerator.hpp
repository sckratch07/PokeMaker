#ifndef _CORE_ID_GENERATOR_HPP__
#define _CORE_ID_GENERATOR_HPP__

#include "Types.hpp"

namespace Core
{
    class IDGenerator
    {
    public:
        static IDType Next()
        {
            static IDType current = 0;
            return ++current;
        }
    };
} // namespace Core

#endif
