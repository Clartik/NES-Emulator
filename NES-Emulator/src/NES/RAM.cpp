#include "RAM.h"

RAM::RAM(uint16_t startAddress, unsigned int size)
	: Peripheral(startAddress, startAddress + size), m_Size(size)
{
	m_RAM = new uint8_t[size];
}

RAM::~RAM()
{
	delete[] m_RAM;
}

uint8_t& RAM::Read(uint16_t address)
{
	address -= m_StartAddress;
	return m_RAM[address];
}

void RAM::Write(uint16_t address, uint8_t data)
{
	address -= m_StartAddress;
	m_RAM[address] = data;
}

void RAM::Write(uint16_t address, uint8_t* data, unsigned int size)
{
	address -= m_StartAddress;

	for (int i = 0; i < size; i++)
		m_RAM[address + i] = *(data + i);
}
