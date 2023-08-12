#include "Emulator.h"

#include <iostream>
#include <thread>

Emulator::Emulator()
{
	if (!glfwInit())
	{
		std::cout << "Couldn't Initalize GLFW" << std::endl;
		return;
	}

	m_Window = glfwCreateWindow(960, 540, "Hello", 0, 0);
	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Window Didn't Initalize" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);	// Vsync

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Couldn't Initalize GLAD" << std::endl;
		return;
	}

	m_NES = new NES;
}

Emulator::~Emulator()
{
	glfwDestroyWindow(m_Window);
	delete m_NES;
}

void Emulator::Run()
{
	while (m_Running)
	{
		m_CurrentFrameTime = glfwGetTime();
		double delta = m_CurrentFrameTime - m_LastFrameTime;

		std::thread gameThread(&NES::OnUpdate, m_NES, delta);
		gameThread.join();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}