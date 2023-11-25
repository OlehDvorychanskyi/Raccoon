#pragma once 
#include <Raccoon/Renderer/Texture2D.h>

namespace Raccoon
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string &filepath);
        OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat internalFormat = TextureFormat::RGBA8);
        ~OpenGLTexture2D();

        virtual void Update(const std::string &filepath, uint32_t offsetX = 0U, uint32_t offsetY = 0U) override;

        virtual void Bind(uint32_t unit) const override;

        virtual void SetQuality(TextureQuality quality) override;
        virtual void SetData(void *data, uint32_t size) override;

        virtual uint32_t GetWidth() const override { return m_Size.x; }
        virtual uint32_t GetHeight() const override { return m_Size.y; }
        virtual glm::u32vec2 GetSize() const override { return m_Size; };
        virtual uint32_t GetRendererID() const override { return m_Id; }   

        virtual bool operator==(const Texture2D& other) const override;     
    private:
        unsigned char* LoadTextureFromFile(const std::string &filepath);
        void ApplyQuality();
    private:
        uint32_t m_Id;
        glm::u32vec2 m_Size;
        TextureFormat m_Format;
        TextureQuality m_Quality;
    };
}