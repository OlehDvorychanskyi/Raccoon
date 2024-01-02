#pragma once
#include <glm/glm.hpp>
#include <string>
#include <imgui.h>

namespace Raccoon
{
    class Color
    {
    public:
        Color(float r, float g, float b, float a);
        Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
        Color(const std::string &hex);
        
        glm::vec4 GetRGB() const { return m_Color; }
        float GetRed() const { return m_Color.x; }
        float GetGreen() const { return m_Color.y; }
        float GetBlue() const { return m_Color.z; }
        float GetAlpha() const { return m_Color.w; }
        
        ImVec4 GetRGBImGui() const { return {m_Color.r, m_Color.g, m_Color.b, m_Color.a}; }
    private:
        glm::vec4 m_Color;
    };
}