#pragma once 
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <string>
#include <vector>
#include <memory>

#include <Raccoon/Renderer/Texture2D.h>
#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Core/TimeStep.h>
#include <Raccoon/Scene/ScriptableEntity.h>

namespace Raccoon
{
    // struct TransformComponent3D
    // {
    //     glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
	// 	glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
	// 	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

    //     TransformComponent() = default;
    //     TransformComponent(const glm::vec3 &translation);
    //         : Translation{translation} {}

    //     glm::mat4 GetTransform() const
	// 	{
	// 		glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

	// 		return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
	// 	}
    // };

    class Transform2DComponent
    {
    public:
        Transform2DComponent() = default;
        Transform2DComponent(const glm::vec2 &position)
            : Position{position} {}

        void OnUpdate() 
        {
            m_Transform = glm::translate(glm::mat3(1.f), glm::vec2(Position)) * glm::rotate(glm::mat3(1.f), glm::radians(RotationAngle)) * glm::scale(glm::mat3(1.f), glm::vec2(Scale));
        }

        glm::mat3 GetTransform() const { return m_Transform; }
        glm::mat3& GetTransform() { return m_Transform; }
    public:
        glm::vec2 Position = {0.f, 0.f};
        float RotationAngle = 0.f;
        glm::vec2 Scale = {1.f, 1.f};
    private:
        glm::mat3 m_Transform;
    };

    struct NameComponent
    {
        std::string Name;

        NameComponent() = default;
        NameComponent(const std::string &name) 
            : Name{name} {}
    };

    struct ZComponent
    {
        uint32_t ZIndex = 0;

        ZComponent() = default;
        ZComponent(uint32_t zindex)
            : ZIndex{zindex} {}
    };

    struct SpriteRendererComponent
    {
        std::shared_ptr<Texture2D> Texture;
        glm::vec4 Color = {1.f, 1.f, 1.f, 1.f};
        // TODO: tilling factor 
        
        SpriteRendererComponent()
        {
            Texture = Texture2D::Create(1, 1);
        }
        SpriteRendererComponent(const std::shared_ptr<Texture2D> &texture)
            : Texture{texture} {}
    };

    struct ColorRendererComponent
    {
        glm::vec4 Color = {1.f, 1.f, 1.f, 1.f};

        ColorRendererComponent() = default;
        ColorRendererComponent(const glm::vec4 &color)
            : Color{color} {}
    };

    struct OrthographicCameraComponent
    {
        OrthographicCamera Camera;
        bool FixedAspectRatio = true;

        OrthographicCameraComponent() = default;
        OrthographicCameraComponent(float aspectRatio, float orthographicSize = 1.f)
            : Camera(aspectRatio, orthographicSize) {}
        OrthographicCameraComponent(uint32_t width, uint32_t height, float orthographicSize = 1.f)
            : Camera(width, height, orthographicSize) {}
    };

    class EntityControllerComponent // Trasform2DControllerComponent
    {
    public:
        EntityControllerComponent() = default;
        EntityControllerComponent(Transform2DComponent &transform, bool enableRotation = false);

        void OnUpdate(const TimeStep &timestep);

        void SetTransformComponent(Transform2DComponent &transform) { m_Transform = &transform; }

        void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

        float GetMovementSpeed() const { return m_MoveSpeed; }
        float GetRotationSpeed() const { return m_RotationSpeed; }

        void EnableRotation() { m_EnableRotation = true; }
        void DisableRotation() { m_EnableRotation = false; }
        void SetEnableRotation(bool value) { m_EnableRotation = value; } 
        bool IsRotationEnabled() const { return m_EnableRotation; }
    private:
        Transform2DComponent* m_Transform;

        float m_MoveSpeed = 5.f, m_RotationSpeed = 40.f;
        bool m_EnableRotation;
    };

    struct NativeScriptComponent
    {
        ScriptableEntity *Script = nullptr;

        ScriptableEntity*(*CreateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

        template<typename T> 
        void Bind()
        {
            CreateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Script; nsc->Script = nullptr; };
        }
    };

    class ParentEntityComponent
    {
    public: 
        void AddChild(const std::shared_ptr<Entity> &child);
    private:
        std::vector<std::shared_ptr<Entity>> m_Childrens;
    };
}