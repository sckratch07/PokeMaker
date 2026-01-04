#ifndef _CORE_PROJECT_HPP__
#define _CORE_PROJECT_HPP__

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace Core
{
    class Project
    {
    public:
        Project() = default;
        Project(const std::string& name, const std::string& path) : m_name(name), m_path(path) {}

        bool isValid() const { return !(m_name.empty() && m_path.empty()); }

        bool create(const std::string& name, const std::string& path);
        bool load(const std::string& path);
        bool save() const;

        void setName(const std::string& name) { m_name = name; }
        void setPath(const std::string& path) { m_path = path; }

        const std::string& getName() const { return m_name; }
        const std::string& getPath() const { return m_path; }

    private:
        std::string m_name;
        std::string m_path;
    };
}

#endif