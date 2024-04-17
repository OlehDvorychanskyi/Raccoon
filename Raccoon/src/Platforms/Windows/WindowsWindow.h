#pragma once 
#include <Raccoon/Core/Window.h>
#include <Windows.h>

namespace Raccoon
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties &props);
        ~WindowsWindow();

        virtual void ProcessEvents() override;

        virtual void* GetNativeWindow() const { return m_NativeWindow; }

        virtual void SetTitle(const std::string &title) override;
        virtual std::string GetTitle() const { return m_Data.Title; }

        virtual void Resize(uint32_t width, uint32_t height) override;
        
        virtual uint32_t GetWidth() const { return m_Data.Width; }
        virtual uint32_t GetHeight() const { return m_Data.Height; }
        virtual float GetAspectRatio() const { return (float)m_Data.Width / (float)m_Data.Height; }
    private:
        void InitWindowClass();
        void InitWindow();
    private:
        WindowProperties m_Data;

        HWND m_NativeWindow;
        static WNDCLASS s_WindowClass;
    };
}