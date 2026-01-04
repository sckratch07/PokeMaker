#ifndef _CORE_ANIMATE_SYSTEM_HPP__
#define _CORE_ANIMATE_SYSTEM_HPP__

#include <Core/ECS/System/System.hpp>

namespace Core
{
    class AnimateSystem : public System
    {
    public:
        void update(entt::registry& reg, float dt)
        {
            reg.view<ShapeComponent, AnimateComponent, TilesetComponent>().each([&](entt::entity, ShapeComponent& shape, AnimateComponent& animate, TilesetComponent& tileset)
            {
                if (animate.m_frames.empty()) return;

                animate.m_elapsedTime += dt;
                if (animate.m_elapsedTime >= animate.m_frames[animate.m_currentFrame].m_timer)
                {
                    if (animate.m_looping)
                        animate.m_currentFrame = (animate.m_currentFrame + 1) % static_cast<unsigned int>(animate.m_frames.size());
                    else
                        animate.m_currentFrame = std::min(static_cast<unsigned int>(animate.m_frames.size()) - 1, animate.m_currentFrame + 1);

                    Keyframe& frame = animate.m_frames[animate.m_currentFrame];
                    sf::IntRect texRect = tileset.m_tileset->tileById(frame.m_frame);
                    shape.m_shape.setTextureRect(texRect);
                    animate.m_elapsedTime = 0.f;

                }
            });
        }
    };
}

#endif