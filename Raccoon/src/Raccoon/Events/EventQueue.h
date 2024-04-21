#pragma once 
#include <unordered_set>
#include <memory>
#include <Raccoon/Events/Event.h>

namespace Raccoon
{
    class EventQueue
    {
    public:
        void AddEvent(std::shared_ptr<Event> event);
        std::shared_ptr<Event> GetFront();
    private:
        std::unordered_set<std::shared_ptr<Event>> m_Events;
    };
}