#include <Raccoon/FileSystem/FilePath.h>

namespace Raccoon
{
    FilePath::FilePath(const std::string &relativePath)
    {
        m_Path = relativePath;
    }

    FilePath::FilePath(const char *relativePath)
    {
        m_Path = relativePath;
    }

    std::string FilePath::GetGlobalPath() const 
    { 
        std::filesystem::path basePath = FileSystem::GetBaseDirectory();
        std::filesystem::path fullPath = basePath / m_Path;
        
        bool isGlobalPath = fullPath.is_absolute();

        if (!isGlobalPath) 
            fullPath = basePath / m_Path;

        return fullPath.string(); 
    }
}