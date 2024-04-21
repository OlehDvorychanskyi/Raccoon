#pragma once 
#include <string>
#include <Raccoon/Events/EventQueue.h>
#include <Raccoon/Events/WindowEvents.h>

namespace Raccoon
{
    struct WindowProperties
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProperties(const std::string &title = "Raccoon", uint32_t width = 1280, uint32_t height = 720)
            : Title{title}, Width{width}, Height{height} {}
    };

    class Window
    {
    public:
        void ProcessEvents();
        static void ProcessInternalEvents();

        virtual bool ShouldClose() const = 0;

        virtual void* GetNativeWindow() const = 0;

        virtual void SetTitle(const std::string &title) = 0;
        virtual std::string GetTitle() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual float GetAspectRatio() const = 0;

        static Window* Create(const WindowProperties &props = WindowProperties());
        virtual ~Window();
    protected:
        virtual void OnWindowClose(WindowCloseEvent &event) = 0;
        virtual void OnWindowResize(WindowResizeEvent &event) = 0;
    protected:
        EventQueue m_Events;

        static uint32_t s_WindowCount;
    };
}