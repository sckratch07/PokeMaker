#ifndef _APPLICATION_HPP__
#define _APPLICATION_HPP__

#include <string>

namespace Engine
{
    class Application
    {
    public:
        Application(const char* name = "PokeMaker", unsigned int width = 1600, unsigned int height = 1200) :
            m_name(name), m_width(width), m_height(height) {}
        virtual ~Application() = default;

        virtual void run() = 0;
        virtual void shutdown() = 0;

    private:
        std::string m_name;
        unsigned int m_width = 1600;
        unsigned int m_height = 1200;
    };
}

#endif