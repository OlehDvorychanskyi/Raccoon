#include <Platforms/OpenGL/OpenGLTexture2D.h>
#include <Raccoon/Core/Assert.h>

#include <glad/glad.h>
#include <stb_image.h>

#include <cmath>

namespace Raccoon
{
    uint32_t ToGLInternalFormat(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGB8:
            return GL_RGB8;
        case TextureFormat::RGBA8:
            return GL_RGBA8;
        }
        
        RE_CORE_ASSERT(false, "Unknown texture format");
        return 0;
    }

    uint32_t GetPixelSize(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGB8:
            return 3;
        case TextureFormat::RGBA8:
            return 4;
        }

        RE_CORE_ASSERT(false, "Unknown texture format");
        return 0;
    }

    uint32_t ToGLDataFormat(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGB8:
            return GL_RGB;
        case TextureFormat::RGBA8:
            return GL_RGBA;
        }

        RE_CORE_ASSERT(false, "Unknown texture format");
        return 0;
    }

    OpenGLTexture2D::OpenGLTexture2D(const FilePath &filepath)
        : m_Quality {TextureQuality::Pixelated}
    {
        unsigned char *data = LoadTextureFromFile(filepath); 

        if (data)
        {
            m_Loaded = true;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
            glTextureStorage2D(m_Id, 1, ToGLInternalFormat(m_Format), m_Size.x, m_Size.y);        
            glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, ToGLDataFormat(m_Format), GL_UNSIGNED_BYTE, data);

            ApplyQuality();

            stbi_image_free(data);
        }
    }

    OpenGLTexture2D::OpenGLTexture2D(unsigned char *data, unsigned int length)
        : m_Quality {TextureQuality::Pixelated}
    {
        unsigned char* image = LoadTextureFromMemory(data, length); 

        if (image)
        {
            m_Loaded = true;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
            glTextureStorage2D(m_Id, 1, ToGLInternalFormat(m_Format), m_Size.x, m_Size.y);        
            glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, ToGLDataFormat(m_Format), GL_UNSIGNED_BYTE, data);

            ApplyQuality();

            stbi_image_free(image);
        }
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat internalFormat)
        : m_Size(width, height), m_Format(internalFormat), m_Quality {TextureQuality::Pixelated}
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, ToGLInternalFormat(m_Format), m_Size.x, m_Size.y);  
        ApplyQuality();      
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Update(const FilePath &filepath, uint32_t offsetX, uint32_t offsetY)
    {
        unsigned char *data = LoadTextureFromFile(filepath); 
        glBindTexture(GL_TEXTURE_2D, m_Id);
        glTextureSubImage2D(m_Id, 0, offsetX, offsetY, m_Size.x, m_Size.y, ToGLDataFormat(m_Format), GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    unsigned char* OpenGLTexture2D::LoadTextureFromFile(const FilePath &filepath)
    {
        int32_t NRChannels, x, y;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(filepath.GetRelativePath().c_str(), &x, &y, &NRChannels, 0);
        RE_CORE_ASSERT(data, "Fail to load image");

        m_Path = filepath;

        // RE_CORE_ASSERT((x <= m_Size.x && y <= m_Size.y), "Couldn't update texture: image size bigger then size of texture");
        m_Size.x = x;
        m_Size.y = y;

        if (NRChannels == 3)
            m_Format = TextureFormat::RGB8;
        else if (NRChannels == 4)
            m_Format = TextureFormat::RGBA8;

        return data;
    }

    unsigned char* OpenGLTexture2D::LoadTextureFromMemory(unsigned char *data, unsigned int size)
    {
        int32_t NRChannels, x, y;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* image = stbi_load_from_memory(data, size, &x, &y, &NRChannels, 0);
        RE_CORE_ASSERT(data, "Fail to load image");

        m_Size.x = x;
        m_Size.y = y;

        if (NRChannels == 3)
            m_Format = TextureFormat::RGB8;
        else if (NRChannels == 4)
            m_Format = TextureFormat::RGBA8;

        return image;
    }

    void OpenGLTexture2D::Bind(uint32_t unit) const 
    {
        glBindTextureUnit(unit, m_Id);
    }

    void OpenGLTexture2D::SetQuality(TextureQuality quality)
    {
        m_Quality = quality;
        ApplyQuality();
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size)
    {
		RE_CORE_ASSERT(size == m_Size.x * m_Size.y * GetPixelSize(m_Format), "Data must fill entire texture");

        glBindTexture(GL_TEXTURE_2D, m_Id);
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, ToGLDataFormat(m_Format), GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::ApplyQuality()
    {
        glBindTexture(GL_TEXTURE_2D, m_Id);
        switch (m_Quality) 
        {
            case TextureQuality::Pixelated:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                break;

            case TextureQuality::Smooth:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                break;

            default:
                RE_CORE_ASSERT(false, "Unknown texture quality");
                break;
        }
    }

    bool OpenGLTexture2D::operator==(const Texture2D& other) const
    {
        return this->m_Id == other.GetRendererID();
    }
}