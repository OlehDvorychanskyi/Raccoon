#include <Platforms/OpenGL/OpenGLShaders.h>
#include <Raccoon/Core/Assert.h>

#include <glad/glad.h>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Raccoon
{
    OpenGLShaders::OpenGLShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath)
    {
        uint32_t vertex = CompileShader(vertexFilePath, ShaderType::Vertex);
        uint32_t fragment = CompileShader(fragmentFilePath, ShaderType::Fragment);
        CreateShaderProgram(vertex, fragment);        
    }

    uint32_t OpenGLShaders::CompileShader(const std::string &filePath, ShaderType shaderType)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            RE_CORE_ERROR("Fail to open file {0}", filePath);
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

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void OpenGLShaders::CheckCompileErrors(uint32_t shader, const std::string &filePath)
    {
        int32_t isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            int32_t maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            RE_CORE_ERROR("Fail to compile shader ({0}):\n{1}", filePath, errorLog.data());
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
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value);
    }
    
    void OpenGLShaders::SetInt(const std::string &name, int value) 
    {
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
    }

    void OpenGLShaders::SetInt2(const std::string &name, const glm::ivec2 &value) 
    {
        glUniform2i(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y);
    }

    void OpenGLShaders::SetInt3(const std::string &name, const glm::ivec3 &value) 
    {
        glUniform3i(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y, value.z);
    }

    void OpenGLShaders::SetInt4(const std::string &name, const glm::ivec4 &value) 
    {
        glUniform4f(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void OpenGLShaders::SetArrayInt(const std::string &name, int* data, int count) 
    {
        glUniform1iv(glGetUniformLocation(m_Id, name.c_str()), count, data);
    }

    void OpenGLShaders::SetFloat(const std::string &name, float value) 
    {
        glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
    }

    void OpenGLShaders::SetFloat2(const std::string &name, const glm::vec2 &value) 
    {
        glUniform2f(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y);
    }

    void OpenGLShaders::SetFloat3(const std::string &name, const glm::vec3 &value) 
    {
        glUniform3f(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y, value.z);
    }

    void OpenGLShaders::SetFloat4(const std::string &name, const glm::vec4 &value) 
    {
        glUniform4f(glGetUniformLocation(m_Id, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void OpenGLShaders::SetMat3(const std::string &name, const glm::mat3 &value) 
    {
        glUniformMatrix3fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShaders::SetMat4(const std::string &name, const glm::mat4 &value) 
    {
        glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
}