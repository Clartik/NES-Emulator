#pragma once

#include "Window.h"

#include "Events/ApplicationEvent.h"

#include "NES/NES.h"

class Application
{
public:
	Application(const WindowProps& props);
	~Application();

	void Run();

	inline Window& GetWindow() const { return *m_Window; }

	inline static Application& Get() { return *s_Instance; }
private:
	void OnEvent(Event& e);
	bool OnWindowClose(WindowCloseEvent& e);
private:
	bool m_Running = true;

	double m_LastFrameTime = 0, m_CurrentFrameTime = 0;

	Window* m_Window = nullptr;

	NES* m_NES = nullptr;
private:
	static Application* s_Instance;
};