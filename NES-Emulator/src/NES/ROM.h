#pragma once

#include <stdint.h>

#include "Peripheral.h"

class ROM : public Peripheral
{
public:
	ROM(uint16_t startAddress, uint8_t* data, unsigned int size);
	~ROM();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t data) override;
	virtual void Write(uint16_t address, uint8_t* data, unsigned int size) override;
private:
	uint8_t* m_ROM;
};