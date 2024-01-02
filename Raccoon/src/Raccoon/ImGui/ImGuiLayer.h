#ifndef RE_NO_IMGUI
#pragma once 
#include <Raccoon/Core/Layer.h>

namespace Raccoon
{
    class ImGuiLayer : public Layer
    {
    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &event) override;

        ImGuiLayer() : Layer("ImGui") {}

        void Begin();
        void End();
        void BlockEvents(bool value) { m_BlockEvents = value; }  

        OVERRIDE_LAYER_DEBUG("ImGui")
    private:
        void SetDarkTheme();
    private:
        bool m_BlockEvents = false;
        std::string m_AppdataFolder, m_ImGuiConfigPath;
    };
}
#endif