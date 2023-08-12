#include "Memory.h"

Memory::Memory(uint16_t startAddress, unsigned int size)
	: Peripheral(startAddress, startAddress + size), m_Size(size)
{
	m_RAM = new uint8_t[size];
}

Memory::~Memory()
{
	delete[] m_RAM;
}

uint8_t& Memory::Read(uint16_t address)
{
	address -= m_StartAddress;
	return m_RAM[address];
}

void Memory::Write(uint16_t address, uint8_t data)
{
	address -= m_StartAddress;
	m_RAM[address] = data;
}
