#pragma once 
#include <Raccoon/Core/KeyCodes.h>
#include <Raccoon/Core/MouseCodes.h>
#include <utility>

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

        Input() = delete;
        ~Input() = delete;
    };
}