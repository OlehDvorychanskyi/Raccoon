#include <Raccoon/Renderer/IndexBuffer.h>
#include <Raccoon/Renderer/Renderer.h>

#include <Platforms/OpenGL/OpenGLIndexBuffer.h>

#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}