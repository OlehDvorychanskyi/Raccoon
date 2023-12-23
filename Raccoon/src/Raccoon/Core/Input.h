#pragma once 
#include <Raccoon/Core/KeyCodes.h>
#include <Raccoon/Core/MouseCodes.h>
#include <utility>
#include <glm/glm.hpp>

namespace Raccoon
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode keycode);
        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetCursorPosition();
        static float GetCursorX();
        static float GetCursorY();
        
        static glm::vec2 GetCursorGlobalPosition();

        static glm::vec2 GetWindowPosition();

        static void BlockInputs(bool value);

        Input() = delete;
        ~Input() = delete;
    private:
        static bool m_BlockInputs;
    };
}