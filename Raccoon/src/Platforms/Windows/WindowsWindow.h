#pragma once 
#include <Raccoon/Core/Window.h>
#include <Raccoon/Events/Event.h>
#include <Windows.h>
#include <functional>
#include <memory>

namespace Raccoon
{
    struct WindowData
    {
        WindowProperties Props;
        std::function<void(std::shared_ptr<Event> event)> Callback;
    };

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties &props);
        ~WindowsWindow();

        virtual bool ShouldClose() const override { return m_ShouldClose; }

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
        void InitWindowClass();
        void InitWindow();
    private:
        WindowData m_Data;
        bool m_ShouldClose = false;

        HWND m_NativeWindow;
        static WNDCLASS s_WindowClass;
    };
}