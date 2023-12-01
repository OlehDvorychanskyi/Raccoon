#include <Raccoon/Renderer/FrameBuffer.h>
#include <Platforms/OpenGL/OpenGLFrameBuffer.h>
#include <Raccoon/Renderer/Renderer.h>

namespace Raccoon
{
    std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification &specification)
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFrameBuffer>(specification);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}