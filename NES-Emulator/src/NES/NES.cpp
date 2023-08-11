#include "NES.h"

#include <chrono>
#include <thread>
#include <iostream>

#include "NES/Memory.h"

NES::NES()
{
	m_CPU = new CPU;
	m_PPU = new PPU(PPU_REGISTERS_START_ADDRESS);

	Bus* cpuBus = m_CPU->GetBus();
	Bus* ppuBus = m_PPU->GetBus();

	cpuBus->Add(new Memory(RAM_START_ADDRESS, RAM_SIZE));
	cpuBus->Add(m_PPU);

	ppuBus->Add(new Memory(VRAM_START_ADDRESS, VRAM_SIZE));

	m_CPU->Reset();
}

NES::~NES()
{
	delete m_CPU;
}

void NES::OnUpdate(double deltaTime)
{
	std::thread cpuThread(&CPU::Cycle, m_CPU, (CPU_TIME_PER_INSTRUCTION_SEC * MICROSECONDS_CONVERSION) - deltaTime);

	for (int i = 0; i < 3; i++)
	{
		std::thread ppuThread(&PPU::Cycle, m_PPU, (PPU_TIME_PER_INSTRUCTION_SEC * MICROSECONDS_CONVERSION) - deltaTime);
		ppuThread.join();
	}

	cpuThread.join();
}
