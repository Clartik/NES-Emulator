#pragma once

#include "NES/CPU.h"
#include "NES/Bus.h"
#include "NES/RAM.h"

const double CPU_CLOCK_SPEED_HZ = 1790000.0;
const double CPU_TIME_PER_INSTRUCTION_SEC = 1.0 / CPU_CLOCK_SPEED_HZ;

class NES
{
public:
	NES();
	~NES();

	void OnUpdate(double deltaTime);
private:
	CPU* m_CPU;
	RAM m_RAM;
	Bus m_Bus;
};