#pragma once

#include "Base/Peripheral.h"

const unsigned int NAMETABLE_SIZE = 960;
const unsigned int ATTRIBUTE_SIZE = 64;

const unsigned int NAMETABLE_TOTAL_SIZE = NAMETABLE_SIZE + ATTRIBUTE_SIZE;

class Nametable : public Peripheral
{
public:
	Nametable(uint16_t startAddress);
	~Nametable();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t value) override;
private:
	uint8_t& GetByte(uint16_t address);
private:
	uint8_t m_NameTable[NAMETABLE_SIZE];
	uint8_t m_AttributeTable[ATTRIBUTE_SIZE];
};