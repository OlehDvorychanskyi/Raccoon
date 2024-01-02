#include <Raccoon/FileSystem/FileSystem.h>
#include <Raccoon/Core/Assert.h>
#include <string>

namespace Raccoon
{
    FilePath FileSystem::m_AppData;
 
    FilePath FileSystem::GetAppDataPath()
    {
        if (m_AppData.GetRelativePath().empty())
        {
            char* folder = std::getenv("APPDATA");
            if (folder != nullptr)
            {
                m_AppData = folder + std::string("\\Raccoon");
            }
            else 
                RE_CORE_ERROR("{0}", "Fail to get APPDATA path");
        }
        return m_AppData;
    }

    FilePath FileSystem::GetBaseDirectory()
    {
        return std::filesystem::current_path(); 
    }
}