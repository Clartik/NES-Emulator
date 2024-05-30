#pragma once

#include "CPU.h"
#include "PPU/PPU.h"

const double CPU_CLOCK_SPEED_HZ = 1790000.0;
const double CPU_TIME_PER_INSTRUCTION_SEC = 1.0 / CPU_CLOCK_SPEED_HZ;
const unsigned int MICROSECONDS_CONVERSION = 1000000;

const double PPU_CLOCK_SPEED_HZ = CPU_CLOCK_SPEED_HZ * 3;
const double PPU_TIME_PER_INSTRUCTION_SEC = 1.0 / CPU_CLOCK_SPEED_HZ;

class NES
{
public:
	NES();
	~NES();

	void OnUpdate(double deltaTime);

	void LoadROM(const std::string& filepath);
private:
	CPU* m_CPU;
	PPU* m_PPU;
};