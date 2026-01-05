#ifndef _CORE_ANIMATE_COMPONENT_HPP__
#define _CORE_ANIMATE_COMPONENT_HPP__

#include <vector>
#include <cstdint>

namespace Core
{
    struct Keyframe
    {
		uint32_t m_frame = 0;
        float m_timer = 0.f;
    };
    
    struct AnimateComponent
    {
		std::vector<Keyframe> m_frames;
        unsigned int m_currentFrame;
        float m_elapsedTime = 0.f;
        bool m_looping = true;
    };
}

#endif