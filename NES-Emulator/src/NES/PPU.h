#pragma once

#include "Peripheral.h"
#include "Bus.h"

class PPU : public Peripheral
{
public:
	PPU(uint16_t startAddress, uint8_t size, Bus* bus);
	~PPU();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t value) override;
	virtual void Write(uint16_t address, uint8_t* data, unsigned int size) override;
private:
	void Init();
private:
	Bus* m_Bus;		// Personal Bus
};