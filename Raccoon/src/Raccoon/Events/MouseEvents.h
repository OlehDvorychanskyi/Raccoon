#pragma once 
#include <Raccoon/Events/Event.h>
#include <Raccoon/Core/MouseCodes.h>

namespace Raccoon
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_X{x}, m_Y{y} {}

        float GetX() const { return m_X; }
        float GetY() const { return m_Y; }

        DECLARE_EVENT_TYPE(EventType::MouseMoved);
        DECLARE_EVENT_CATEGORY(EventCategory::MouseEvent);
    private:
        float m_X, m_Y;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float XOffset, float YOffset)
            : m_XOffset{XOffset}, m_YOffset{YOffset} { } 

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        DECLARE_EVENT_TYPE(EventType::MouseScrolled);
        DECLARE_EVENT_CATEGORY(EventCategory::MouseEvent);
    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseCode() const { return m_MouseCode; }

        DECLARE_EVENT_CATEGORY(EventCategory::MouseEvent);
    protected:
        MouseButtonEvent(MouseCode mousecode)
            : m_MouseCode{mousecode} { }
    protected:
        MouseCode m_MouseCode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode mousecode)
            : MouseButtonEvent(mousecode) { }

        DECLARE_EVENT_TYPE(EventType::MouseButtonPressed);
        DECLARE_EVENT_CATEGORY(EventCategory::MouseEvent);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode mousecode)
            : MouseButtonEvent(mousecode) { }   

        DECLARE_EVENT_TYPE(EventType::MouseButtonReleased);
        DECLARE_EVENT_CATEGORY(EventCategory::MouseEvent);
    };
}