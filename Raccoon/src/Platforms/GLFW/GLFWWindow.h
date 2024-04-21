#pragma once 
#include <Raccoon/Core/Window.h>
#include <functional>
#include <memory>

class GLFWwindow;

namespace Raccoon
{
    struct WindowData
    {
        WindowProperties Props;
        std::function<void(std::shared_ptr<Event> event)> Callback;
    };

    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProperties &props);
        ~GLFWWindow();

        virtual bool ShouldClose() const override;

        virtual void* GetNativeWindow() const { return m_NativeWindow; }

        virtual void SetTitle(const std::string &title) override;
        virtual std::string GetTitle() const { return m_Data.Props.Title; }

        virtual void Resize(uint32_t width, uint32_t height) override;
        
        virtual uint32_t GetWidth() const { return m_Data.Props.Width; }
        virtual uint32_t GetHeight() const { return m_Data.Props.Height; }
        virtual float GetAspectRatio() const { return (float)m_Data.Props.Width / (float)m_Data.Props.Height; }
    protected:
        virtual void OnWindowClose(WindowCloseEvent &event) override;
        virtual void OnWindowResize(WindowResizeEvent &event) override;
    private:
        void InitWindow();
        void InitEventCallbacks();

        void Shutdown();
    private:
        WindowData m_Data;

        GLFWwindow *m_NativeWindow;
    };
}