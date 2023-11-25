#include <Raccoon/Renderer/ParticleSystem.h>
#include <Raccoon/Math/Random.h>

#include <glm/gtx/compatibility.hpp>

namespace Raccoon
{
    ParticleSystem2D::ParticleSystem2D()    
    {
        m_Particles.resize(1000);
    }

    void ParticleSystem2D::OnUpdate(const TimeStep &timestep)
    {
        for (auto &particle : m_Particles)
        {
            if (particle.Active == false)
                continue;

            if (particle.LifeRemaining <= 0.0f)
		    {
                particle.Active = false;
                continue;
            }   
            
            particle.LifeRemaining -= timestep.GetDeltaTime();
            particle.Position += particle.Velocity * timestep.GetDeltaTime(); 

            float life = particle.LifeRemaining / particle.LifeTime;
            particle.CurrentColor = glm::lerp(particle.EndColor, particle.BeginColor, life);
            particle.CurrentSize = glm::lerp(particle.EndSize, particle.BeginSize, life);
        }
    }

    void ParticleSystem2D::Emit(const Particle2D &particle)
    {
        ParticleData &particleData = m_Particles[m_ParticleIndex];
        particleData.Active = true;
        particleData.Position = particle.Position;

        particleData.Velocity = particle.Velocity;
        particleData.Velocity.x += Raccoon::Random::Float(particle.VelocityRangeX.x, particle.VelocityRangeX.y);
        particleData.Velocity.y += Raccoon::Random::Float(particle.VelocityRangeY.x, particle.VelocityRangeY.y);

        particleData.BeginColor = particle.BeginColor;
	    particleData.EndColor = particle.EndColor;
        particleData.CurrentColor = particle.BeginColor;

        particleData.BeginSize = particle.BeginSize;
        particleData.EndSize = particle.EndSize;
        particleData.CurrentSize = particle.BeginSize;

        particleData.LifeTime = particle.LifeTime;
        particleData.LifeRemaining = particle.LifeTime;

        m_ParticleIndex = --m_ParticleIndex % m_Particles.size();
    }    
}