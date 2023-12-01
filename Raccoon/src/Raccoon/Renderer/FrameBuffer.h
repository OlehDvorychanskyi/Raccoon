#pragma once 
#include <memory>

namespace Raccoon
{
    struct FrameBufferSpecification
    {
        uint32_t Width, Height;
    };

    class FrameBuffer
    {
    public:
        virtual ~FrameBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachment() const = 0;
        virtual FrameBufferSpecification GetSpecification() const = 0;
    
        static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification &specification);
    };
}