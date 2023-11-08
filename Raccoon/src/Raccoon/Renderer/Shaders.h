#pragma once 
#include <Raccoon/Renderer/BufferLayout.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace Raccoon
{
    class Shaders
    {
    public:
        virtual ~Shaders() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        // virtual void SetLayout(const BufferLayout &layout);

        virtual void SetBool(const std::string &name, bool value) = 0;
        
        virtual void SetInt(const std::string &name, int value) = 0;
        virtual void SetInt2(const std::string &name, const glm::ivec2 &value) = 0;
        virtual void SetInt3(const std::string &name, const glm::ivec3 &value) = 0;
        virtual void SetInt4(const std::string &name, const glm::ivec4 &value) = 0;

        virtual void SetArrayInt(const std::string &name, int* data, int count) = 0;

        virtual void SetFloat(const std::string &name, float value) = 0;
        virtual void SetFloat2(const std::string &name, const glm::vec2 &value) = 0;
        virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;
        virtual void SetFloat4(const std::string &name, const glm::vec4 &value) = 0;

        virtual void SetMat3(const std::string &name, const glm::mat3 &value) = 0;
        virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;

        static std::shared_ptr<Shaders> Create(const std::string &vertexFilePath, const std::string &fragmentFilePath);
    };
}