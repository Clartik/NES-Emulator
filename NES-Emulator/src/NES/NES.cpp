#include "NES.h"

#include <chrono>
#include <thread>
#include <iostream>

NES::NES()
	: m_RAM(MEMORY_START_ADDRESS, MEMORY_SIZE)
{
	m_Bus.Add(&m_RAM);

	m_CPU = new CPU(&m_Bus);
	m_CPU->Reset();
}

NES::~NES()
{
	delete m_CPU;
}

void NES::OnUpdate(double deltaTime)
{
	m_CPU->Cycle();

	std::this_thread::sleep_for(std::chrono::microseconds((int)(CPU_TIME_PER_INSTRUCTION_SEC * 1000000)));
}
