#pragma once 
#include <vector>
#include <cstdint>

#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    enum class ShaderDataType
    {
        None = 0,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		RE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

    struct BufferLayoutElement
    {
        ShaderDataType Type;
        std::string Name;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;
    
        BufferLayoutElement(ShaderDataType type, const std::string &name, bool normalized = false)
            : Type{type}, Name{name}, Size(ShaderDataTypeSize(type)), Offset{0}, Normalized{normalized} { }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
                case ShaderDataType::Float:    return 1;
                case ShaderDataType::Float2:   return 2;
                case ShaderDataType::Float3:   return 3;
                case ShaderDataType::Float4:   return 4;
                case ShaderDataType::Mat3:     return 3 * 3;
                case ShaderDataType::Mat4:     return 4 * 4;
                case ShaderDataType::Int:      return 1;
                case ShaderDataType::Int2:     return 2;
                case ShaderDataType::Int3:     return 3;
                case ShaderDataType::Int4:     return 4;
                case ShaderDataType::Bool:     return 1;
            }

            RE_CORE_ASSERT(false, "Unknown ShaderDataType");
		    return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferLayoutElement> elements)
            : m_LayoutElements{elements}, m_Stride{0}
        {
            CalculateOffsetAndStride();
        }

        uint32_t GetStride() const { return m_Stride; }
        const std::vector<BufferLayoutElement>& GetElements() const { return m_LayoutElements; }

        std::vector<BufferLayoutElement>::iterator begin() { return m_LayoutElements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return m_LayoutElements.end(); }

        std::vector<BufferLayoutElement>::const_iterator begin() const { return m_LayoutElements.begin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_LayoutElements.end(); }
    private:
        void CalculateOffsetAndStride()
        {
            m_Stride = 0;
            for (auto &element : m_LayoutElements)
            {
                element.Offset = m_Stride;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferLayoutElement> m_LayoutElements;
        uint32_t m_Stride;
    };
}