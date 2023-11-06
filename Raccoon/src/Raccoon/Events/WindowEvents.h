#pragma once 
#include <Raccoon/Events/Event.h>

namespace Raccoon
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        DECLARE_EVENT_TYPE(EventType::WindowClose);
        DECLARE_EVENT_CATEGORY(EventCategory::WindowEvent);
        OVERRIDE_EVENT_DEBUG("WindowCloseEvent");
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

        DECLARE_EVENT_TYPE(EventType::WindowResize);
        DECLARE_EVENT_CATEGORY(EventCategory::WindowEvent);
        OVERRIDE_EVENT_DEBUG("WindowResizeEvent");
    private:
        uint32_t m_Width, m_Height;
    };
}