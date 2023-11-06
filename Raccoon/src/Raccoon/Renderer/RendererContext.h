#pragma once 
#include <memory>

namespace Raccoon
{
    class RendererContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffer() = 0;
        virtual ~RendererContext() = default;

        static std::unique_ptr<RendererContext> Create(void *window); 
    };
}