#pragma once 
#include <Raccoon/Events/Event.h>
#include <Raccoon/Core/KeyCodes.h>

namespace Raccoon
{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        DECLARE_EVENT_CATEGORY(EventCategory::KeyEvent);
    protected:
        KeyEvent(KeyCode keycode)
            : m_KeyCode{keycode} { }
    protected:
        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keyCode, bool repeat = false)
            : KeyEvent(keyCode), m_Repeat{repeat} { } 

        bool IsRepeat() const { return m_Repeat; }

        DECLARE_EVENT_TYPE(EventType::KeyPressed);
        DECLARE_EVENT_CATEGORY(EventCategory::KeyEvent);            
    private:
        bool m_Repeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode keycode)
            : KeyEvent(keycode) { }

        DECLARE_EVENT_TYPE(EventType::KeyReleased);
        DECLARE_EVENT_CATEGORY(EventCategory::KeyEvent);
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(KeyCode keycode)
            : KeyEvent(keycode) { }

        DECLARE_EVENT_TYPE(EventType::KeyTyped);
        DECLARE_EVENT_CATEGORY(EventCategory::KeyEvent);
    };
}