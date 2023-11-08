#include <Raccoon/Renderer/VertexBuffer.h>
#include <Raccoon/Renderer/Renderer.h>

#include <Platforms/OpenGL/OpenGLVertexBuffer.h>

#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}