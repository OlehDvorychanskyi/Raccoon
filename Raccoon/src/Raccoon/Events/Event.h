#pragma once
#include <cstdint>
#include <memory>

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
 
    #ifdef RE_DEBUG
        #define DECLARE_EVENT_DEBUG() virtual const char* GetEventName() const = 0; virtual std::string ToString() const = 0;
        #define OVERRIDE_EVENT_DEBUG(name) virtual const char* GetEventName() const override { return name; }  virtual std::string ToString() const override { return name; }
    #else
        #define DECLARE_EVENT_DEBUG()
        #define OVERRIDE_EVENT_DEBUG(name)
    #endif

    class Event
    {
        friend inline bool operator==(const std::shared_ptr<Event> &a, const std::shared_ptr<Event> &b) { return a->GetEventType() == b->GetEventType(); } 
    public:
        virtual EventType GetEventType() const = 0;
        virtual uint32_t GetEventCategory() const = 0;
        virtual bool BelongToCategory(EventCategory category) const = 0;
        virtual ~Event() = default;

        DECLARE_EVENT_DEBUG()
    public:
        bool Handled = false;
    };

    class EventDispacher
    {
    public:
        EventDispacher(Event &event)
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