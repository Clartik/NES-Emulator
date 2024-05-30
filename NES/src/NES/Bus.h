#pragma once

#include "Base/Peripheral.h"

class Bus
{
public:
	Bus();
	~Bus();

	uint8_t* Read(uint16_t address);
	void Write(uint16_t address, uint8_t value);

	void Add(Peripheral* peripheral);
	void Remove(Peripheral* peripheral);
private:
	Peripheral* Find(uint16_t address);
private:
	std::vector<Peripheral*> m_Peripherals;
};