#pragma once 
#include <Raccoon/Core/Assert.h>
#include <Raccoon/Core/LayerStack.h>
#include <Raccoon/Events/EventQueue.h>
#include <Raccoon/Core/Window.h>
#include <Raccoon/Events/WindowEvents.h>
#include <Raccoon/ImGui/IMGuiLayer.h>

#include <Raccoon/Renderer/Shaders.h>
#include <Raccoon/Renderer/IndexBuffer.h>
#include <Raccoon/Renderer/VertexBuffer.h>
#include <Raccoon/Renderer/VertexArray.h>

#include <Raccoon/Renderer/Renderer.h>

#include <memory>

int main(int argc, char** argv);

namespace Raccoon
{
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;  

        char* operator[] (std::size_t index)
        {
            RE_CORE_ASSERT(index < Count, "Args index should be less then args count");
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name = "Raccoon Application";
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application
    { 
    public:
        Application(const ApplicationSpecification& specification);
        ~Application(); 

        Window& GetWindow() { return *m_Window; }
        ApplicationSpecification& GetSpecification() { return m_Specification; }

        #ifndef RE_NO_IMGUI
            ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; } 
        #endif

        float GetFrameTime() const { return m_FrameTime; }

        void Close();

        void OnWindowClose(WindowCloseEvent &event);
        void OnWindowResize(WindowResizeEvent &event);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        static Application& Get() { return *m_Instance; }
    private:
        void Run();
        void QueueEvent(std::shared_ptr<Event> event);
        void DispatchEvent();
    private:
        ApplicationSpecification m_Specification;
        Window *m_Window;
        LayerStack m_Layers;
        
        #ifndef RE_NO_IMGUI
            ImGuiLayer* m_ImGuiLayer;
        #endif 

        EventQueue m_Events;
        bool m_Running = true;
        static Application *m_Instance;
        float m_FrameTime = 0.f;

        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);
}