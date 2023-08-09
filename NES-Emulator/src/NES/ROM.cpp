#include "ROM.h"

#include <cstring>
#include <iostream>

ROM::ROM(uint16_t startAddress, uint8_t* data, unsigned int size)
	: Peripheral(startAddress, startAddress + 0xBFDF)
{
	m_ROM = new uint8_t[0xBFDF];
	memcpy(m_ROM, data, sizeof(uint8_t) * size);
}

ROM::~ROM()
{
	delete[] m_ROM;
}

uint8_t& ROM::Read(uint16_t address)
{
	address -= m_StartAddress;
	return m_ROM[address];
}

void ROM::Write(uint16_t address, uint8_t data)
{
	std::cout << "Writing is not permitted!" << std::endl;
}

void ROM::Write(uint16_t address, uint8_t* data, unsigned int size)
{
	std::cout << "Writing is not permitted!" << std::endl;
}
