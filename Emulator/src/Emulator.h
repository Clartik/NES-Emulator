#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "NES/NES.h"

class Emulator
{
public:
	Emulator();
	~Emulator();

	void Run();
private:
	bool m_Running = true;

	double m_LastFrameTime = 0, m_CurrentFrameTime = 0;

	GLFWwindow* m_Window = nullptr;

	NES* m_NES = nullptr;
};