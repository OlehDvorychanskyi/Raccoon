#pragma once 
#include <memory>
#include <cstdint>

#include <Raccoon/Renderer/BufferLayout.h>

namespace Raccoon
{
    class VertexBuffer
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(BufferLayout layout) = 0;

        virtual void SetData(void *data, uint32_t size) = 0;

        static std::shared_ptr<VertexBuffer> Create(float *vertices, uint32_t size);
        static std::shared_ptr<VertexBuffer> Create(uint32_t size);
        virtual ~VertexBuffer() = default;
    };
}