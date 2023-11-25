#pragma once 
#include <glm/glm.hpp>
#include <Raccoon/Core/TimeStep.h>

#include <vector>

namespace Raccoon
{
    struct Particle2D
    {
        glm::vec2 Position, Velocity, VelocityRangeX, VelocityRangeY;
        glm::vec4 BeginColor, EndColor;
        float BeginSize, EndSize;
        float LifeTime = 1.f;
    };

    struct ColoredParticle2D
    {

    };

    struct TexturedParticle2D
    {

    };

    class ParticleSystem2D
    {
    public:
        ParticleSystem2D();

        void OnUpdate(const TimeStep &timestep);
        void Emit(const Particle2D &particle); 
    private:
        struct ParticleData
        {
            glm::vec2 Position, Velocity;
            glm::vec4 BeginColor, EndColor, CurrentColor;
            float BeginSize, EndSize, CurrentSize;
            float LifeTime, LifeRemaining;
            bool Active;
        };

        const std::vector<ParticleData>& GetParticles() const { return m_Particles; }

        std::vector<ParticleData> m_Particles; 
        int32_t m_ParticleIndex = 999;

        friend class Renderer2D;
    };
}