#pragma once 
#include <Raccoon/FileSystem/FileSystem.h>

namespace Raccoon
{
    class FilePath
    {
    public:
        FilePath() = default;
        FilePath(const std::string &relativePath);
        FilePath(const char *relativePath); 

        void SetPath(const std::string &path) { m_Path = path; }
        std::string GetGlobalPath() const;
        std::string GetRelativePath() const { return m_Path.string(); }
        std::filesystem::path GetPath() const { return m_Path; }
        std::string GetFileExtention() const { return m_Path.extension().string(); }
        std::string GetFileName() const { return m_Path.filename().string(); }
        std::string GetParentPath() const { return m_Path.parent_path().string(); }
    private:
        std::filesystem::path m_Path;
    };
}