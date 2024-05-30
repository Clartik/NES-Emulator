#include "PPU.h"

#include <iostream>
#include <thread>
#include <chrono>

// StartAddress + size - 1 because startAddress is the start and size - 1 is the end
PPU::PPU(uint16_t startAddress)
	: Peripheral(startAddress, startAddress + 6), BusController(new Bus)
{
}

PPU::~PPU()
{
}

uint8_t& PPU::Read(uint16_t address)
{
	switch (address)
	{
	case 0x02:
		return m_PPUStatus.Hex;
	case 0x04:
		return m_OAMData;
	case 0x07:
		return m_PPUData;
	default:
	{
		std::cout << "Reading from 0x" << std::hex << (address + m_StartAddress) << " is not allowed!" << std::endl;
		return m_PPUCtrl.Hex;		// Just to satisfy function return. DO NOT USE
	}
	}
}

void PPU::Write(uint16_t address, uint8_t value)
{
	switch (address)
	{
	case 0x00:
		m_PPUCtrl.Hex = value;
		break;
	case 0x01:
		m_PPUMask.Hex = value;
		break;
	case 0x03:
		m_OAMAddress = value;
		break;
	case 0x04:
		m_OAMData = value;
		break;
	case 0x05:
		m_PPUScroll = value;
		break;
	case 0x06:
		m_PPUAddress = value;
		break;
	case 0x07:
		m_PPUData = value;
		break;
	default:
	{
		std::cout << "Writing to 0x" << std::hex << (address + m_StartAddress) << " is not allowed!" << std::endl;
		return;
	}
	}
}

uint8_t* PPU::VRAMRead(uint16_t address)
{
	address = GetMirrorAddress(address);
	return m_Bus->Read(address);
}

void PPU::VRAMWrite(uint16_t address, uint8_t value)
{
	address = GetMirrorAddress(address);
	m_Bus->Write(address, value);
}

void PPU::Init()
{
}

void PPU::Cycle(double waitTime)
{
	std::this_thread::sleep_for(std::chrono::microseconds((int)waitTime));
}

uint16_t PPU::GetMirrorAddress(uint16_t address)
{
	if (address >= VRAM_START_ADDRESS && address <= VRAM_MIRROR_END_ADDRESS)
		return address & VRAM_END_ADDRESS;

	return address;
}
