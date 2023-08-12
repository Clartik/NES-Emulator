#pragma once

#include <stdint.h>

#include "Base/Peripheral.h"

const uint16_t ROM_START_ADDRESS = 0x4020;

const unsigned int TRAINER_SIZE = 512;
const unsigned int PRG_BASE_SIZE = 16384;		// Multipled with actual size
const unsigned int CHR_BASE_SIZE = 8192;		// Multipled with actual size

class ROM : public Peripheral
{
public:
	ROM(uint8_t* data, unsigned int size);
	~ROM();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t data) override;
private:
	void Load(uint8_t const* data, unsigned int size);
private:
	uint8_t const* m_PRGStart;
	uint8_t const* m_PRGEnd;

	uint8_t const* m_CHRStart;
	uint8_t const* m_CHREnd;

	uint8_t* m_Data;
};