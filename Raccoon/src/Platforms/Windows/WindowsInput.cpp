#include <Raccoon/Core/Input.h>
#include <Raccoon/Core/Application.h>

#include <glfw/glfw3.h>

namespace Raccoon
{   
    bool Input::m_BlockInputs = false;

    bool Input::IsKeyPressed(KeyCode keycode)
    {
        if (!m_BlockInputs)
        {
            auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
            auto status = glfwGetKey(window, static_cast<int32_t>(keycode));
            return status == GLFW_PRESS;
        }
        return false;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        if (!m_BlockInputs)
        {
            auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
            auto status = glfwGetMouseButton(window, static_cast<int32_t>(button));
            return status == GLFW_PRESS;
        }
        return false;
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

    glm::vec2 Input::GetCursorGlobalPosition()
    {
        auto[x, y] = Input::GetCursorPosition();
        auto windowPosition = Input::GetWindowPosition();
        return {windowPosition.x + x, windowPosition.y + y};
    }

    glm::vec2 Input::GetWindowPosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return {(float)x, (float)y};
    }

    void Input::BlockInputs(bool value)
    {
        m_BlockInputs = value;
    }
}