#pragma once

#include <stdint.h>

const unsigned int MEMORY_SIZE = 2048;

class CPU6502
{
public:
	CPU6502();
	~CPU6502();
private:
	// Acuumlator, X-Index, Y-Index, Flag, Stack Pointers
	uint8_t m_A, m_X, m_Y, m_F, m_S;
	uint16_t m_PC;

	uint8_t m_RAM[MEMORY_SIZE];
};