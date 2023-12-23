#include <Platforms/OpenGL/OpenGLShaders.h>
#include <Raccoon/Core/Assert.h>

#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace Raccoon
{
    OpenGLShaders::OpenGLShaders(const FilePath &vertexFilePath, const FilePath &fragmentFilePath)
    {
        uint32_t vertex = CompileShader(vertexFilePath, ShaderType::Vertex);
        uint32_t fragment = CompileShader(fragmentFilePath, ShaderType::Fragment);
        
        CreateShaderProgram(vertex, fragment);    
        
        ExtractUniforms(ShaderType::Vertex);
        ExtractUniforms(ShaderType::Fragment);
    }

    uint32_t OpenGLShaders::CompileShader(const FilePath &filePath, ShaderType shaderType)
    {
        std::ifstream file(filePath.GetGlobalPath());
        if (!file.is_open())
        {
            RE_CORE_ERROR("Fail to open file {0}", filePath.GetGlobalPath());
        }
        m_FilePath[shaderType] = filePath;

        std::string sourceCode;
        std::string line;
        while (std::getline(file, line)) sourceCode += line + "\n";
        m_SourceCode[shaderType] = sourceCode;

        uint32_t shaderID = glCreateShader((shaderType == ShaderType::Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

        const char* source = sourceCode.c_str();

        glShaderSource(shaderID, 1, &source, NULL);
        glCompileShader(shaderID);

        CheckCompileErrors(shaderID, filePath);

        return shaderID;
    }

    void OpenGLShaders::CreateShaderProgram(uint32_t vertex, uint32_t fragment)
    {
        m_Id = glCreateProgram();  

        glAttachShader(m_Id, vertex);
        glAttachShader(m_Id, fragment);
        glLinkProgram(m_Id);

        CheckLinkErrors();

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void OpenGLShaders::CheckCompileErrors(uint32_t shader, const FilePath &filePath)
    {
        int32_t isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            int32_t maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            RE_CORE_ERROR("Fail to compile shader ({0}):\n{1}", filePath.GetGlobalPath(), errorLog.data());
            return;
        }
    }

    void OpenGLShaders::CheckLinkErrors()
    {
        int32_t isLinked;
        glGetProgramiv(m_Id, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int32_t maxLength = 0;
            glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(m_Id, maxLength, &maxLength, errorLog.data());
            RE_CORE_ERROR("Fail to link shaders: \n{0}", errorLog.data());
        }
    }

    void OpenGLShaders::ExtractUniforms(ShaderType type)
    {
        std::istringstream sourceStream(m_SourceCode[type]);
        std::string line;
        while (std::getline(sourceStream, line)) 
        {
            std::size_t temp = line.find("uniform");
            if (temp != std::string::npos)
            {
                std::istringstream lineStream(line.substr(temp, line.size()));
                std::string qualifier, type, name;
                lineStream >> qualifier >> type >> name;

                name.erase(std::remove(name.begin(), name.end(), ';'), name.end());
                size_t pos = name.find('[');
                if (pos != std::string::npos) 
                {
                    name = name.substr(0, pos);
                }

                uint32_t location = glGetUniformLocation(m_Id, name.c_str());
                RE_CORE_ASSERT(location != -1, "Couldn't get uniform location for uniform");
                m_Uniforms[name] = location;
            }
        }
    }

    void OpenGLShaders::Bind() const 
    { 
        glUseProgram(m_Id);
    }
    
    void OpenGLShaders::Unbind() const  
    { 
        glUseProgram(0);
    }

    void OpenGLShaders::SetBool(const std::string &name, bool value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform1i(element->second, (int)value);
    }
    
    void OpenGLShaders::SetInt(const std::string &name, int value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform1i(element->second, value);
    }

    void OpenGLShaders::SetInt2(const std::string &name, const glm::ivec2 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform2i(element->second, value.x, value.y);
    }

    void OpenGLShaders::SetInt3(const std::string &name, const glm::ivec3 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform3i(element->second, value.x, value.y, value.z);
    }

    void OpenGLShaders::SetInt4(const std::string &name, const glm::ivec4 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform4f(element->second, value.x, value.y, value.z, value.w);
    }

    void OpenGLShaders::SetArrayInt(const std::string &name, int* data, int count) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform1iv(element->second, count, data);
    }

    void OpenGLShaders::SetFloat(const std::string &name, float value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform1f(element->second, value);
    }

    void OpenGLShaders::SetFloat2(const std::string &name, const glm::vec2 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform2f(element->second, value.x, value.y);
    }

    void OpenGLShaders::SetFloat3(const std::string &name, const glm::vec3 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform3f(element->second, value.x, value.y, value.z);
    }

    void OpenGLShaders::SetFloat4(const std::string &name, const glm::vec4 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniform4f(element->second, value.x, value.y, value.z, value.w);
    }

    void OpenGLShaders::SetMat3(const std::string &name, const glm::mat3 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniformMatrix3fv(element->second, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShaders::SetMat4(const std::string &name, const glm::mat4 &value) 
    {
        auto element = m_Uniforms.find(name);
        RE_CORE_ASSERT(element != m_Uniforms.end(), "Couldn't find uniform");
        glUniformMatrix4fv(element->second, 1, GL_FALSE, glm::value_ptr(value));
    }
}