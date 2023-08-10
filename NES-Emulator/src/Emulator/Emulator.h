#pragma once

#include "NES/NES.h"

class Emulator
{
public:
	Emulator();
	~Emulator();

	void Run();
private:
	bool m_Running = true;

	NES* m_NES;
};