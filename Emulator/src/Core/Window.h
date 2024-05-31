#pragma once

#include "pch.h"

static const unsigned int DEFAULT_WINDOW_WIDTH = 960;
static const unsigned int DEFAULT_WINDOW_HEIGHT = 540;

class Event;
struct GLFWwindow;

struct WindowProps
{
	std::string Title;
	unsigned int Width, Height;

	WindowProps(
		const std::string& title = "App",
		unsigned int width = DEFAULT_WINDOW_WIDTH,
		unsigned int height = DEFAULT_WINDOW_HEIGHT
	)
		: Title(title), Width(width), Height(height) { }
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event& e)>;
public:
	Window(const WindowProps& props);
	~Window();

	void OnUpdate(float deltaTime);

	double GetTime() const;

	inline unsigned int GetWidth() const { return m_Data.Width; }
	inline unsigned int GetHeight() const { return m_Data.Height; }

	inline void* GetNativeWindow() const { return m_Window; }

	inline bool IsVSync() const { return m_Data.VSync; }

	void SetVSync(bool enabled);
	inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
private:
	void SetGLFWCallbacks();
private:
	GLFWwindow* m_Window = nullptr;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync = true;

		EventCallbackFn EventCallback;
	};

	WindowData m_Data;
};

