#pragma once 
#include <Raccoon/Renderer/VertexArray.h>
#include <vector>
#include <cstdint>

namespace Raccoon
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override; 
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;

        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) override;
    private:
        uint32_t m_Id;
        uint32_t m_VertexArrayIndex = 0U;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}