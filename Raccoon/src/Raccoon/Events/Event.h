#pragma once 
#include <cstdint>

namespace Raccoon
{
    enum class EventType
    {   
        None = 0,
        WindowResize, WindowClose,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory : uint32_t
    {
        None = 0,
        WindowEvent = BIT(0),
        KeyEvent = BIT(1),
        MouseEvent = BIT(2)
    };

    #define DECLARE_EVENT_TYPE(type) static EventType GetStaticEventType() { return type; } virtual EventType GetEventType() const override { return type; }
    #define DECLARE_EVENT_CATEGORY(category) virtual uint32_t GetEventCategory() const override { return category; } virtual bool BelongToCategory(EventCategory Category) const override { return category & Category; } 

    class Event
    {
    public:
        virtual EventType GetEventType() const = 0;
        virtual uint32_t GetEventCategory() const = 0;
        virtual bool BelongToCategory(EventCategory category) const = 0;
        virtual ~Event() = default; 
    public:
        bool Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event &event)
            : m_Event(event) {}

        template <typename DynamicEventType, typename CallbackType>
        void Dispatch(const CallbackType &callback)
        {
            if (m_Event.GetEventType() == DynamicEventType::GetStaticEventType())
            {
                callback(static_cast<DynamicEventType&>(m_Event));
            }
        }
    private:
        Event &m_Event;
    };
}