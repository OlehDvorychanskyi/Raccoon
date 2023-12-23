#include <Raccoon/FileSystem/FileSystem.h>
#include <string>
#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    std::filesystem::path FileSystem::m_BasePath = std::filesystem::current_path();

    std::filesystem::path FileSystem::GetBaseDirectory()
    {
        return m_BasePath;
    }
}