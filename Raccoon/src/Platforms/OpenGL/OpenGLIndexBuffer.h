#pragma once 
#include <Raccoon/Renderer/IndexBuffer.h>

namespace Raccoon
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const { return m_Count; } 
    private:
        uint32_t m_Id;
        uint32_t m_Count;
    };
}