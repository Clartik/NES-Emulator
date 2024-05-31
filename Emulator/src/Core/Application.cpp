#include "pch.h"
#include "Application.h"

#include "Core.h"

Application* Application::s_Instance = nullptr;

Application::Application(const WindowProps& props)
{
	s_Instance = this;

	m_Window = new Window(props);
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	m_NES = new NES;
}

Application::~Application()
{
	delete m_Window;
	delete m_NES;
}

void Application::Run()
{
	while (m_Running)
	{
		m_CurrentFrameTime = m_Window->GetTime();
		double deltaTime = m_CurrentFrameTime - m_LastFrameTime;

		/*std::thread gameThread(&NES::OnUpdate, m_NES, deltaTime);
		gameThread.join();*/

		m_Window->OnUpdate(deltaTime);
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
