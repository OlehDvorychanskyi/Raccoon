#pragma once 
#include <Raccoon/Renderer/Shaders.h>

#include <string>
#include <memory>
#include <unordered_map>

namespace Raccoon
{
    class ShaderLibrary
    {
    public:
        void Load(const std::string &name, const std::string &vertexFilePath, const std::string &fragmentFilePath);
        void Add(const std::string &name, const std::shared_ptr<Shaders> &shaders);
        std::shared_ptr<Shaders> Get(const std::string &name) const; 
    private:
        bool Exist(const std::string &name);
    private:
        std::unordered_map<std::string, std::shared_ptr<Shaders>> m_Shaders;
    };
}