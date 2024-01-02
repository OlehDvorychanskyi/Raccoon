#ifndef RE_NO_IMGUI
#include <Raccoon/ImGui/ImGuiLayer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Raccoon/Core/Application.h>
#include <Raccoon/Renderer/RendererCommand.h>

#include <glfw/glfw3.h>

#include <Raccoon/Renderer/Color.h>
#include <Raccoon/ImGui/Fonts.h>

#include <../fonts/IconFont.h>
#include <../fonts/OpenSans-Bold.h>
#include <../fonts/OpenSans-Regular.h>

namespace Raccoon
{
    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        
        char* folder = std::getenv("APPDATA");
        if (folder != nullptr)
            m_AppdataFolder = folder;
        else 
            RE_CORE_ERROR("{0}", "Fail to get APPDATA path");

        m_ImGuiConfigPath = m_AppdataFolder + "/Raccoon/editor.ini";
        ImGui::GetIO().IniFilename = m_ImGuiConfigPath.c_str();

        ImGui::StyleColorsDark();
        SetDarkTheme();

        float fontSize = 20.0f;
        
        ImFontConfig config;
        config.FontDataOwnedByAtlas = false;
        auto bold = io.Fonts->AddFontFromMemoryTTF(OpenSans_Bold, OpenSans_Bold_len, fontSize, &config);
        auto regular = io.Fonts->AddFontFromMemoryTTF(OpenSans_Regular, OpenSans_Regular_len, fontSize, &config);
        Fonts::LoadFont(bold, "Bold");
        Fonts::LoadFont(regular, "Regular");

        ImFontConfig fontConfig;
        fontConfig.MergeMode = true;
        fontConfig.PixelSnapH = true;
        fontConfig.FontDataOwnedByAtlas = false;
        // fontConfig.GlyphMinAdvanceX = fontSize * 2.f / 3.f;

        static const ImWchar icons_ranges[] = { 0xe005, 0xf8ff, 0 };   

        auto iconFont = io.Fonts->AddFontFromMemoryTTF(icon_font, icon_font_len, fontSize, &fontConfig, icons_ranges);

        Fonts::LoadFont(iconFont, "Icon");

        io.FontDefault = Fonts::GetFont("Regular");

        GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 430 core");

        ImGui::LoadIniSettingsFromDisk(m_ImGuiConfigPath.c_str());
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui::SaveIniSettingsToDisk(m_ImGuiConfigPath.c_str());
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event &event)
    {
        if (m_BlockEvents)
        {
            ImGuiIO &io = ImGui::GetIO();
            event.Handled |= event.BelongToCategory(EventCategory::MouseEvent) & io.WantCaptureMouse; 
            event.Handled |= event.BelongToCategory(EventCategory::KeyEvent) & io.WantCaptureKeyboard; 
        }
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {   
        ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
    }

    void ImGuiLayer::SetDarkTheme()
    {
        Color dark("#16141A"), dark2("#1C1A20"), dark1("#222227"), grey("#2E2E31"), whiteGrey("#525759"), white("#CCCEC9");

        auto& style = ImGui::GetStyle();

        auto& colors = style.Colors;

        style.TabBarBorderSize = 0.f;
        style.DockingSeparatorSize = 3.f;
        style.WindowBorderSize = 1.f;
        style.FramePadding.y = 4.f;
        // style.ItemSpacing = ImVec2(8.f, 8.f);
        style.DockingSeparatorSize = 1.f;

        style.WindowPadding = ImVec2(5.f, 5.f);
        style.FramePadding = ImVec2(5.f, 5.f);
        style.ItemSpacing = ImVec2(5.f, 5.f);
        style.ChildRounding = 5.f;
        style.FrameRounding = 5.f;
        style.PopupRounding = 5.f;



        // ImVec4 BackGroundColor = Dark;
        // ImVec4 DefaultColor = DarkBlue;
        // ImVec4 HoveredColor = DarkerBlue;
        // ImVec4 ActiveColor = Blue;
        // ImVec4 TextColor = BrightBlue;

        
        ImVec4 BackGroundColor = dark.GetRGBImGui();
        ImVec4 SecondBackGroundColor = dark1.GetRGBImGui();
        ImVec4 DarkGray = dark2.GetRGBImGui();
        ImVec4 Grey = grey.GetRGBImGui();
        ImVec4 WhiteGrey = whiteGrey.GetRGBImGui();
        ImVec4 White = white.GetRGBImGui();
        // ImVec4 DefaultColor = DarkBlue;
        // ImVec4 HoveredColor = DarkerBlue;
        // ImVec4 ActiveColor = Blue;
        // ImVec4 TextColor = BrightBlue;

        // -----------------------------------------------

		colors[ImGuiCol_WindowBg] = SecondBackGroundColor;
		colors[ImGuiCol_ChildBg] = SecondBackGroundColor;
		colors[ImGuiCol_PopupBg] = SecondBackGroundColor;
        colors[ImGuiCol_MenuBarBg] = BackGroundColor;

        colors[ImGuiCol_Border] = WhiteGrey;

        colors[ImGuiCol_Tab] = SecondBackGroundColor;      
        colors[ImGuiCol_TabHovered] = WhiteGrey;
        colors[ImGuiCol_TabActive] = WhiteGrey; 
        colors[ImGuiCol_TabUnfocused] = SecondBackGroundColor; 
        colors[ImGuiCol_TabUnfocusedActive] = SecondBackGroundColor;

        colors[ImGuiCol_ResizeGrip] = WhiteGrey;
        colors[ImGuiCol_ResizeGripHovered] = WhiteGrey;
        colors[ImGuiCol_ResizeGripActive] = WhiteGrey;

        colors[ImGuiCol_TitleBg] = DarkGray;
        colors[ImGuiCol_TitleBgActive] = DarkGray;

        colors[ImGuiCol_Header] = Grey;
        colors[ImGuiCol_HeaderHovered] = WhiteGrey;
        colors[ImGuiCol_HeaderActive] = WhiteGrey;

        colors[ImGuiCol_Text] = White;
        colors[ImGuiCol_TextSelectedBg] = White;

        colors[ImGuiCol_FrameBg] = Grey;
        colors[ImGuiCol_FrameBgHovered] = WhiteGrey;
        colors[ImGuiCol_FrameBgActive] = WhiteGrey;

        colors[ImGuiCol_Button] = Grey;
        colors[ImGuiCol_ButtonHovered] = WhiteGrey;
        colors[ImGuiCol_ButtonActive] = WhiteGrey;

        colors[ImGuiCol_SliderGrab] = WhiteGrey;
        colors[ImGuiCol_SliderGrabActive] = White;
        // colors[ImGuiCol_Separator] = 
        // colors[ImGuiCol_SeparatorHovered] = Grey;
        // colors[ImGuiCol_SeparatorActive] = Grey;
        
        // colors[ImGuiCol_DockingPreview] = ImVec4(0.f, 0.f, 0.f, 0.f);;
        // colors[ImGuiCol_DockingEmptyBg] = Grey;  



        
    }
}
#endif