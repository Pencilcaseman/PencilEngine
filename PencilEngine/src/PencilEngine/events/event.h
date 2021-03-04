#pragma once

#include <pcpch.h>

#include <PencilEngine/core.h>

namespace pencil
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; } \
	                               EventType getEventType() const override { return getStaticType(); } \
	                               const char * getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class PENCIL_API Event
	{
		friend class EventDispatcher;
	public:
		bool handled = false;

		virtual EventType getEventType() const = 0;
		virtual const char *getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }
	};

	class EventDispatcher
	{
		template<typename t>
		using EventFn = std::function<bool(t &)>;
	public:
		EventDispatcher(Event &event) : m_event(event) {}

		template<typename t>
		bool dispatch(EventFn<t> func)
		{
			if (m_event.getEventType() == t::getStaticType())
			{
				m_event.handled = func(*(t *) &m_event);
				return true;
			}
			return false;
		}

	private:
		Event &m_event;
	};

	inline std::ostream &operator<<(std::ostream &os, const Event &e) { return os << e.toString(); }
}
