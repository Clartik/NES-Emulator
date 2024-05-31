#pragma once

#include "pch.h"

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

class Event
{
public:
	virtual	EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }
public:
	bool Handled = false;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

class EventDispatcher
{
private:
	template <typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_Event(event) { }

	template <typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType() != T::GetStaticType())
			return false;

		m_Event.Handled = func(*(T*)&m_Event);
		return true;
	}
private:
	Event& m_Event;
};