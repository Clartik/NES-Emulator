#include "CPU.h"

CPU::CPU()
{
}

CPU::~CPU()
{
}

void CPU::Write(uint8_t address, uint8_t* data, unsigned int size)
{
	for (int i = 0; i < size; i++)
		m_RAM[address + i] = *(data + i);
}

void CPU::Reset()
{
	m_PC = PC_START_ADDRESS;
	m_SP = STACK_START_ADDRESS;

	m_F.Hex = 0x00;

	for (int i = 0; i < MEMORY_SIZE; i++)
		m_RAM[i] = 0;
}

void CPU::Cycle()
{
	while (m_Cycles > 0)
	{
		uint16_t opcode = FetchOPCode();
		DecodeAndExecute(opcode);
	}
}

uint16_t CPU::FetchOPCode()
{
	uint8_t pcl = m_RAM[m_PC++];
	uint8_t pch = m_RAM[m_PC++];

	m_Cycles--;
	return (pch << 8) | pcl;
}

void CPU::DecodeAndExecute(uint16_t instruction)
{
	
}

uint16_t CPU::FetchByte()
{
	switch (m_CurrentInstruction->AddressMode)
	{
		case AddressMode::IMM:
		case AddressMode::ZP:
		{
			return m_RAM[m_PC++];
		}
		case AddressMode::ZPX:
		{
			return m_RAM[m_PC++] + m_X;
		}
		case AddressMode::ZPY:
		{
			return m_RAM[m_PC++] + m_Y;
		}
		case AddressMode::ABS:
		{
			return GetAddress(m_PC);
		}
		case AddressMode::ABSX:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_X;

			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return addrAbs;
		}
		case AddressMode::ABSY:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_Y;

			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return addrAbs;
		}
		case AddressMode::IND:
		{
			uint16_t ptr = GetAddress(m_PC);
			return GetAddress(ptr);
		}
		case AddressMode::INDX: 
		{
			uint16_t ptr = GetAddress(m_PC) + m_X;

			if (ptr > 0xFF)
			{
				ptr = ptr - 0xFF;

				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return GetAddress(ptr);
		}
		case AddressMode::INDY:
		{
			uint16_t ptr = GetAddress(m_PC) + m_Y;
			return GetAddress(ptr);
		}
		case AddressMode::ACC:
		{
			return m_A;
		}
		case AddressMode::REL:
		{
			return (int8_t)m_RAM[m_PC++];
		}
	}
}

uint16_t CPU::GetAddress(uint16_t& ptr)
{
	uint8_t lo = m_RAM[ptr++];
	uint8_t hi = m_RAM[ptr++];

	return (hi << 8) | lo;
}

#pragma region Instructions

void CPU::OP_ADC()
{
	uint8_t byte = FetchByte();
	uint8_t result = m_A + byte + m_F.C;

	m_F.C = result > 255;
	m_F.Z = result == 0;
	m_F.V = ~(m_A ^ byte) & (m_A ^ result) & 0x80;
	m_F.N = result & 0x80;

	m_A = result;
}

void CPU::OP_AND()
{
	m_A &= FetchByte();

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
}

void CPU::OP_ASL()
{
	uint8_t byte = FetchByte();
	uint8_t temp = byte << 1;

	m_F.C = byte & 0x80;
	m_F.Z = temp == 0;
	m_F.N = temp & 0x80;
}

void CPU::OP_BCC()
{
	uint8_t byte = FetchByte();

	if (!m_F.C)
		m_PC += byte;
}

void CPU::OP_BCS()
{
	uint8_t byte = FetchByte();

	if (m_F.C)
		m_PC += byte;
}

#pragma endregion
