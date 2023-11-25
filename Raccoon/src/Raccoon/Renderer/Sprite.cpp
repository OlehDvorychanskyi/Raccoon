#include <Raccoon/Renderer/Sprite.h>

namespace Raccoon
{
    Sprite::Sprite(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &bottomLeft, const glm::vec2 &upperRight)
    {
        m_Texture = texture;

        m_TextureCoords [0] = { bottomLeft.x, bottomLeft.y };
        m_TextureCoords [1] = { upperRight.x, bottomLeft.y };
        m_TextureCoords [2] = { upperRight.x, upperRight.y };
        m_TextureCoords [3] = { bottomLeft.x, upperRight.y };
    }

    std::shared_ptr<Sprite> Sprite::CreateFromCoords(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &spriteSize, const glm::vec2 &spriteCoords)
    {
        glm::vec2 bottomLeft = { (spriteCoords.x * spriteSize.x) / texture->GetWidth(), (spriteCoords.y * spriteSize.y) / texture->GetHeight() };
        glm::vec2 upperRight = { ((spriteCoords.x + 1) * spriteSize.x) / texture->GetWidth(), ((spriteCoords.y + 1) * spriteSize.y) / texture->GetHeight() };

        return std::make_shared<Sprite>(texture, bottomLeft, upperRight);
    }
    
    std::shared_ptr<Sprite> Sprite::CreateFromOffset(const std::shared_ptr<Texture2D> &texture, const glm::vec2 &spriteSize, const glm::vec2 &spriteOffset)
    {
        glm::vec2 bottomLeft = { spriteOffset.x / texture->GetWidth(), spriteOffset.y / texture->GetHeight() };
        glm::vec2 upperRight = { (spriteOffset.x + spriteSize.x) / texture->GetWidth(), (spriteOffset.y + spriteSize.y) / texture->GetHeight() };
        
        return std::make_shared<Sprite>(texture, bottomLeft, upperRight);
    }
}