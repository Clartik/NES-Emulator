#include "Bus.h"

#include <iostream>

Bus::Bus()
{
}

Bus::~Bus()
{
	for (auto* i : m_Peripherals)
		delete i;
}

uint8_t* Bus::Read(uint16_t address)
{
	Peripheral* peripheral = Find(address);

	if (!peripheral)
		return nullptr;

	return &peripheral->Read(address);
}

void Bus::Write(uint16_t address, uint8_t value)
{
	Peripheral* peripheral = Find(address);

	if (!peripheral)
		return;

	peripheral->Write(address, value);
}

void Bus::Add(Peripheral* peripheral)
{
	m_Peripherals.push_back(peripheral);
}

void Bus::Remove(Peripheral* peripheral)
{
	auto it = std::find(m_Peripherals.begin(), m_Peripherals.end(), peripheral);

	if (it == m_Peripherals.end())
	{
		std::cout << "Could Not Find Peripheral '" << peripheral << "' in Bus" << std::endl;
		return;
	}

	m_Peripherals.erase(it);
}

Peripheral* Bus::Find(uint16_t address)
{
	auto it = std::find_if(m_Peripherals.begin(), m_Peripherals.end(), [&address](const Peripheral* peripheral)
	{
		if (peripheral->IsInRange(address))
			return peripheral;
	});

	if (it != m_Peripherals.end())
		return *it;

	std::cout << "Address (" << address << ") is not mapped to Bus" << std::endl;
	return nullptr;
}
