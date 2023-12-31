#include <Raccoon/Renderer/Shaders.h>
#include <Raccoon/Renderer/Renderer.h>

#include <Platforms/OpenGL/OpenGLShaders.h>

namespace Raccoon
{
    std::shared_ptr<Shaders> Shaders::Create(const FilePath &vertexFilePath, const FilePath &fragmentFilePath, bool fromFile)
    {
        switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShaders>(vertexFilePath, fragmentFilePath, fromFile);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
    }

	std::shared_ptr<Shaders> Shaders::Create(const std::string &vertexSource, const std::string &fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShaders>(vertexSource, fragmentSource);
		}

		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}