#pragma once

#include <stdint.h>

// Peripheral is a generic class that the Bus can use to communicate
class Peripheral
{
public:
	bool IsInRange(uint16_t address) const
	{
		if (address >= m_StartAddress && address <= m_EndAddress)
			return true;

		return false;
	}

	virtual uint8_t& Read(uint16_t address) = 0;
	virtual void Write(uint16_t address, uint8_t value) = 0;
	virtual void Write(uint16_t address, uint8_t* data, unsigned int size) = 0;
protected:
	Peripheral(uint16_t startAddress, uint16_t endAddress)
		: m_StartAddress(startAddress), m_EndAddress(endAddress) {}
protected:
	// Addresses Used By Bus
	uint16_t m_StartAddress, m_EndAddress;
};