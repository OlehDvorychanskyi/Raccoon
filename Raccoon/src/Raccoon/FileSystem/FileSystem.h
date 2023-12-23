#pragma once
#include <filesystem>

namespace Raccoon
{
    class FileSystem
    {
    public:
        static std::filesystem::path GetBaseDirectory(); // TODO: think about return type
    private:
        static std::filesystem::path m_BasePath;
    };
}