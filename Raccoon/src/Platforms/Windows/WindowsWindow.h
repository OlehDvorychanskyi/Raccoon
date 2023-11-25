#pragma once 
#include <Raccoon/Core/Window.h>
#include <Raccoon/Renderer/RendererContext.h>

#include <GLFW/glfw3.h>

namespace Raccoon
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties &props);
        ~WindowsWindow();

        void OnUpdate() override;

        virtual void SetVSync(bool value) override;
        virtual bool GetVSync() const override { return m_Data.VSync; }

        virtual float GetAspectRatio() const override { return (float)GetWidth() / (float)GetHeight(); }
        
        virtual void SetEventCallback(const EventCallback &callback) override { m_Data.Callback = callback; }
        
        virtual void* GetNativeWindow() const override { return m_Window; }
        
        virtual uint32_t GetWidth() const override { return m_Data.Width; }
        virtual uint32_t GetHeight() const override { return m_Data.Height; }
    private:
        struct WindowData
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
            bool VSync;
            EventCallback Callback;
        };
        WindowData m_Data;
        GLFWwindow *m_Window;
        std::unique_ptr<RendererContext> m_Context;
        static uint32_t WindowCount;
    private:
        void Init(const WindowProperties& props);
        void Shutdown();
    };
}