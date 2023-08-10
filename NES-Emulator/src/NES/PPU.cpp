#include "PPU.h"

// StartAddress + size - 1 because startAddress is the start and size - 1 is the end
PPU::PPU(uint16_t startAddress, uint8_t size, Bus* bus)
	: Peripheral(startAddress, startAddress + size - 1), m_Bus(bus)
{
}

PPU::~PPU()
{
}

uint8_t& PPU::Read(uint16_t address)
{
	return *m_Bus->Read(address);
}

void PPU::Write(uint16_t address, uint8_t value)
{
	m_Bus->Write(address, value);
}

void PPU::Write(uint16_t address, uint8_t* data, unsigned int size)
{
	m_Bus->Write(address, data, size);
}

void PPU::Init()
{
}
