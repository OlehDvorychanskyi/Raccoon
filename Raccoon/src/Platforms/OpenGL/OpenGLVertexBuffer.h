#pragma once 
#include <Raccoon/Renderer/VertexBuffer.h>

namespace Raccoon
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(BufferLayout layout) override { m_Layout = layout; }

        virtual void SetData(void *data, uint32_t size) override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        uint32_t m_Id;
        BufferLayout m_Layout;
    };
}