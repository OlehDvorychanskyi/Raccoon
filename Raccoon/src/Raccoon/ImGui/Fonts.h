#ifndef RE_NO_IMGUI
#pragma once 
#include <map>
#include <string>
#include <imgui.h>
#include <Raccoon/FileSystem/FilePath.h>

namespace Raccoon
{
    class Fonts
    {
    public:
        static ImFont* GetFont(const std::string &name);
        static void LoadFont(ImFont *font, const std::string &name);
    private:
        static std::map<std::string, ImFont*> m_Fonts;
    };
}
#endif