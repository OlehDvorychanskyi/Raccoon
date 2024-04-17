#pragma once 
#include <string>

namespace Raccoon
{
    struct WindowProperties
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool VSync;

        WindowProperties(const std::string &title = "Raccoon", uint32_t width = 1280, uint32_t height = 720, bool vsync = true)
            : Title{title}, Width{width}, Height{height}, VSync{vsync} {}
    };

    class Window
    {
    public:
        virtual void ProcessEvents() = 0;
        static void ProcessInternalEvents();
        // virtual void SwapBuffers() = 0; for future

        virtual void* GetNativeWindow() const = 0;
        // virtual void SetNativeWindow(void *window) = 0;

        virtual void SetTitle(const std::string &title) = 0;
        virtual std::string GetTitle() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual float GetAspectRatio() const = 0;

        virtual void SetVSync(bool value) = 0;
        virtual bool GetVSync() const = 0;

        static Window* Create(const WindowProperties &props = WindowProperties());
        virtual ~Window();
    protected:
        static uint32_t s_WindowCount;
    };
}