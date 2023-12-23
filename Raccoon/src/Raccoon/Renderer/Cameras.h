#pragma once
#include <Raccoon/Events/Event.h>
#include <Raccoon/Core/TimeStep.h>
#include <glm/glm.hpp>

namespace Raccoon
{
    class Camera2D
    {
    public:
        Camera2D() = default;
        virtual ~Camera2D() = default;

        virtual void OnUpdate() = 0;

        const glm::mat3& GetProjection() const { return m_Projection; }
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

    class EditorCamera : public Camera2D
    {
    public:
        EditorCamera();
        EditorCamera(float aspectRatio, float zoom = 1.f, bool fixedAspectRatio = true);
        EditorCamera(uint32_t width, uint32_t height, float zoom = 1.f, bool fixedAspectRatio = true);

        virtual void OnUpdate() override;
        void OnUpdateController(const TimeStep &ts, const glm::vec2 &viewportSize, const glm::vec2 &viewportPosition);
        void OnEvent(Event &event);

        const glm::mat3& GetView() const { return m_View; }

        void SetAspectRatio(float ratio);
        void SetAspectRatio(uint32_t width, uint32_t height);
        float GetAspectRatio() const { return m_AspectRatio; }

        void SetFixAspectRatio(bool value) { m_FixedAspectRatio = value; }
        
        const glm::vec2& GetPosition() const { return m_Position; }
    private:
        void RecalculateProjection();
        void RecalculateView();

        void AddPosition(const glm::vec2 &position);
        void AddPositionX(float x);
        void AddPositionY(float y);
        void SetPosition(const glm::vec2 &position);

        void AddZoom(float zoom);
        void SetZoom(float zoom);
    private:
        glm::mat3 m_View = glm::mat3(1.f);
        glm::vec2 m_Position = glm::vec2(0.f, 0.f), m_CursorPosition = glm::vec2(0.f, 0.f);

        bool m_RecalculateProjection = false, m_RecalculateView = false;
        float m_AspectRatio, m_Zoom = 1.f;
        bool m_FixedAspectRatio = true;

        float m_MoveSpeed = 0.003f, m_ZoomSpeed = 1.f;
    };
}