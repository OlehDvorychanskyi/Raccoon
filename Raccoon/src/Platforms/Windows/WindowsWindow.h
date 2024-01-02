#pragma once 
#include <Raccoon/Core/Window.h>
#include <Raccoon/Renderer/RendererContext.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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
        virtual void SetNativeWindow(void *window) override { m_Window = (GLFWwindow*)window; }

        virtual void SetTitle(const std::string &title) override { glfwSetWindowTitle(m_Window, title.c_str()); }
        virtual void Resize(uint32_t width, uint32_t height) override { glfwSetWindowSize(m_Window, (int)width, (int)height); }

        virtual void SetLogo(const FilePath &path) override;
        virtual void SetTitleBarDarkMode() override;

        virtual glm::uvec2 GetFramebufferSize() const override
        {
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(m_Window, &framebufferWidth, &framebufferHeight);
            return {(uint32_t)framebufferWidth, (uint32_t)framebufferHeight};
        }
        
        virtual uint32_t GetWidth() const override { return m_Data.Width; }
        virtual uint32_t GetHeight() const override { return m_Data.Height; }
        virtual void Shutdown() override;
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
    };
}