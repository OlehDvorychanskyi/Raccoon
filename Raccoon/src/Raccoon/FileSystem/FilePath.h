#pragma once 
#include <filesystem>

namespace Raccoon
{
    class FilePath
    {
    friend bool operator== (const FilePath &lhs, const FilePath &rhs)
    {
        return lhs.m_Path == rhs.m_Path;
    }

    public:
        FilePath() = default;
        FilePath(const std::string &relativePath);
        FilePath(const std::filesystem::path &path);
        FilePath(const char *relativePath); 

        void SetPath(const std::string &path) { m_Path = path; }
        std::string GetGlobalPath() const;
        std::string GetRelativePath() const { return m_Path.string(); }
        std::filesystem::path GetPath() const { return m_Path; }
        std::string GetFileExtention() const { return m_Path.extension().string(); }
        std::string GetFileName() const { return m_Path.filename().string(); }
        std::string GetFileNameWithoutExtention() const { return m_Path.stem().string(); }
        std::string GetParentPath() const { return m_Path.parent_path().string(); }

        bool IsEmptyFolder();
        bool IsDirectory() const { return std::filesystem::is_directory(m_Path); }
        bool IsFile() const { return std::filesystem::is_regular_file(m_Path); }
        bool Exist() const { return std::filesystem::exists(m_Path); }
    private:
        std::filesystem::path m_Path;
    };

    bool CopyDirectory(const FilePath &source, const FilePath &destination);
    bool CopyFile(const FilePath &source, const FilePath &destination);
}