#pragma once 
#include <Raccoon/Renderer/Texture2D.h>
#include <memory>

namespace Raccoon
{
    class Sprite
    {
    public:
        Sprite(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &bottomLeft, const glm::vec2 &upperRight);
        
        const glm::vec2* GetTextureCoords() const { return m_TextureCoords; }
        const std::shared_ptr<Texture2D>& GetTexture() const { return m_Texture; }

        static std::shared_ptr<Sprite> CreateFromCoords(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &spriteSize, const glm::vec2 &spriteCoords);
        static std::shared_ptr<Sprite> CreateFromOffset(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &spriteSize, const glm::vec2 &spriteOffset);
    private:
        std::shared_ptr<Texture2D> m_Texture;
        glm::vec2 m_TextureCoords[4];
    };
}