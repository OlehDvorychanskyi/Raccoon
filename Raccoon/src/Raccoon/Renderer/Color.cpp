#include <Raccoon/Renderer/Color.h>
#include <Raccoon/Math/Math.h>

#include <iomanip>
#include <sstream>

namespace Raccoon
{
    Color::Color(float r, float g, float b, float a)
    {
        m_Color = glm::vec4(r, g, b, a);
    }

    Color::Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
    {
        float R = ConvertValue((float)r, 0.f, 255.f, 0.f, 1.f);
        float G = ConvertValue((float)g, 0.f, 255.f, 0.f, 1.f);
        float B = ConvertValue((float)b, 0.f, 255.f, 0.f, 1.f);
        float A = ConvertValue((float)a, 0.f, 255.f, 0.f, 1.f);

        m_Color = glm::vec4(R, G, B, A);
    }

    Color::Color(const std::string &hex)
    {
        std::string hexValue = (hex[0] == '#') ? hex.substr(1) : hex;

        float r, g, b, A = 1.f;
        r = std::stoi(hexValue.substr(0, 2), nullptr, 16);
        g = std::stoi(hexValue.substr(2, 2), nullptr, 16);
        b = std::stoi(hexValue.substr(4, 2), nullptr, 16);

        float R = ConvertValue(r, 0.f, 255.f, 0.f, 1.f);
        float G = ConvertValue(g, 0.f, 255.f, 0.f, 1.f);
        float B = ConvertValue(b, 0.f, 255.f, 0.f, 1.f);

        m_Color = glm::vec4(R, G, B, A);
    }
}