#include "Emulator.h"

#include <iostream>
#include <thread>

Emulator::Emulator()
{
	m_NES = new NES;
}

Emulator::~Emulator()
{
	delete m_NES;
}

void Emulator::Run()
{
	while (m_Running)
	{
		std::thread gameThread(&NES::OnUpdate, m_NES, 0);
		gameThread.join();
	}
}