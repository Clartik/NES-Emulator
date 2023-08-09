#pragma once

#include <vector>
#include <algorithm>

#include "Peripheral.h"

class Bus
{
public:
	Bus();
	~Bus();

	uint8_t* Read(uint16_t address);
	void Write(uint16_t address, uint8_t value);
	void Write(uint16_t address, uint8_t* value, unsigned int size);

	void Add(Peripheral* peripheral);
	void Remove(Peripheral* peripheral);
private:
	Peripheral* Find(uint16_t address);
private:
	std::vector<Peripheral*> m_Peripherals;
};