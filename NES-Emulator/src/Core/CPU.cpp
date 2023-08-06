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
			uint8_t pt1 = m_RAM[m_PC++];
			uint8_t pt2 = m_RAM[m_PC++];

			return (pt2 << 8) | pt1;
		}
		case AddressMode::ABSX:
		{
			uint8_t pt1 = m_RAM[m_PC++];
			uint8_t pt2 = m_RAM[m_PC++];

			uint8_t val = ((pt2 << 8) | pt1) + m_X;

			if (val > 255)
			{
				val = val - 255;

				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return val;
		}
		case AddressMode::ABSY:
		{
			uint8_t pt1 = m_RAM[m_PC++];
			uint8_t pt2 = m_RAM[m_PC++];

			uint8_t val = ((pt2 << 8) | pt1) + m_Y;

			if (val > 255)
			{
				val = val - 255;

				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return val;
		}
		case AddressMode::IND:
		{
			uint8_t ptr1 = m_RAM[m_PC++];
			uint8_t ptr2 = m_RAM[m_PC++];

			const uint16_t ptr = (ptr2 << 8) | ptr1;

			uint8_t real1 = m_RAM[ptr + 0];
			uint8_t real2 = m_RAM[ptr + 1];

			return (real2 << 8) | real1;
		}
		case AddressMode::INDX: 
		{
			uint8_t ptr1 = m_RAM[m_PC++];
			uint8_t ptr2 = m_RAM[m_PC++];

			const uint16_t ptr = (ptr2 << 8) | ptr1;

			uint8_t real1 = m_RAM[ptr + 0];
			uint8_t real2 = m_RAM[ptr + 1];

			uint8_t realVal = ((real2 << 8) | real1) + m_X;

			if (realVal > 255)
				realVal = realVal - 255;

			return realVal;
		}
		case AddressMode::INDY:
		{
			uint8_t ptr1 = m_RAM[m_PC++];
			uint8_t ptr2 = m_RAM[m_PC++];

			const uint16_t ptr = (ptr2 << 8) | ptr1;

			uint8_t real1 = m_RAM[ptr + 0];
			uint8_t real2 = m_RAM[ptr + 1];

			uint8_t realVal = ((real2 << 8) | real1) + m_Y;

			if (realVal > 255)
			{
				realVal = realVal - 255;

				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return realVal;
		}
		case AddressMode::ACC:
		{
			return m_A;
		}
	}
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

#pragma endregion
