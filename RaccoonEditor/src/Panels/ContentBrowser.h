#pragma once
#include <Raccoon/FileSystem/FilePath.h>
#include <Raccoon/Renderer/Color.h>
#include <Raccoon/Renderer/Texture2D.h>
#include <imgui.h>

namespace Raccoon
{
    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();
        ContentBrowserPanel(const FilePath &basePath);

        void SetBasePath(const FilePath &basePath);

        void OnImGuiRender();
    private:
        void RenderFileSystem(const std::filesystem::path &path);
        void RenderContent();
    private:
        FilePath m_BasePath, m_CurrentPath; 
        std::filesystem::path m_SelectedEntry;      

        Color dark{"1C1A20"}, grey{"222227"}, whiteGrey{"2E2E31"}, menu{"#16141A"};
        ImVec4 m_Dark{dark.GetRGBImGui()}, m_Grey{grey.GetRGBImGui()}, m_WhiteGrey{whiteGrey.GetRGBImGui()}, m_MenuColor{menu.GetRGBImGui()};
    };
}