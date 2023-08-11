#pragma once

#include "NES/Base/Peripheral.h"
#include "NES/Base/BusController.h"

const unsigned int SPRITE_SIZE = 4;
const unsigned int OAM_SIZE = 256;			// 64 sprites can be in the OAM so 64 * 4 bytes

const unsigned int VRAM_SIZE = 2048;
const uint16_t VRAM_START_ADDRESS = 0x2000;
const uint16_t VRAM_END_ADDRESS = 0x2FFF;
const uint16_t VRAM_MIRROR_END_ADDRESS = 0X2EFF;

const uint16_t NAMETABLE_START_ADDRESS = 0x2000;

class PPU : public Peripheral, public BusController
{
public:
	PPU(uint16_t startAddress);
	~PPU();

	// Implements Peripheral
	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t value) override;

	uint8_t* VRAMRead(uint16_t address);
	void VRAMWrite(uint16_t address, uint8_t value);

	void Cycle(double waitTime);
private:
	void Init();

	uint16_t GetMirrorAddress(uint16_t address);
private:
	union
	{
		struct
		{
			uint8_t NN : 2;		// Nametable Select
			uint8_t	I : 1;		// Increment for VRAM address
			uint8_t S : 1;		// Sprite tile Select
			uint8_t B : 1;		// Background tile select
			uint8_t H : 1;		// Sprite Height
			uint8_t P : 1;		// PPU master/slave
			uint8_t V : 1;		// NMI Enable
		};

		uint8_t Hex;
	} m_PPUCtrl;
	union 
	{
		struct
		{
			uint8_t G : 1;		// Greyscale
			uint8_t m : 1;		// Background Left column enable
			uint8_t M : 1;		// Sprite Left column enable
			uint8_t b : 1;		// Background enable
			uint8_t s : 1;		// Sprite enable
			uint8_t Red : 1;		// Emphasize Red
			uint8_t Grey : 1;		// Emphasize Green
			uint8_t Blue : 1;		// Emphasize Blue
		};

		uint8_t Hex;
	} m_PPUMask;
	union
	{
		struct
		{
			uint8_t Unused : 5;
			uint8_t O : 1;			// Sprite Overflow
			uint8_t S : 1;			// Sprite 0 hit
			uint8_t V : 1;			// vblank
		};

		uint8_t Hex;
	} m_PPUStatus;
	uint8_t m_OAMAddress, m_OAMData, m_OAMDMA;
	uint8_t m_PPUScroll, m_PPUAddress, m_PPUData;

	bool m_Odd;
};