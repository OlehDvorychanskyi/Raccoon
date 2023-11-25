#pragma once 
#include <Raccoon/Renderer/ShaderLibrary.h>
#include <Raccoon/Renderer/OrthographicCamera.h>
#include <Raccoon/Renderer/Texture2D.h>
#include <Raccoon/Renderer/Sprite.h>
#include <Raccoon/Renderer/ParticleSystem.h>

#include <glm/glm.hpp>
#include <memory.h>

namespace Raccoon
{   
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(OrthographicCamera &camera);
        static void End();
        
        // ----- TO DO: --------------------------------------
            // DONE: Draw Rectangle with texture 
            // Draw Rectangle with glm::mat4 transform
            // Draw Rectangle with position and size in pixels  
            // Draw Rectangle with rotation
            // Change glm::vec4 color to int color or to Raccoon::Color
        // ---------------------------------------------------

        static void DrawRectangle(const glm::mat4 &transform, const glm::vec4 &color);      
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const glm::vec4 &color);

        static void DrawRectangle(const glm::mat4 &transform, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const std::shared_ptr<Sprite> &sprite, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});

        static void DrawRectangle(const glm::mat4 &transform, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});
        static void DrawRectangle(const glm::vec2 &position, const glm::vec2 &size, float rotationAngle, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color = {1.f, 1.f, 1.f, 1.f});

        static void DrawParticles(const ParticleSystem2D &particles);

    private:    
        static void DrawRectangle(const glm::mat4 &transform, const std::shared_ptr<Texture2D> &texture, const glm::vec2* textureCoords, const glm::vec4 &color);

        // ----- TO DO: --------------------------------------
            // Draw Circle 
            // Draw Line
            // Draw Text
            // Draw User defined primitives 
        // ---------------------------------------------------
    private: 
        // ----- TO DO: --------------------------------------
            // Send color as a uniform
            // Send texture index as a uniform
        // ---------------------------------------------------
        static void BeginBatch();
        static void NextBatch();
        static void EndBatch();

        // ----- TO DO: --------------------------------------
            // Add some stats(draw calls, memory usage...)
        // ---------------------------------------------------
    };   
}