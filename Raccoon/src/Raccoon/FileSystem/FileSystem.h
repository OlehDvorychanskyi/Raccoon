#pragma once
#include <filesystem>
#include <Raccoon/FileSystem/FilePath.h>

namespace Raccoon
{
    class FileSystem
    {
    public:
        static FilePath GetAppDataPath();
        static FilePath GetBaseDirectory();
    private:
        static FilePath m_AppData;
    };
}