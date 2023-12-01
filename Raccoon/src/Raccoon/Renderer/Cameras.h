#pragma once
#include <Raccoon/Events/Event.h>
#include <glm/glm.hpp>

namespace Raccoon
{
    class Camera2D
    {
    public:
        Camera2D() = default;
        virtual ~Camera2D() = default;

        virtual void OnUpdate() = 0;

        const glm::mat3& GetProjection() { return m_Projection; }
    protected:
        glm::mat3 m_Projection = glm::mat3(1.f);
    };

    class OrthographicCamera : public Camera2D
    {
    public:
        OrthographicCamera();
        OrthographicCamera(float aspectRatio, float orthographicSize = 1.f);
        OrthographicCamera(uint32_t width, uint32_t height, float orthographicSize = 1.f);
        virtual ~OrthographicCamera() = default;

        virtual void OnUpdate() override;

        void SetAspectRatio(float ratio);
        void SetAspectRatio(uint32_t width, uint32_t height);
        float GetAspectRatio() const { return m_AspectRatio; }

        void SetOrthographicSize(float size);
        float GetOrthographicSize() const { return m_OrthographicSize; }
    private:
        void RecalculateProjection();
    private:
        float m_AspectRatio, m_OrthographicSize;
        bool m_RecalculateProjection = false;
    };
}