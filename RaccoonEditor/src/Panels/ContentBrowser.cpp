#include <Panels/ContentBrowser.h>
// #include <Panels/icons/IconFont.h>
#include <Raccoon/ImGui/Fonts.h>

#include <locale>
#include <codecvt>

namespace Raccoon
{
    ContentBrowserPanel::ContentBrowserPanel() 
    {
        // ImGuiIO& io = ImGui::GetIO();

        // ImFontConfig fontConfig;
        // fontConfig.FontDataOwnedByAtlas = false;
        // fontConfig.MergeMode = true;

        // auto iconFont = io.Fonts->AddFontFromMemoryTTF(__Font_Awesome_6_Brands_Regular_400_otf, __Font_Awesome_6_Brands_Regular_400_otf_len, 16.0f, &fontConfig);

        // Fonts::LoadFont(iconFont, "Icon");
    }

    ContentBrowserPanel::ContentBrowserPanel(const FilePath &basePath)
        : ContentBrowserPanel()
    {
        m_BasePath = basePath;
        m_CurrentPath = basePath;
    }

    void ContentBrowserPanel::SetBasePath(const FilePath &basePath)
    {
        m_BasePath = basePath;
        m_CurrentPath = basePath;
    }

    void ContentBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("ContentBrowser");
        
        // if (ImGui::BeginTabBar("ContentBrowser", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_TabListPopupButton))
        // {
        //     if (ImGui::BeginTabItem("ContentBrowser", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton))
        //     {
        //         ImGui::SameLine();
        //         if (ImGui::Button("\u00D7")) 
        //         {
        //             ImGui::EndTabItem();
        //         }

        //         ImGui::EndTabItem();
        //     }

        //     ImGui::EndTabBar();
        // }
        static float filesystemWidth = 200.f;
        
        ImGui::Columns(2, "ContentColumns", false);

        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Dark);

        ImGui::SetColumnWidth(-1, filesystemWidth);

        ImGui::BeginChild("FileSystem", ImVec2(filesystemWidth, ImGui::GetContentRegionAvail().y));
        RenderFileSystem(m_BasePath.GetPath());
        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::BeginChild("Content");
        RenderContent();
        ImGui::EndChild();

        ImGui::PopStyleColor();

        ImGui::Columns(1);


        ImGui::End();
    }

    void ContentBrowserPanel::RenderFileSystem(const std::filesystem::path &path)
    {
        for (auto &entry : std::filesystem::directory_iterator(path))
        {
            const auto& entryPath = entry.path();
            const auto& entryName = entryPath.filename().string();

            ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_None | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (std::filesystem::is_directory(entryPath))
                nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
            else
                nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            
            if (m_SelectedEntry.string() == entryPath.string())
            {
                nodeFlags |= ImGuiTreeNodeFlags_Selected;
            }

            std::string icon = std::filesystem::is_directory(entryPath) ? "\xef\x81\xbb" : "\xef\x85\x9b";
        
            bool isOpen = ImGui::TreeNodeEx(entryName.c_str(), nodeFlags, "%s %s", icon.c_str(), entryName.c_str());

            if (ImGui::IsItemHovered() && (ImGui::IsMouseClicked(0) || ImGui::IsMouseClicked(1))) 
            {

                m_SelectedEntry = entryPath;

                if (std::filesystem::is_directory(entryPath) && ImGui::IsMouseDoubleClicked(0)) 
                {
                    m_CurrentPath = entryPath.string();
                } 
                else if (std::filesystem::is_regular_file(entryPath)) 
                {

                }
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("New folder"))
                {
                    if (std::filesystem::is_directory(m_SelectedEntry))
                    {
                        std::filesystem::create_directory(m_SelectedEntry.string() + "\\New folder");
                    }
                    else
                    {
                        std::filesystem::create_directory(m_SelectedEntry.parent_path().string() + "\\New folder");
                    }
                }

                if (ImGui::MenuItem("Delete"))
                {
                    std::filesystem::remove(entryPath);
                }

                ImGui::EndPopup();
            }

            

            if (isOpen && std::filesystem::is_directory(entryPath)) 
            {
                RenderFileSystem(entryPath);
                ImGui::TreePop();
            }
        }
    }

    void ContentBrowserPanel::RenderContent()
    {
        // static auto itemSize = ImVec2(64.f, 64.f);
        // auto columns = int32_t(ImGui::GetContentRegionAvail().x / itemSize.x);
        // ImGui::BeginTable("##ContentTable", columns);

        // // int index = columns;

        // for (auto &entry : std::filesystem::directory_iterator(m_CurrentPath.GetPath()))
        // {
        //     const auto& entryPath = entry.path();
        //     const auto& entryName = entryPath.filename().string();

        //     std::string icon = std::filesystem::is_directory(entryPath) ? "\xef\x81\xbb" : "\xef\x85\x9b";

        //     ImGui::SetWindowFontScale(5.0f);
        //     ImGui::Text("%s", icon.c_str());
        //     ImGui::SetWindowFontScale(1.0f);

        //     ImGui::Text("%s", entryName.c_str());

        //     ImGui::TableNextColumn();
        // }

        // ImGui::EndTable();

        // for (auto &entry : std::filesystem::directory_iterator(m_CurrentPath.GetPath()))
        // {
        //     const auto& entryPath = entry.path();
        //     const auto& entryName = entryPath.filename().string();

        //     std::string icon = std::filesystem::is_directory(entryPath) ? "\xef\x81\xbb" : "\xef\x85\x9b";

        //     bool selected = (m_SelectedFile == entryPath);

        //     auto cursor = ImGui::GetCursorPos();

        //     if (ImGui::Selectable(("##" + entryName).c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(64.f, 64.f)))
        //     {
        //         if (ImGui::IsItemClicked())
        //         {
        //             m_SelectedFile = entryPath;
        //         }

        //         if (ImGui::IsMouseDoubleClicked(0)) 
        //         {
        //             // open file
        //         }
        //     }

            

        //     ImGui::SetCursorPos(cursor);
            
        //     // ImGui::Columns(2, "##", false);

        //     ImGui::SetWindowFontScale(5.0f);
        //     ImGui::Text("%s", icon.c_str());
        //     ImGui::SetWindowFontScale(1.0f);

        //     ImGui::Text("%s", entryName.c_str());
        // }
    }
}