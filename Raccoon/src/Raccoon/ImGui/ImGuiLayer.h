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

        void Begin();
        void End();
        void BlockEvents(bool value) { m_BlockEvents = value; }  

        OVERRIDE_LAYER_DEBUG("ImGui")
    private:
        void SetDarkTheme();
    private:
        // bool m_BlockEvents = true;
        bool m_BlockEvents = false;
    };
}