#pragma once 
#include <string>
#include <memory>
#include <cstdint>

#include <glm/glm.hpp>

namespace Raccoon
{
    enum class TextureFiltering : uint8_t
    {
        Linear,
        Nearest
    };

    enum class TextureFormat : uint8_t
    {
        RGB8,
        RGBA8
    };

    enum class TextureQuality : uint8_t
    {
        Pixelated,
        Smooth
    };

    class Texture2D
    {
    public:
        virtual ~Texture2D() = default;
        virtual void Bind(uint32_t unit = 0) const = 0; // ToDo: Count system for texture units

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual glm::u32vec2 GetSize() const = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual void SetQuality(TextureQuality quality) = 0;
        virtual void SetData(void *data, uint32_t size) = 0;

        virtual void Update(const std::string &filepath, uint32_t offsetX = 0U, uint32_t offsetY = 0U) = 0;
        
        virtual bool operator==(const Texture2D& other) const = 0;

        static std::shared_ptr<Texture2D> Create(const std::string &filepath);
        static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height, TextureFormat internalFormat = TextureFormat::RGBA8);
    };
}