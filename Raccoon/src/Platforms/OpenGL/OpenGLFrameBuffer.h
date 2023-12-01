#pragma once 
#include <Raccoon/Renderer/FrameBuffer.h>
#include <cstdint>

namespace Raccoon
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification &specification);
        virtual ~OpenGLFrameBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetColorAttachment() const override { return m_ColorAttachment; }
        virtual FrameBufferSpecification GetSpecification() const override { return m_Specification; }
    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FrameBufferSpecification m_Specification;
    };
}