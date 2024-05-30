#pragma once

#include "Base/Peripheral.h"

class Memory : public Peripheral
{
public:
	Memory(uint16_t startAddress, unsigned int size);
	~Memory();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t data) override;
private:
	uint8_t* m_RAM;
	unsigned int m_Size;
};