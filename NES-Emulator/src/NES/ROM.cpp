#include "ROM.h"

#include <cstring>
#include <iostream>

// TODO: Add NES 2.0 format support

ROM::ROM(uint16_t startAddress, uint8_t* data, unsigned int size)
	: Peripheral(startAddress, startAddress + size)
{
	m_Data = new uint8_t[size];
	Load(data, size);
}

ROM::~ROM()
{
	delete[] m_Data;
}

void ROM::Load(uint8_t const* data, unsigned int size)
{
	memcpy(m_Data, data, size);

	#pragma region Header

	data += 4;	// NES + MS DOS File end

	uint8_t prgSize = *data;		// Size in 16 KB units
	data++;
	uint8_t chrSize = *data;		// Size in 8 KB units. 0 = CHR RAM
	data++;

	// FLAG 6
	uint8_t flag6 = *data;

	bool horizontalMirror = flag6 & 0x01;		// 1 = Horizontal, 0 = Vertical
	bool batteryExists = flag6 & 0x02;			// 0x6000 - 0x7FFF
	bool trainerExists = flag6 & 0x04;				// 512 Byte (0x7000 - 0x71FF)
	bool ignoreMirror = flag6 & 0x08;			// If ignored, it provides a four screen vram
	uint8_t mapperNybbleLo = flag6 & 0xF0;			// Only 4 bit

	data++;
	
	// FLAG 7
	uint8_t flag7 = *data;

	bool vsUniSystem = flag7 & 0x01;
	bool playChoice10 = flag7 & 0x02;
	uint8_t flags8To15 = flag7 & 0x0C;			// If equal to 2, flags 8 to 15 are in NES 2.0 format
	uint8_t mapperNybbleHi = flag7 & 0xF0;

	data++;

	// FLAG 8
	uint8_t prgRamSize = *data;					// Size in 8 kb units. // 0 means something chekck!
	data++;

	// FLAG 9	
	bool ntscTV = !(*data & 0x01);				// 0 = NTSC. 1 = PAL
	// Bit 1 to 7 are reserved, Should be 0

	data++;

	// FLAG 10
	uint8_t flag10 = *data;
	
	uint8_t tvSystem = flag10 & 0x03;			// 0 = NTSC, 2 = PAL, 1/3 = Dual
	bool prgRamExists = !(flag10 & 0x10);		// 0 = Present, 1 = Nope
	bool busConflicts = flag10 & 0x20;			// 0 = No Bus Conflicts, 1 = Bus Conflicts

	data += 5;									// Unused

	#pragma endregion

	// If Trainer exists, 512 bytes here or else it is 0
	if (trainerExists)
		data += TRAINER_SIZE;

	const uint8_t finalPRGSize = PRG_BASE_SIZE * prgSize;

	m_PRGStart = data;
	data += finalPRGSize;
	m_PRGEnd = data - 1;


	// CHR RAM
	if (!chrSize)
	{

	}
	else
	{
		const uint8_t finalCHRSize = CHR_BASE_SIZE * chrSize;

		m_CHRStart = data;
		data += finalCHRSize;
		m_CHREnd = data - 1;
	}

	// Ignoring Playchoice INST-ROM and PROM
}

uint8_t& ROM::Read(uint16_t address)
{
	return m_Data[address];
}

void ROM::Write(uint16_t address, uint8_t data)
{
	std::cout << "Writing is not permitted!" << std::endl;
}
