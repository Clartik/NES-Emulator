#pragma once

#include "Bus.h"

class BusController
{
public:
	Bus* GetBus() const { return m_Bus; }
protected:
	BusController(Bus* bus)
		: m_Bus(bus) { }

	Bus* m_Bus = nullptr;
};