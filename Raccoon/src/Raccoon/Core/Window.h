#pragma once 
#include <Raccoon/Events/Event.h>
#include <Raccoon/FileSystem/FilePath.h>
#include <Raccoon/Renderer/Color.h>
#include <string>
#include <memory>
#include <functional>
#include <glm/glm.hpp>

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
        using EventCallback = std::function<void(std::shared_ptr<Event> event)>;
        virtual void SetEventCallback(const EventCallback &callback) = 0;
        
        virtual void OnUpdate() = 0;

        virtual void SetVSync(bool value) = 0;
        virtual bool GetVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;
        virtual void SetNativeWindow(void *window) = 0;

        virtual void SetTitle(const std::string &title) = 0;
        virtual void SetTitleBarDarkMode() = 0;
        virtual void SetLogo(const FilePath &path) = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;    
        virtual float GetAspectRatio() const = 0;

        virtual glm::uvec2 GetFramebufferSize() const = 0;

        virtual void Shutdown() = 0; 

        static Window* Create(const WindowProperties &props = WindowProperties());
        virtual ~Window() = default;
    };
}