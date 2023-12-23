#include <Raccoon/ImGui/ImGuiLayer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Raccoon/Core/Application.h>
#include <Raccoon/Renderer/RendererCommand.h>

#include <glfw/glfw3.h>

#include <Raccoon/Renderer/Color.h>
#include <Raccoon/ImGui/Fonts.h>

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
    
        ImGui::StyleColorsDark();
        SetDarkTheme();

        float fontSize = 20.0f;// *2.0f;
		auto bold = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
		auto regular = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);
        
        Fonts::LoadFont(bold, "Bold");
        Fonts::LoadFont(regular, "Regular");

		io.FontDefault = Fonts::GetFont("Regular");

        GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 430 core");
    }

    void ImGuiLayer::OnDetach()
    {
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
        // ImVec4 Black = ImVec4(0.15294117647058825f, 0.21568627450980393f, 0.30196078431372547f, 1.f);
        // ImVec4 Black1 = ImVec4(0.3215686274509804f, 0.42745098039215684f, 0.5098039215686274f, 1.f);
        // ImVec4 Black2 = ImVec4(0.615686274509804f, 0.6980392156862745f, 0.7490196078431373f, 1.f);
        // ImVec4 White = ImVec4(0.8666666666666667f, 0.9019607843137255f, 0.9294117647058824f, 1.f);

        // ImVec4 Dark = ImVec4{ 0.00784313725490196f, 0.06274509803921569f, 0.1411764705882353f, 1.f };
        // ImVec4 DarkBlue = ImVec4{ 0.0196078431372549f, 0.14901960784313725, 0.34901960784313724f, 1.f };
        // ImVec4 DarkerBlue = ImVec4{ 0.12941176470588235f, 0.3137254901960784f, 0.5019607843137254f, 1.f };
        // ImVec4 Blue = ImVec4{ 0.22941176470588235f, 0.4137254901960784f, 0.6019607843137254f, 1.f };
        // ImVec4 BrightBlue = ImVec4{ 0.49019607843137253f, 0.6274509803921569f, 0.792156862745098f, 1.f };
        // ImVec4 White = ImVec4{ 0.7568627450980392f, 0.9098039215686274f, 1.f, 1.f };

        Color dark("#16141A"), dark2("#1C1A20"), dark1("#222227"), grey("#2E2E31"), whiteGrey("#525759"), white("#CCCEC9"); // #2E3336 #141218 #2E2E31
        

        auto& colors = ImGui::GetStyle().Colors;

        ImGui::GetStyle().TabBarBorderSize = 0.f;
        ImGui::GetStyle().DockingSeparatorSize = 3.f;
        ImGui::GetStyle().WindowBorderSize = 0.f;


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

        colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);

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



        // colors[ImGuiCol_Border] = BackGroundColor;
        // colors[ImGuiCol_BorderShadow] = DefaultColor;

        // colors[ImGuiCol_Tab] = DefaultColor;      
        // colors[ImGuiCol_TabHovered] = HoveredColor;
        // colors[ImGuiCol_TabActive] = HoveredColor; 
        // colors[ImGuiCol_TabUnfocused] = DefaultColor; 
        // colors[ImGuiCol_TabUnfocusedActive] = DefaultColor;

        // colors[ImGuiCol_Button] = DefaultColor;
        // colors[ImGuiCol_ButtonHovered] = HoveredColor;
        // colors[ImGuiCol_ButtonActive] = HoveredColor;

        // colors[ImGuiCol_Header] = DefaultColor;
        // colors[ImGuiCol_HeaderHovered] = DefaultColor;
        // colors[ImGuiCol_HeaderActive] = DefaultColor;

        // colors[ImGuiCol_Text] = TextColor;
        // colors[ImGuiCol_TextSelectedBg] = DefaultColor;

        // colors[ImGuiCol_TitleBg] = BackGroundColor;
        // colors[ImGuiCol_TitleBgActive] = BackGroundColor;
        // colors[ImGuiCol_TitleBgCollapsed] = BackGroundColor;

        // colors[ImGuiCol_FrameBg] = DefaultColor;
        // colors[ImGuiCol_FrameBgHovered] = HoveredColor;
        // colors[ImGuiCol_FrameBgActive] = HoveredColor;

        // colors[ImGuiCol_ResizeGrip] = BackGroundColor;
        // colors[ImGuiCol_ResizeGripHovered] = BackGroundColor;
        // colors[ImGuiCol_ResizeGripActive] = BackGroundColor;
        // ---------------------------------------------

        // colors[ImGuiCol_TableHeaderBg] = Dark;

        // colors[ImGuiCol_ScrollbarBg] = BackGroundColor; 
        // colors[ImGuiCol_ScrollbarGrab] = BackGroundColor;
        // colors[ImGuiCol_ScrollbarGrabHovered] = BackGroundColor;
        // colors[ImGuiCol_ScrollbarGrabActive] = BackGroundColor;

        // colors[ImGuiCol_CheckMark] = DarkBlue;

        // colors[ImGuiCol_SliderGrab] = BackGroundColor;
        // colors[ImGuiCol_SliderGrabActive] = BackGroundColor;

        // colors[ImGuiCol_Separator] = BackGroundColor;
        // colors[ImGuiCol_SeparatorHovered] = BackGroundColor;
        // colors[ImGuiCol_SeparatorActive] = BackGroundColor;


        // colors[ImGuiCol_DragDropTarget] = Dark; 
        // colors[ImGuiCol_PlotLines] = BackGroundColor;
        // colors[ImGuiCol_PlotLines] = BackGroundColor;
        // colors[ImGuiCol_PlotLinesHovered] = BackGroundColor;
        // colors[ImGuiCol_PlotHistogram] = BackGroundColor;
        // colors[ImGuiCol_PlotHistogramHovered] = BackGroundColor;

        // colors[ImGuiCol_NavHighlight] = BackGroundColor;
        // colors[ImGuiCol_NavWindowingHighlight] = BackGroundColor;
        // colors[ImGuiCol_NavWindowingDimBg] = BackGroundColor;
        // colors[ImGuiCol_ModalWindowDimBg] = BackGroundColor;
    }
}

// enum ImGuiCol_
// {
//     ImGuiCol_Text,
//     ImGuiCol_TextDisabled,
//     ImGuiCol_WindowBg,              // Background of normal windows
//     ImGuiCol_ChildBg,               // Background of child windows
//     ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
//     ImGuiCol_Border,
//     ImGuiCol_BorderShadow,
//     ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
//     ImGuiCol_FrameBgHovered,
//     ImGuiCol_FrameBgActive,
//     ImGuiCol_TitleBg,
//     ImGuiCol_TitleBgActive,
//     ImGuiCol_TitleBgCollapsed,
//     ImGuiCol_MenuBarBg,
//     ImGuiCol_ScrollbarBg,
//     ImGuiCol_ScrollbarGrab,
//     ImGuiCol_ScrollbarGrabHovered,
//     ImGuiCol_ScrollbarGrabActive,
//     ImGuiCol_CheckMark,
//     ImGuiCol_SliderGrab,
//     ImGuiCol_SliderGrabActive,
//     ImGuiCol_Button,
//     ImGuiCol_ButtonHovered,
//     ImGuiCol_ButtonActive,
//     ImGuiCol_Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
//     ImGuiCol_HeaderHovered,
//     ImGuiCol_HeaderActive,
//     ImGuiCol_Separator,
//     ImGuiCol_SeparatorHovered,
//     ImGuiCol_SeparatorActive,
//     ImGuiCol_ResizeGrip,            // Resize grip in lower-right and lower-left corners of windows.
//     ImGuiCol_ResizeGripHovered,
//     ImGuiCol_ResizeGripActive,
//     ImGuiCol_Tab,                   // TabItem in a TabBar
//     ImGuiCol_TabHovered,
//     ImGuiCol_TabActive,
//     ImGuiCol_TabUnfocused,
//     ImGuiCol_TabUnfocusedActive,
//     ImGuiCol_DockingPreview,        // Preview overlay color when about to docking something
//     ImGuiCol_DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
//     ImGuiCol_PlotLines,
//     ImGuiCol_PlotLinesHovered,
//     ImGuiCol_PlotHistogram,
//     ImGuiCol_PlotHistogramHovered,
//     ImGuiCol_TableHeaderBg,         // Table header background
//     ImGuiCol_TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
//     ImGuiCol_TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
//     ImGuiCol_TableRowBg,            // Table row background (even rows)
//     ImGuiCol_TableRowBgAlt,         // Table row background (odd rows)
//     ImGuiCol_TextSelectedBg,
//     ImGuiCol_DragDropTarget,        // Rectangle highlighting a drop target
//     ImGuiCol_NavHighlight,          // Gamepad/keyboard: current highlighted item
//     ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
//     ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
//     ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
//     ImGuiCol_COUNT
// };