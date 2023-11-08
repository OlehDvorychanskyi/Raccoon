#include <Raccoon/Renderer/RendererAPI.h>

#include <Platforms/OpenGL/OpenGLRendererAPI.h>

namespace Raccoon
{
    // Detect API here 
    RendererAPI::API RendererAPI::m_RendererAPI = RendererAPI::API::OpenGL;

    std::shared_ptr<RendererAPI> RendererAPI::Create()
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLRendererAPI>();
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }
}