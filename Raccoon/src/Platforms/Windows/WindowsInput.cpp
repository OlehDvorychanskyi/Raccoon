#include <Raccoon/Core/Input.h>
#include <Raccoon/Core/Application.h>

#include <glfw/glfw3.h>

namespace Raccoon
{   
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto status = glfwGetKey(window, static_cast<int32_t>(keycode));
        return status == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto status = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return status == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetCursorPosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {float(xPos), float(yPos)};
    }

    float Input::GetCursorX()
    {
        auto[x, y] = GetCursorPosition();
        return x;
    }

    float Input::GetCursorY()
    {
        auto[x, y] = GetCursorPosition();
        return y;
    }   
}