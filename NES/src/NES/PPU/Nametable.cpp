#include "pch.h"
#include "Nametable.h"

Nametable::Nametable(uint16_t startAddress)
    : Peripheral(startAddress, startAddress + (NAMETABLE_TOTAL_SIZE - 1))
{
}

Nametable::~Nametable()
{
}

uint8_t& Nametable::Read(uint16_t address)
{
    return GetByte(address);
}

void Nametable::Write(uint16_t address, uint8_t value)
{
    GetByte(address) = value;
}

uint8_t& Nametable::GetByte(uint16_t address)
{
    if (address <= NAMETABLE_SIZE)
        return m_NameTable[address];

    return m_AttributeTable[address];
}
