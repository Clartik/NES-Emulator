#pragma once

#include "Peripheral.h"

class RAM : public Peripheral
{
public:
	RAM(uint16_t startAddress, unsigned int size);
	~RAM();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t data) override;
	virtual void Write(uint16_t address, uint8_t* data, unsigned int size) override;
private:
	uint8_t* m_RAM;
	unsigned int m_Size;
};