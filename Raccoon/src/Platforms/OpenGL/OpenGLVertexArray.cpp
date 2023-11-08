#include <Platforms/OpenGL/OpenGLVertexArray.h>

#include <glad/glad.h>

namespace Raccoon
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		RE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_Id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_Id);
    }

    void OpenGLVertexArray::Bind() const 
    {
        glBindVertexArray(m_Id);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const 
    {
        return m_IndexBuffer;
    } 

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const 
    {
        return m_VertexBuffers;
    }
    
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) 
    {
        glBindVertexArray(m_Id);
        IndexBuffer->Bind();

        m_IndexBuffer = IndexBuffer;
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer)
    {
        RE_CORE_ASSERT(VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

        glBindVertexArray(m_Id);
        VertexBuffer->Bind();

        const auto &layout = VertexBuffer->GetLayout();
        for (const auto &element : layout)
        {
            switch (element.Type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    glEnableVertexAttribArray(m_VertexArrayIndex);  
                    glVertexAttribPointer(m_VertexArrayIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
                    ++m_VertexArrayIndex;
                    break;
                }

                case ShaderDataType::Bool:
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                {
                    glEnableVertexAttribArray(m_VertexArrayIndex);  
                    glVertexAttribIPointer(m_VertexArrayIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), layout.GetStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
                    ++m_VertexArrayIndex;
                    break;
                }
                
                default:
					RE_CORE_ASSERT(false, "Unknown ShaderDataType");
            }
        }
        m_VertexBuffers.push_back(VertexBuffer);
    }
}