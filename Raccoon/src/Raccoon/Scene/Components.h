#pragma once 
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <string>

#include <Raccoon/Renderer/Texture2D.h>
#include <Raccoon/Renderer/Cameras.h>

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

    struct Transform2DComponent
    {
        glm::vec2 Translation = {0.0f, 0.0f};
        float Rotation = 0.f;
        glm::vec2 Scale = {1.f, 1.f};

        Transform2DComponent() = default;
        Transform2DComponent(const glm::vec2 &translation)
            : Translation{translation} {}

        glm::mat3 GetTransform() const
		{
			return glm::translate(glm::mat3(1.0f), glm::vec2(Translation)) * glm::rotate(glm::mat3(1.f), glm::radians(Rotation)) * glm::scale(glm::mat3(1.0f), glm::vec2(Scale));
		}
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
        
        SpriteRendererComponent() = default;
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
        bool ActiveCamera = true;

        OrthographicCameraComponent() = default;
        OrthographicCameraComponent(float aspectRatio, float orthographicSize = 1.f)
            : Camera(aspectRatio, orthographicSize) {}
        OrthographicCameraComponent(uint32_t width, uint32_t height, float orthographicSize = 1.f)
            : Camera(width, height, orthographicSize) {}
    };
}