#include <Raccoon/Renderer/Texture2D.h>
#include <Raccoon/Renderer/Renderer.h>

#include <Platforms/OpenGL/OpenGLTexture2D.h>

namespace Raccoon
{
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string &filepath)
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(filepath);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, TextureFormat internalFormat)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height, internalFormat);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}