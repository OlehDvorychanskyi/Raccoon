#include <Raccoon/Events/EventQueue.h>

namespace Raccoon
{
    void EventQueue::AddEvent(std::shared_ptr<Event> event)
    {
        if (m_Events.find(event) == m_Events.end())
        {
            m_Events.insert(std::move(event));
        }
    }

    std::shared_ptr<Event> EventQueue::GetFront()
    {
        if (!m_Events.empty())
        {
            auto front = std::move(*m_Events.begin());
            m_Events.erase(m_Events.begin());
            return front;
        }
        return {nullptr};
    }
}