#pragma once

#include <stdint.h>

const unsigned int KB_TO_BYTES = 1024;

class Mapper
{
public:
	virtual uint16_t GetAddress(uint16_t address) = 0;
	virtual void Write(uint16_t address, uint8_t value) {}
	virtual void Reset() {}
protected:
	Mapper(uint16_t prgStartAddress, unsigned int prgSize)
		: m_PRGStart(prgStartAddress), m_PRGSize(prgSize) { }

	uint16_t m_PRGStart;
	unsigned int m_PRGSize;
};

class Mapper0 : public Mapper
{
public:
	Mapper0(uint16_t prgStartAddress, unsigned int prgSize);
	
	// Return First 16 KB of ROM for 0x8000 - 0xBFFF
	// Return Last 16 KB of ROM for 0xC000 - 0xFFFF if greater than 16 kb
	// If not, mirror 0x8000 - 0xBFFF
	virtual uint16_t GetAddress(uint16_t address) override;
};

class Mapper1 : public Mapper
{
public:
	Mapper1(uint16_t prgStartAddress, unsigned int prgSize);

	virtual uint16_t GetAddress(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t value) override;
	virtual void Reset() override;
private:
	uint8_t& GetInternalRegister(uint16_t address);
private:
	// Registers
	union
	{
		struct
		{
			uint8_t MM : 2;		// Mirroring. 0 = One-screen, lower bank. 1 = One-screen, upper bank. 2 = Vertical. 3 = Horizontal
			uint8_t PP : 2;		// PRG bank mode. 1: Switch 32 kb at 0x8000, ignore low bit of bank number
			// 2: Fix first bank at 0x8000 and switch 16 kb bank at 0xC000;
			// 3: Fix Last bank at 0xC000 and switch 16 kb bank at 0x8000;
			uint8_t C : 1;		// 0: Switch 8 kb at a time. 1: Switch two seperate 4 kb banks
		};

		uint8_t Hex;	// 5 bit
	} m_Control;				// 0x8000 - 0x9FFF
	uint8_t m_CHRB0, m_CHRB1, m_PRGB;		// 5 BITS! CHRB0: 0xA000 - 0xBFFF. CHRB1: 0xC000 - 0xDFFF. PRGB: 0xE000 - 0xFFFF

	uint8_t m_SR = 0x10;		// Only use first 5 Bits!
};