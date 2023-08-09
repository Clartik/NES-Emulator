#pragma once

#include "NES/CPU.h"
#include "NES/Bus.h"
#include "NES/RAM.h"

class Emulator
{
public:
	Emulator();
	~Emulator();

	void Run();
private:
	bool m_Running = true;

	CPU* m_CPU;
	Bus m_Bus;
	RAM m_RAM;
};