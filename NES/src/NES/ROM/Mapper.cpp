#include "Mapper.h"

#include <iostream>

Mapper0::Mapper0(uint16_t prgStartAddress, unsigned int prgSize)
    : Mapper(prgStartAddress, prgSize)
{
}

uint16_t Mapper0::GetAddress(uint16_t address)
{
    // TODO: 

    // Less than 16 KB
    if (m_PRGSize <= 16 * KB_TO_BYTES)
        return address & 0xBFFF;

    return m_PRGStart + (address - 0x8000);
}

Mapper1::Mapper1(uint16_t prgStartAddress, unsigned int prgSize)
    : Mapper(prgStartAddress, prgSize)
{
}

uint16_t Mapper1::GetAddress(uint16_t address)
{
    if (address >= 0x0000 && address <= 0x1FFF)
    {
        return 0;
    }
}

void Mapper1::Write(uint16_t address, uint8_t value)
{
    static int writeCount = 0;

    if (address >= 0x8000 && address <= 0xFFFF)
    {
        if (writeCount >= 4)
        {
            uint8_t& bank = GetInternalRegister(address & 0x6000);

            bank = m_SR >> 1;
            bank |= (value & 0x01) << 4;
            
            m_SR = 0x10;    // 0001 0000 = 10000
            writeCount = 0;

            return;
        }

        m_SR >>= 1;
        m_SR |= (value & 0x01) << 4;

        writeCount++;
    }
}

void Mapper1::Reset()
{
}

uint8_t& Mapper1::GetInternalRegister(uint16_t address)
{
    if (address >= 0x8000 && address <= 0x9FFF)
        return m_Control.Hex;
    
    if (address >= 0xA000 && address <= 0xBFFF)
        return m_CHRB0;

    if (address >= 0xC000 && address <= 0xDFFF)
        return m_CHRB1;

    if (address >= 0xE000 && address <= 0xFFFF)
        return m_PRGBank;

    std::cout << "Couldn't find correct internal register at 0x" << std::hex << address << std::endl;
    return m_Control.Hex;
}
