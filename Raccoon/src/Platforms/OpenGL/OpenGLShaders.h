#pragma once 
#include <Raccoon/Renderer/Shaders.h>
#include <string>
#include <unordered_map>
#include <cstdint>

namespace Raccoon
{
    class OpenGLShaders : public Shaders
    {
    public:
        enum class ShaderType
        {
            Vertex,
            Fragment
        };
    public:
        OpenGLShaders(const FilePath &vertexFilePath, const FilePath &fragmentFilePath, bool fromFile);
        OpenGLShaders(const std::string &vertexSource, const std::string &fragmentSource);

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetBool(const std::string &name, bool value) override;
        
        virtual void SetInt(const std::string &name, int value) override;
        virtual void SetInt2(const std::string &name, const glm::ivec2 &value) override;
        virtual void SetInt3(const std::string &name, const glm::ivec3 &value) override;
        virtual void SetInt4(const std::string &name, const glm::ivec4 &value) override;

        virtual void SetArrayInt(const std::string &name, int* data, int count) override;

        virtual void SetFloat(const std::string &name, float value) override;
        virtual void SetFloat2(const std::string &name, const glm::vec2 &value) override;
        virtual void SetFloat3(const std::string &name, const glm::vec3 &value) override;
        virtual void SetFloat4(const std::string &name, const glm::vec4 &value) override;

        virtual void SetMat3(const std::string &name, const glm::mat3 &value) override;
        virtual void SetMat4(const std::string &name, const glm::mat4 &value) override;
    private:
        std::string GetSourceCode(const FilePath &path);
        uint32_t CompileShader(const std::string &filePath, ShaderType shaderType);
        void CheckCompileErrors(uint32_t shader);
        void CheckLinkErrors();
        void CreateShaderProgram(uint32_t vertex, uint32_t fragment);
        void ExtractUniforms(ShaderType type);
    private:
        uint32_t m_Id;
        std::unordered_map<ShaderType, FilePath> m_FilePath;
        std::unordered_map<ShaderType, std::string> m_SourceCode;
        std::unordered_map<std::string, uint32_t> m_Uniforms;
    };
}