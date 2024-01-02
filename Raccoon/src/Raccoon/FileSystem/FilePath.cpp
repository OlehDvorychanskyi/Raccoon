#include <Raccoon/FileSystem/FilePath.h>
#include <Raccoon/FileSystem/FileSystem.h>
#include <Raccoon/Core/Assert.h>
#include <fstream>

namespace Raccoon
{
    FilePath::FilePath(const std::string &relativePath)
    {
        m_Path = relativePath;
    }

    FilePath::FilePath(const std::filesystem::path &path)
    {
        m_Path = path;
    }

    FilePath::FilePath(const char *relativePath)
    {
        m_Path = relativePath;
    }

    std::string FilePath::GetGlobalPath() const 
    { 
        std::filesystem::path basePath = FileSystem::GetBaseDirectory().GetPath();
        std::filesystem::path fullPath = basePath / m_Path;
        
        bool isGlobalPath = fullPath.is_absolute();

        if (!isGlobalPath) 
            fullPath = basePath / m_Path;

        return fullPath.string(); 
    }

    bool FilePath::IsEmptyFolder()
    {
        if (Exist() && IsDirectory())
        {
            if (std::filesystem::begin(std::filesystem::directory_iterator(m_Path)) == std::filesystem::end(std::filesystem::directory_iterator(m_Path)))
            {
                return true;
            }
        }
        else
            RE_CORE_WARN("{0} is not a directory", GetRelativePath());
        return false;
    }

    bool CopyFile(const FilePath &source, const FilePath &destination)
    {
        std::ifstream sourceFile(source.GetRelativePath(), std::ios::binary);
        std::ofstream destinationFile(destination.GetRelativePath(), std::ios::binary);

        if (!sourceFile || !destinationFile) 
        {
            RE_CORE_ERROR("Failed to open files for copying");
            return false;
        }

        destinationFile << sourceFile.rdbuf();

        return true;
    }

    bool CopyDirectory(const FilePath &source, const FilePath &destination)
    {
        try 
        {
            std::filesystem::create_directories(destination.GetRelativePath());

            for (const auto& entry : std::filesystem::directory_iterator(source.GetPath())) 
            {
                const std::filesystem::path& sourcePath = entry.path();
                const std::filesystem::path destinationPath = destination.GetPath() / entry.path().filename();

                if (std::filesystem::is_directory(sourcePath)) 
                    CopyDirectory(sourcePath, destinationPath);
                else 
                    CopyFile(sourcePath, destinationPath);
            }

            return true;
        } 
        catch (const std::exception& e) 
        {
            RE_CORE_ERROR("Error copying directory: {0}", e.what());
            return false;
        }
    }
}