#include <Raccoon/Renderer/ShaderLibrary.h>
#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shaders> &shaders)
    {
        RE_CORE_ASSERT(Exist(name), "Shader with this name already exists");
        m_Shaders[name] = shaders;
    }

    void ShaderLibrary::Load(const std::string &name, const std::string &vertexFilePath, const std::string &fragmentFilePath)
    {
        RE_CORE_ASSERT(Exist(name), "Shader with this name already exists");
        std::shared_ptr<Shaders> shaders = Shaders::Create(vertexFilePath, fragmentFilePath);
        m_Shaders[name] = shaders;
    }
    
    std::shared_ptr<Shaders> ShaderLibrary::Get(const std::string &name) const
    {
        auto it = m_Shaders.find(name);
        RE_CORE_ASSERT(it != m_Shaders.end(), "Shader with this name doesn't exist");
        return it->second;
    }    

    bool ShaderLibrary::Exist(const std::string &name)
    {
        return (m_Shaders.find(name) != m_Shaders.end()) ? true : false;
    }
}