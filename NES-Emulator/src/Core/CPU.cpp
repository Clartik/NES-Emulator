#include "CPU.h"

CPU::CPU()
{
}

CPU::~CPU()
{
}

void CPU::Write(uint16_t address, uint8_t* data, unsigned int size)
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
		// Fetch
		uint8_t opcode = m_RAM[m_PC++];
		// Decode
		m_CurrentInstruction = &m_Instructions[opcode];
		// Execute
		m_CurrentInstruction->Func();
	}
}

uint8_t& CPU::FetchByte()
{
	switch (m_CurrentInstruction->AddressMode)
	{
		// No Memory Needed
		case AddressMode::IMM:
		// Memory comes from 0x00 - 0xFF
		case AddressMode::ZP:
		{
			return m_RAM[m_PC++];
		}
		// Memory comes from 0x00 - 0xFF with X offset
		case AddressMode::ZPX:
		{
			uint16_t address = m_RAM[m_PC++] + m_X;
			return m_RAM[address];
		}
		// Memory comes from 0x00 - 0xFF with Y offset
		case AddressMode::ZPY:
		{
			uint16_t address = m_RAM[m_PC++] + m_Y;
			return m_RAM[address];
		}
		// Returns the absolute address
		case AddressMode::ABS:
		{
			return m_RAM[GetAddress(m_PC)];
		}
		// Returns the absolute address with X offset
		case AddressMode::ABSX:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_X;

			// If page boundary was crossed by adding X
			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return m_RAM[addrAbs];
		}
		// Returns the absolute address with Y offset
		case AddressMode::ABSY:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_Y;

			// If page boundary was crossed by adding Y
			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return m_RAM[addrAbs];
		}
		// Pointer to actual address
		case AddressMode::IND:
		{
			uint16_t ptr = GetAddress(m_PC);
			return m_RAM[GetAddress(ptr)];
		}
		// Pointer to actual address with X Offset
		// Points to 0x00 to 0xFF (Page Zero)
		case AddressMode::INDX: 
		{
			uint16_t ptr = m_RAM[m_PC++] + m_X;

			// Wrapping if adding X goes beyond Zero Page
			if (ptr > 0xFF)
			{
				ptr = ptr - 0xFF;

				if (m_CurrentInstruction->CanIncreaseCycles)
					m_Cycles++;
			}

			return m_RAM[GetAddress(ptr)];
		}
		// Pointer to actual address with Y Offset
		// Probably Wrong. Very confused
		case AddressMode::INDY:
		{
			uint16_t ptr = m_RAM[m_PC++] + m_Y;
			return m_RAM[GetAddress(ptr)];
		}
		case AddressMode::ACC:
		{
			return m_A;
		}
		// Returns signed byte that is added to Program Counter Depending on the Condition
		case AddressMode::REL:
		{
			return m_RAM[m_PC++];
		}
	}
}

uint16_t CPU::GetAddress(uint16_t& ptr)
{
	uint8_t lo = m_RAM[ptr++];
	uint8_t hi = m_RAM[ptr++];

	return (hi << 8) | lo;
}

#pragma region Stack

void CPU::PushToStack(uint8_t value)
{
	m_RAM[m_SP++] = value;
}

void CPU::PushToStack(uint16_t value)
{
	uint8_t lo = value;
	uint8_t hi = (value >> 4);

	m_RAM[m_SP++] = lo;
	m_RAM[m_SP++] = hi;
}

uint8_t CPU::PopFromStack()
{
	return m_RAM[--m_SP];
}

uint16_t CPU::PopFromStackAddress()
{
	uint8_t lo = m_RAM[--m_SP];
	uint8_t hi = m_RAM[--m_SP];

	return (hi << 8) | lo;
}

#pragma endregion

#pragma region Instructions

void CPU::OP_ADC()
{
	uint16_t byte = FetchByte();
	uint16_t result = m_A + byte + m_F.C;

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
	Helper_BranchIf(!m_F.C);
}

void CPU::OP_BCS()
{
	Helper_BranchIf(m_F.C);
}

void CPU::OP_BEQ()
{
	Helper_BranchIf(m_F.Z);
}

void CPU::OP_BIT()
{
	uint16_t byte = FetchByte();
	
	m_F.Z = (m_A & byte) == 0;
	m_F.V = (byte & 0x40);
	m_F.N = (byte & 0x80);
}

void CPU::OP_BMI()
{
	Helper_BranchIf(m_F.N);
}

void CPU::OP_BNE()
{
	Helper_BranchIf(!m_F.Z);
}

void CPU::OP_BPL()
{
	Helper_BranchIf(!m_F.N);
}

void CPU::OP_BRK()
{
	PushToStack(m_PC);
	PushToStack(m_F.Hex);

	// TODO: Implement with Bus
	m_PC = m_RAM[IRQ_INTERRUPT_ADDRESS];

	m_F.B = 1;
}

void CPU::OP_BVC()
{
	Helper_BranchIf(!m_F.V);
}

void CPU::OP_BVS()
{
	Helper_BranchIf(m_F.V);
}

void CPU::OP_CLC()
{
	m_F.C = 0;
}

void CPU::OP_CLD()
{
	m_F.D = 0;
}

void CPU::OP_CLI()
{
	m_F.I = 0;
}

void CPU::OP_CLV()
{
	m_F.V = 0;
}

void CPU::OP_CMP()
{
	Helper_Compare(m_A);
}

void CPU::OP_CPX()
{
	Helper_Compare(m_X);
}

void CPU::OP_CPY()
{
	Helper_Compare(m_Y);
}

void CPU::OP_DEC()
{
	uint8_t byte = FetchByte();
	Helper_Decrement(byte);
}

void CPU::Helper_BranchIf(bool condition)
{
	int8_t byte = FetchByte();

	if (condition)
	{
		uint16_t temp = m_PC + byte;

		// Comparing high 8 bits because after zero page, the addresses exist in that space
		if ((temp & 0xFF00) != (m_PC & 0xFF00))
			m_Cycles += 2;

		m_PC = temp;
		m_Cycles++;
	}
}

void CPU::Helper_Compare(uint8_t value)
{
	uint8_t byte = FetchByte();

	m_F.C = value >= byte;
	m_F.Z = value == byte;

	uint8_t result = value - byte;

	m_F.N = result & 0x80;
}

void CPU::Helper_Decrement(uint8_t& value)
{
	value--;

	m_F.Z = value == 0;
	m_F.N = value & 0x80;
}

#pragma endregion
