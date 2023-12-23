#include <Raccoon/Renderer/Renderer2D.h>

#include <Raccoon/Renderer/VertexBuffer.h>
#include <Raccoon/Renderer/IndexBuffer.h>
#include <Raccoon/Renderer/VertexArray.h>

#include <Raccoon/Renderer/RendererCommand.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <vector>

namespace Raccoon
{
    struct ColoredRectangleVertex
    {
        glm::vec2 Position;
        glm::vec4 Color;    
    };

    struct TexturedRectangleVertex
    {
        glm::vec2 Position;
        glm::vec4 Color; 
        glm::vec2 TextureCoords;
        float TextureIndex;
    };

    struct ColoredRectangleData
    {
        uint32_t IndexCount = 0;
        uint32_t RectangleCount = 0;
        ColoredRectangleVertex *CurrentVertex = nullptr;
        ColoredRectangleVertex *BeginVertex = nullptr;

        std::shared_ptr<VertexBuffer> VertexBuffer;
        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<Shaders> Shaders;
    };
    static ColoredRectangleData s_ColoredRectangleData;

    struct TexturedRectangleData
    {
        uint32_t IndexCount = 0;
        uint32_t RectangleCount = 0;
        TexturedRectangleVertex *CurrentVertex = nullptr;
        TexturedRectangleVertex *BeginVertex = nullptr;

        std::shared_ptr<VertexBuffer> VertexBuffer;
        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<Shaders> Shaders;

        std::shared_ptr<Texture2D> DefaultTexture;
        std::vector<std::shared_ptr<Texture2D>> TextureUnits;
        uint32_t CurrentTextureUnit = 1; // 0 unit occupied by default texture 
    };
    static TexturedRectangleData s_TexturedRectangleData;

    struct RectangleData
    {
        glm::vec3 RectangleVertexPositions[4];    
        glm::vec2 RectangleTextureCoords[4];
    };
    static RectangleData s_RectangleData;

    enum class RendererObject2DType
    {
        None = 0,
        ColoredRectangle,
        TexturedRectangle
    };

    struct RendererData
    {
        static constexpr uint32_t MaxInstances = 20000;
        static constexpr uint32_t MaxVertices = MaxInstances * 4;
		static constexpr uint32_t MaxIndices = MaxInstances * 6;
        uint32_t MaxTextureUnits;

        glm::mat3 ViewProjectionMatrix;

        RendererObject2DType CurrentRendererObject = RendererObject2DType::None;
        Renderer2D::Stats Renderer2DStats;
    };
    static RendererData s_RendererData; 

    void Renderer2D::Init()
    {                          
    // ----------------------- RENDERER -------------------------------------------------------------------------------------------------
        s_RendererData.MaxTextureUnits = RendererCommand::GetMaxTextureUnits(); 
    // -----------------------------------------------------------------------------------------------------------------------------------

    // ----------------------- RECTANGLE -------------------------------------------------------------------------------------------------

        uint32_t *RectangleIndices = new uint32_t[RendererData::MaxIndices];
        
        for (uint32_t i = 0, offset = 0; i < RendererData::MaxIndices; i+=6, offset+=4)
        {                 
            RectangleIndices[i + 0] = offset + 0;
            RectangleIndices[i + 1] = offset + 1;
            RectangleIndices[i + 2] = offset + 2;

            RectangleIndices[i + 3] = offset + 2;
            RectangleIndices[i + 4] = offset + 3;
            RectangleIndices[i + 5] = offset + 0;
        }

        std::shared_ptr<IndexBuffer> RectangleIndexBuffer = IndexBuffer::Create(RectangleIndices, RendererData::MaxIndices);
        delete[] RectangleIndices;

        s_RectangleData.RectangleVertexPositions[0] = { -0.5f, -0.5f, 1.0f };
		s_RectangleData.RectangleVertexPositions[1] = {  0.5f, -0.5f, 1.0f };
		s_RectangleData.RectangleVertexPositions[2] = {  0.5f,  0.5f, 1.0f };
		s_RectangleData.RectangleVertexPositions[3] = { -0.5f,  0.5f, 1.0f };

        s_RectangleData.RectangleTextureCoords[0] = { 0.0f, 0.0f };
        s_RectangleData.RectangleTextureCoords[1] = { 1.0f, 0.0f };
        s_RectangleData.RectangleTextureCoords[2] = { 1.0f, 1.0f };
        s_RectangleData.RectangleTextureCoords[3] = { 0.0f, 1.0f };

    // -----------------------------------------------------------------------------------------------------------------------------------

    // ----------------------- COLORED RECTANGLE -----------------------------------------------------------------------------------------

        s_ColoredRectangleData.VertexBuffer = VertexBuffer::Create(s_RendererData.MaxVertices * sizeof(ColoredRectangleVertex));
        s_ColoredRectangleData.VertexBuffer->SetLayout({
            {ShaderDataType::Float2, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
        });
        s_ColoredRectangleData.BeginVertex = new ColoredRectangleVertex[RendererData::MaxVertices];
        
        s_ColoredRectangleData.VertexArray = VertexArray::Create();
        s_ColoredRectangleData.VertexArray->AddVertexBuffer(s_ColoredRectangleData.VertexBuffer);
        s_ColoredRectangleData.VertexArray->SetIndexBuffer(RectangleIndexBuffer);

        s_ColoredRectangleData.Shaders = Shaders::Create("assets/shaders/ColoredRectangle.vs", "assets/shaders/ColoredRectangle.fs");
    // ------------------------------------------------------------------------------------------------------------------------------------

    // ----------------------- TEXTURED RECTANGLE -----------------------------------------------------------------------------------------
        
        s_TexturedRectangleData.VertexBuffer = VertexBuffer::Create(s_RendererData.MaxVertices * sizeof(TexturedRectangleVertex));
        s_TexturedRectangleData.VertexBuffer->SetLayout({
            {ShaderDataType::Float2, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_TextureCoords"},
            {ShaderDataType::Float, "a_TextureIndex"}
        });
        s_TexturedRectangleData.BeginVertex = new TexturedRectangleVertex[RendererData::MaxVertices];

        s_TexturedRectangleData.VertexArray = VertexArray::Create();
        s_TexturedRectangleData.VertexArray->AddVertexBuffer(s_TexturedRectangleData.VertexBuffer);
        s_TexturedRectangleData.VertexArray->SetIndexBuffer(RectangleIndexBuffer); 

        s_TexturedRectangleData.Shaders = Shaders::Create("assets/shaders/TexturedRectangle.vs", "assets/shaders/TexturedRectangle.fs");
        
        s_TexturedRectangleData.TextureUnits.resize(s_RendererData.MaxTextureUnits);

        s_TexturedRectangleData.DefaultTexture = Texture2D::Create(1, 1);
        uint32_t data = 0xffffffff; // white texture
        s_TexturedRectangleData.DefaultTexture->SetData(&data, sizeof(uint32_t));

        s_TexturedRectangleData.TextureUnits[0] = s_TexturedRectangleData.DefaultTexture;

    // ------------------------------------------------------------------------------------------------------------------------------------        
    }

    void Renderer2D::Shutdown()
    {
        delete[] s_ColoredRectangleData.BeginVertex;
        delete[] s_TexturedRectangleData.BeginVertex;
    }

    void Renderer2D::Begin(Camera2D &camera, const glm::mat3 &transform)
    {
        camera.OnUpdate();
        s_RendererData.ViewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);

        // ----- TO DO: --------------------------------------
            // Send ViewProjectionMatrix to the shaders once per scene here
        // ---------------------------------------------------

        Renderer2D::BeginBatch();
    }

    void Renderer2D::Begin(EditorCamera &camera)
    {
        camera.OnUpdate();
        s_RendererData.ViewProjectionMatrix = camera.GetProjection() * camera.GetView();

        // ----- TO DO: --------------------------------------
            // Send ViewProjectionMatrix to the shaders once per scene here
        // ---------------------------------------------------

        Renderer2D::BeginBatch();
    }

    void Renderer2D::End()
    {
        Renderer2D::EndBatch();
    }

    void Renderer2D::BeginBatch()
    {
        Renderer2D::BeginColoredRectangle();
        Renderer2D::BeginTexturedRectangle();

        s_RendererData.CurrentRendererObject = RendererObject2DType::None;
    }

    void Renderer2D::BeginColoredRectangle()
    {
        s_ColoredRectangleData.IndexCount = 0;
        s_ColoredRectangleData.CurrentVertex = s_ColoredRectangleData.BeginVertex;
    }

    void Renderer2D::BeginTexturedRectangle()
    {
        s_TexturedRectangleData.IndexCount = 0;
        s_TexturedRectangleData.CurrentVertex = s_TexturedRectangleData.BeginVertex;
        s_TexturedRectangleData.CurrentTextureUnit = 1;
    }

    void Renderer2D::EndBatch()
    {
        Renderer2D::FlushColoredRectangle();
        Renderer2D::FlushTexturedRectangle();
    }

    void Renderer2D::Flush()
    {
        switch (s_RendererData.CurrentRendererObject)
        {
        case RendererObject2DType::ColoredRectangle:
            Renderer2D::NextBatchColoredRectangle();
            break;
        case RendererObject2DType::TexturedRectangle:
            Renderer2D::NextBatchTexturedRectangle();
            break;
        };
    }

    void Renderer2D::FlushColoredRectangle()
    {
        if (s_ColoredRectangleData.IndexCount > 0u)
        {
            uint32_t verticesNumber = s_ColoredRectangleData.CurrentVertex - s_ColoredRectangleData.BeginVertex; 
            uint32_t dataSize = verticesNumber * sizeof(ColoredRectangleVertex);

            s_ColoredRectangleData.VertexArray->Bind();
            s_ColoredRectangleData.VertexBuffer->SetData(s_ColoredRectangleData.BeginVertex, dataSize);

            s_ColoredRectangleData.Shaders->Bind();
            s_ColoredRectangleData.Shaders->SetMat3("u_ViewProjection", s_RendererData.ViewProjectionMatrix);
            RendererCommand::DrawIndexed(s_ColoredRectangleData.VertexArray, s_ColoredRectangleData.IndexCount);
            ++s_RendererData.Renderer2DStats.DrawCalls;
        }
    }

    void Renderer2D::FlushTexturedRectangle()
    {   
        if (s_TexturedRectangleData.IndexCount > 0u)
        {
            uint32_t verticesNumber = s_TexturedRectangleData.CurrentVertex - s_TexturedRectangleData.BeginVertex;
            uint32_t dataSize = verticesNumber * sizeof(TexturedRectangleVertex);

            s_TexturedRectangleData.VertexArray->Bind();
            s_TexturedRectangleData.VertexBuffer->SetData(s_TexturedRectangleData.BeginVertex, dataSize);

            for (uint32_t i = 0; i < s_TexturedRectangleData.CurrentTextureUnit; i++)
                s_TexturedRectangleData.TextureUnits[i]->Bind(i);

            s_TexturedRectangleData.Shaders->Bind();
            s_TexturedRectangleData.Shaders->SetMat3("u_ViewProjection", s_RendererData.ViewProjectionMatrix);
            RendererCommand::DrawIndexed(s_TexturedRectangleData.VertexArray, s_TexturedRectangleData.IndexCount);
            ++s_RendererData.Renderer2DStats.DrawCalls;
        }
    }

    void Renderer2D::NextBatchColoredRectangle()
    {
        Renderer2D::FlushColoredRectangle();
        Renderer2D::BeginColoredRectangle();
        s_RendererData.CurrentRendererObject = RendererObject2DType::None;
    }

    void Renderer2D::NextBatchTexturedRectangle()
    {
        Renderer2D::FlushTexturedRectangle();
        Renderer2D::BeginTexturedRectangle();
        s_RendererData.CurrentRendererObject = RendererObject2DType::None;
    }

    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {        
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, color);
    }

    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const glm::vec4 &color)
    {
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::rotate(glm::mat3(1.0f), glm::radians(rotationAngle)) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, color);
    }

    void Renderer2D::DrawRectangle(const glm::mat3 &transform, const glm::vec4 &color)
    {
        if (s_RendererData.CurrentRendererObject != RendererObject2DType::ColoredRectangle && s_RendererData.CurrentRendererObject != RendererObject2DType::None)
        {
            Renderer2D::Flush();
        }   
        s_RendererData.CurrentRendererObject = RendererObject2DType::ColoredRectangle;         

        if (s_ColoredRectangleData.IndexCount >= RendererData::MaxIndices)
        {
            Renderer2D::NextBatchColoredRectangle();
        }

        for (uint32_t i = 0; i < 4; ++i) // 4 because there is 4 vertices in Rectangle
		{
            s_ColoredRectangleData.CurrentVertex->Position = transform * s_RectangleData.RectangleVertexPositions[i];
            s_ColoredRectangleData.CurrentVertex->Color = color;
            ++s_ColoredRectangleData.CurrentVertex;
		}   
        s_ColoredRectangleData.IndexCount += 6;  
        ++s_ColoredRectangleData.RectangleCount; 
    }

    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color)
    {        
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, texture, color);
    }

    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color)
    {
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::rotate(glm::mat3(1.0f), glm::radians(rotationAngle)) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, texture, color);
    }

    void Renderer2D::DrawRectangle(const glm::mat3 &transform, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color)
    {
        Renderer2D::DrawRectangle(transform, texture, s_RectangleData.RectangleTextureCoords, color); 
    }

    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color)
    {
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, sprite, color);
    }
    
    void Renderer2D::DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color)
    {
        glm::mat3 transform = glm::translate(glm::mat3(1.0f), position) * glm::rotate(glm::mat3(1.0f), glm::radians(rotationAngle)) * glm::scale(glm::mat3(1.0f), size);
        Renderer2D::DrawRectangle(transform, sprite, color);
    }

    void Renderer2D::DrawRectangle(const glm::mat3 &transform, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color)
    {
        Renderer2D::DrawRectangle(transform, sprite->GetTexture(), sprite->GetTextureCoords(), color);
    }

    void Renderer2D::DrawRectangle(const glm::mat3 &transform, const std::shared_ptr<Texture2D> &texture, const glm::vec2* textureCoords, const glm::vec4 &color)
    {
        if (s_RendererData.CurrentRendererObject != RendererObject2DType::TexturedRectangle && s_RendererData.CurrentRendererObject != RendererObject2DType::None)
        {
            Renderer2D::Flush();
        }   
        s_RendererData.CurrentRendererObject = RendererObject2DType::TexturedRectangle;

        if (s_TexturedRectangleData.IndexCount >= RendererData::MaxIndices)
            Renderer2D::NextBatchTexturedRectangle();

        bool useDefaultTexture = false;
        if (texture == nullptr || texture->IsLoaded() == false)
        {
            useDefaultTexture = true;
        }

        uint32_t textureIndex = 0u;
        if (useDefaultTexture == false)
        {
            for (uint32_t i = 0; i < s_TexturedRectangleData.CurrentTextureUnit; i++)
            {
                if (*(s_TexturedRectangleData.TextureUnits[i]) == *texture)
                {
                    textureIndex = i;
                    break;
                }
            }

            if (textureIndex == 0u)
            {
                if (s_TexturedRectangleData.CurrentTextureUnit >= s_RendererData.MaxTextureUnits)
                    Renderer2D::NextBatchTexturedRectangle();

                textureIndex = s_TexturedRectangleData.CurrentTextureUnit;
                s_TexturedRectangleData.TextureUnits[s_TexturedRectangleData.CurrentTextureUnit] = texture;
                ++s_TexturedRectangleData.CurrentTextureUnit;
            }
        }

        for (uint32_t i = 0; i < 4; i++) // 4 because there is 4 vertices in Rectangle
		{
            s_TexturedRectangleData.CurrentVertex->Position = transform * s_RectangleData.RectangleVertexPositions[i];
            s_TexturedRectangleData.CurrentVertex->Color = color;
            s_TexturedRectangleData.CurrentVertex->TextureCoords = *(textureCoords + i);
            s_TexturedRectangleData.CurrentVertex->TextureIndex = (useDefaultTexture == true) ? 0.f : textureIndex;
            ++s_TexturedRectangleData.CurrentVertex;
		}   
        s_TexturedRectangleData.IndexCount += 6;  
        ++s_TexturedRectangleData.RectangleCount;
    }

    void Renderer2D::DrawParticles(const ParticleSystem2D &particles)
    {
        for (auto &particle : particles.GetParticles())
        {
            if (particle.Active == false)
                continue;

            Renderer2D::DrawRectangle(particle.Position, {particle.CurrentSize, particle.CurrentSize}, particle.CurrentColor);
        }
    }

    void Renderer2D::ResetStats()
    {
        s_RendererData.Renderer2DStats.DrawCalls = 0;
    }

    Renderer2D::Stats Renderer2D::GetStats()
    {
        return s_RendererData.Renderer2DStats;
    }
}