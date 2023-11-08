#include <Raccoon/Renderer/VertexArray.h>
#include <Raccoon/Renderer/Renderer.h>

#include <Platforms/OpenGL/OpenGLVertexArray.h>

namespace Raccoon
{
    std::shared_ptr<VertexArray> VertexArray::Create()   
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLVertexArray>();
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}