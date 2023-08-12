#pragma once

#include <stdint.h>
#include <string>

#include "NES/Base/Peripheral.h"

#include "Mapper.h"

const uint16_t ROM_START_ADDRESS = 0x4020;

const unsigned int TRAINER_SIZE = 512;
const unsigned int PRG_BASE_SIZE = 16384;		// Multipled with actual size
const unsigned int CHR_BASE_SIZE = 8192;		// Multipled with actual size

class ROM : public Peripheral
{
public:
	ROM(const std::string& filepath, unsigned int size);
	~ROM();

	virtual uint8_t& Read(uint16_t address) override;
	virtual void Write(uint16_t address, uint8_t data) override;
private:
	void Load();
	void SetMapper(uint8_t mapperByte);
private:
	uint8_t* m_PRGStart;
	unsigned int m_PRGSize;

	uint8_t* m_CHRStart;
	unsigned int m_CHRSize;

	uint8_t* m_Data;
	Mapper* m_Mapper;
};