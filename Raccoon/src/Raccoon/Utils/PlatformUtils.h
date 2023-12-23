#pragma once 
#include <string>

namespace Raccoon
{
    class FileDialogs
    {
    public: 
        static std::string OpenFile(const char *filters);
        static std::string SaveFile(const char *filters);
        static std::string OpenFolder();
    };

    class Time
    {
    public:
        static float GetTime();
    };
}