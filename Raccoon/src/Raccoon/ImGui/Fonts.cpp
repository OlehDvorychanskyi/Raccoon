#include <Raccoon/ImGui/Fonts.h>
#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    std::map<std::string, ImFont*> Fonts::m_Fonts;

    ImFont* Fonts::GetFont(const std::string &name)
    {
        return m_Fonts[name];
    }

    void Fonts::LoadFont(ImFont *font, const std::string &name)
    {
        RE_CORE_ASSERT(m_Fonts.find(name) == m_Fonts.end(), "Font already exist!");
        m_Fonts[name] = font;
    }
}