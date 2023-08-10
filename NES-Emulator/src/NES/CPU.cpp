#include "CPU.h"

#include <iostream>

CPU::CPU(Bus* bus)
	: m_Bus(bus)
{
	m_Instructions = {
		{ 0x69, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::IMM , 2, false } },
		{ 0x65, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::ZP  , 3, false } },
		{ 0x75, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::ZPX , 4, false } },
		{ 0x6D, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::ABS , 4, false } },
		{ 0x7D, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::ABSX, 4, true } },
		{ 0x79, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::ABSY, 4, true } },
		{ 0x61, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::INDX, 6, false } },
		{ 0x71, { "ADC", BIND_OPCODE_FN(OP_ADC), AddressMode::INDY, 5, true } },

		{ 0x29, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::IMM , 2, false } },
		{ 0x25, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::ZP  , 3, false } },
		{ 0x35, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::ZPX , 4, false } },
		{ 0x2D, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::ABS , 4, false } },
		{ 0x3D, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::ABSX, 4, true } },
		{ 0x39, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::ABSY, 4, true } },
		{ 0x21, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::INDX, 6, false } },
		{ 0x31, { "AND", BIND_OPCODE_FN(OP_AND), AddressMode::INDY, 5, true } },

		{ 0x0A, { "ASL", BIND_OPCODE_FN(OP_ASL), AddressMode::ACC, 2, false } },
		{ 0x06, { "ASL", BIND_OPCODE_FN(OP_ASL), AddressMode::ZP, 5, false } },
		{ 0x16, { "ASL", BIND_OPCODE_FN(OP_ASL), AddressMode::ZPX, 6, false } },
		{ 0x0E, { "ASL", BIND_OPCODE_FN(OP_ASL), AddressMode::ABS, 6, false } },
		{ 0x1E, { "ASL", BIND_OPCODE_FN(OP_ASL), AddressMode::ABSX, 7, false } },

		{ 0x90, { "BCC", BIND_OPCODE_FN(OP_BCC), AddressMode::REL, 2, false } },

		{ 0xB0, { "BCS", BIND_OPCODE_FN(OP_BCS), AddressMode::REL, 2, false } },

		{ 0xF0, { "BEQ", BIND_OPCODE_FN(OP_BEQ), AddressMode::REL, 2, false } },

		{ 0x24, { "BIT", BIND_OPCODE_FN(OP_BIT), AddressMode::ZP, 3, false } },
		{ 0x2C, { "BIT", BIND_OPCODE_FN(OP_BIT), AddressMode::ABS, 4, false } },

		{ 0x30, { "BMI", BIND_OPCODE_FN(OP_BMI), AddressMode::REL, 2, false } },

		{ 0x10, { "BPL", BIND_OPCODE_FN(OP_BPL), AddressMode::REL, 2, false } },

		{ 0x00, { "BRK", BIND_OPCODE_FN(OP_BRK), AddressMode::IMP, 7, false } },

		{ 0x50, { "BVC", BIND_OPCODE_FN(OP_BVC), AddressMode::REL, 2, false } },

		{ 0x70, { "BVS", BIND_OPCODE_FN(OP_BVS), AddressMode::REL, 2, false } },

		{ 0x18, { "CLC", BIND_OPCODE_FN(OP_CLC), AddressMode::IMP, 2, false } },

		{ 0xD8, { "CLD", BIND_OPCODE_FN(OP_CLD), AddressMode::IMP, 2, false } },

		{ 0x58, { "CLI", BIND_OPCODE_FN(OP_CLI), AddressMode::IMP, 2, false } },

		{ 0xB8, { "CLV", BIND_OPCODE_FN(OP_CLV), AddressMode::IMP, 2, false } },

		{ 0xC9, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::IMM, 2, false } },
		{ 0xC5, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::ZP, 3, false } },
		{ 0xD5, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::ZPX, 4, false } },
		{ 0xCD, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::ABS, 4, false } },
		{ 0xDD, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::ABSX, 4, true } },
		{ 0xD9, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::ABSY, 4, true } },
		{ 0xC1, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::INDX, 6, false } },
		{ 0xD1, { "CMP", BIND_OPCODE_FN(OP_CMP), AddressMode::INDY, 5, true} },

		{ 0xE0, { "CPX", BIND_OPCODE_FN(OP_CPX), AddressMode::IMM, 2, false } },
		{ 0xE4, { "CPX", BIND_OPCODE_FN(OP_CPX), AddressMode::ZP, 3, false } },
		{ 0xEC, { "CPX", BIND_OPCODE_FN(OP_CPX), AddressMode::ABS, 4, false } },

		{ 0xC0, { "CPY", BIND_OPCODE_FN(OP_CPY), AddressMode::IMM, 2, false } },
		{ 0xC4, { "CPY", BIND_OPCODE_FN(OP_CPY), AddressMode::ZP, 3, false } },
		{ 0xCC, { "CPY", BIND_OPCODE_FN(OP_CPY), AddressMode::ABS, 4, false } },

		{ 0xC6, { "DEC", BIND_OPCODE_FN(OP_DEC), AddressMode::ZP, 5, false } },
		{ 0xD6, { "DEC", BIND_OPCODE_FN(OP_DEC), AddressMode::ZPX, 6, false } },
		{ 0xCE, { "DEC", BIND_OPCODE_FN(OP_DEC), AddressMode::ABS, 6, false } },
		{ 0xDE, { "DEC", BIND_OPCODE_FN(OP_DEC), AddressMode::ABSX, 7, false } },

		{ 0xCA, { "DEX", BIND_OPCODE_FN(OP_DEX), AddressMode::IMP, 2, false } },

		{ 0x88, { "DEY", BIND_OPCODE_FN(OP_DEY), AddressMode::IMP, 2, false } },

		{ 0x49, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::IMM, 2, false } },
		{ 0x45, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::ZP, 3, false } },
		{ 0x55, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::ZPX, 4, false } },
		{ 0x4D, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::ABS, 4, false } },
		{ 0x5D, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::ABSX, 4, true } },
		{ 0x59, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::ABSY, 4, true } },
		{ 0x41, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::INDX, 6, false } },
		{ 0x51, { "EOR", BIND_OPCODE_FN(OP_EOR), AddressMode::INDY, 5, true } },

		{ 0xE6, { "INC", BIND_OPCODE_FN(OP_INC), AddressMode::ZP, 5, false } },
		{ 0xF6, { "INC", BIND_OPCODE_FN(OP_INC), AddressMode::ZPX, 6, false } },
		{ 0xEE, { "INC", BIND_OPCODE_FN(OP_INC), AddressMode::ABS, 6, false } },
		{ 0xFE, { "INC", BIND_OPCODE_FN(OP_INC), AddressMode::ABSX, 7, false } },

		{ 0xE8, { "INX", BIND_OPCODE_FN(OP_INX), AddressMode::IMP, 2, false } },

		{ 0xC8, { "INY", BIND_OPCODE_FN(OP_INY), AddressMode::IMP, 2, false } },

		{ 0x4C, { "JMP", BIND_OPCODE_FN(OP_JMP), AddressMode::ABS, 3, false } },
		{ 0x6C, { "JMP", BIND_OPCODE_FN(OP_JMP), AddressMode::IND, 5, false } },

		{ 0x20, { "JSR", BIND_OPCODE_FN(OP_JSR), AddressMode::ABS, 6, false } },

		{ 0xA9, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::IMM, 2, false } },
		{ 0xA5, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::ZP, 3, false } },
		{ 0xB5, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::ZPX, 4, false } },
		{ 0xAD, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::ABS, 4, false } },
		{ 0xBD, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::ABSX, 4, true } },
		{ 0xB9, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::ABSY, 4, true } },
		{ 0xA1, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::INDX, 6, false } },
		{ 0xB1, { "LDA", BIND_OPCODE_FN(OP_LDA), AddressMode::INDY, 5, true} },

		{ 0xA2, { "LDX", BIND_OPCODE_FN(OP_LDX), AddressMode::IMM, 2, false } },
		{ 0xA6, { "LDX", BIND_OPCODE_FN(OP_LDX), AddressMode::ZP, 3, false } },
		{ 0xB6, { "LDX", BIND_OPCODE_FN(OP_LDX), AddressMode::ZPY, 4, false } },
		{ 0xAE, { "LDX", BIND_OPCODE_FN(OP_LDX), AddressMode::ABS, 4, false } },
		{ 0xBE, { "LDX", BIND_OPCODE_FN(OP_LDX), AddressMode::ABSY, 4, true} },

		{ 0xA0, { "LDY", BIND_OPCODE_FN(OP_LDY), AddressMode::IMM, 2, false } },
		{ 0xA4, { "LDY", BIND_OPCODE_FN(OP_LDY), AddressMode::ZP, 3, false } },
		{ 0xB4, { "LDY", BIND_OPCODE_FN(OP_LDY), AddressMode::ZPX, 4, false } },
		{ 0xAC, { "LDY", BIND_OPCODE_FN(OP_LDY), AddressMode::ABS, 4, false } },
		{ 0xBC, { "LDY", BIND_OPCODE_FN(OP_LDY), AddressMode::ABSX, 4, true} },

		{ 0x4A, { "LSR", BIND_OPCODE_FN(OP_LSR), AddressMode::ACC, 2, false } },
		{ 0x46, { "LSR", BIND_OPCODE_FN(OP_LSR), AddressMode::ZP, 5, false } },
		{ 0x56, { "LSR", BIND_OPCODE_FN(OP_LSR), AddressMode::ZPX, 6, false } },
		{ 0x4E, { "LSR", BIND_OPCODE_FN(OP_LSR), AddressMode::ABS, 6, false } },
		{ 0x5E, { "LSR", BIND_OPCODE_FN(OP_LSR), AddressMode::ABSX, 7, false } },

		{ 0xEA, { "NOP", BIND_OPCODE_FN(OP_NOP), AddressMode::IMP, 2, false } },

		{ 0x09, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::IMM, 2, false } },
		{ 0x05, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::ZP, 3, false } },
		{ 0x15, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::ZPX, 4, false } },
		{ 0x0D, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::ABS, 4, false } },
		{ 0x1D, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::ABSX, 4, true } },
		{ 0x19, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::ABSY, 4, true } },
		{ 0x01, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::INDX, 6, false } },
		{ 0x11, { "ORA", BIND_OPCODE_FN(OP_ORA), AddressMode::INDY, 5, true} },

		{ 0x48, { "PHA", BIND_OPCODE_FN(OP_PHA), AddressMode::IMP, 3, false } },

		{ 0x08, { "PHP", BIND_OPCODE_FN(OP_PHP), AddressMode::IMP, 3, false } },

		{ 0x68, { "PLA", BIND_OPCODE_FN(OP_PLA), AddressMode::IMP, 4, false } },

		{ 0x28, { "PLP", BIND_OPCODE_FN(OP_PLP), AddressMode::IMP, 4, false } },

		{ 0x2A, { "ROL", BIND_OPCODE_FN(OP_ROL), AddressMode::ACC, 2, false } },
		{ 0x26, { "ROL", BIND_OPCODE_FN(OP_ROL), AddressMode::ZP, 5, false } },
		{ 0x36, { "ROL", BIND_OPCODE_FN(OP_ROL), AddressMode::ZPX, 6, false } },
		{ 0x2E, { "ROL", BIND_OPCODE_FN(OP_ROL), AddressMode::ABS, 6, false } },
		{ 0x3E, { "ROL", BIND_OPCODE_FN(OP_ROL), AddressMode::ABSX, 7, false } },

		{ 0x6A, { "ROR", BIND_OPCODE_FN(OP_ROR), AddressMode::ACC, 2, false } },
		{ 0x66, { "ROR", BIND_OPCODE_FN(OP_ROR), AddressMode::ZP, 5, false } },
		{ 0x76, { "ROR", BIND_OPCODE_FN(OP_ROR), AddressMode::ZPX, 6, false } },
		{ 0x6E, { "ROR", BIND_OPCODE_FN(OP_ROR), AddressMode::ABS, 6, false } },
		{ 0x7E, { "ROR", BIND_OPCODE_FN(OP_ROR), AddressMode::ABSX, 7, false } },

		{ 0x40, { "RTI", BIND_OPCODE_FN(OP_RTI), AddressMode::IMP, 6, false } },

		{ 0x60, { "RTS", BIND_OPCODE_FN(OP_RTS), AddressMode::IMP, 6, false } },

		{ 0xE9, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::IMM, 2, false } },
		{ 0xE5, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::ZP, 3, false } },
		{ 0xF5, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::ZPX, 4, false } },
		{ 0xED, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::ABS, 4, false } },
		{ 0xFD, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::ABSX, 4, true } },
		{ 0xF9, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::ABSY, 4, true } },
		{ 0xE1, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::INDX, 6, false } },
		{ 0xF1, { "SBC", BIND_OPCODE_FN(OP_SBC), AddressMode::INDY, 5, true} },

		{ 0x38, { "SEC", BIND_OPCODE_FN(OP_SEC), AddressMode::IMP, 2, false } },

		{ 0xF8, { "SED", BIND_OPCODE_FN(OP_SED), AddressMode::IMP, 2, false } },

		{ 0x78, { "SEI", BIND_OPCODE_FN(OP_SEI), AddressMode::IMP, 2, false } },

		{ 0x85, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::ZP, 3, false } },
		{ 0x95, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::ZPX, 4, false } },
		{ 0x8D, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::ABS, 4, false } },
		{ 0x9D, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::ABSX, 5, false } },
		{ 0x99, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::ABSY, 5, false } },
		{ 0x81, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::INDX, 6, false } },
		{ 0x91, { "STA", BIND_OPCODE_FN(OP_STA), AddressMode::INDY, 6, false } },

		{ 0x86, { "STX", BIND_OPCODE_FN(OP_STX), AddressMode::ZP, 3, false } },
		{ 0x96, { "STX", BIND_OPCODE_FN(OP_STX), AddressMode::ZPY, 4, false } },
		{ 0x8E, { "STX", BIND_OPCODE_FN(OP_STX), AddressMode::ABS, 4, false } },

		{ 0x84, { "STY", BIND_OPCODE_FN(OP_STY), AddressMode::ZP, 3, false } },
		{ 0x94, { "STY", BIND_OPCODE_FN(OP_STY), AddressMode::ZPX, 4, false } },
		{ 0x8C, { "STY", BIND_OPCODE_FN(OP_STY), AddressMode::ABS, 4, false } },

		{ 0xAA, { "TAX", BIND_OPCODE_FN(OP_TAX), AddressMode::IMP, 2, false } },

		{ 0xA8, { "TAY", BIND_OPCODE_FN(OP_TAY), AddressMode::IMP, 2, false } },

		{ 0xB8, { "TSX", BIND_OPCODE_FN(OP_TSX), AddressMode::IMP, 2, false } },

		{ 0x8A, { "TXA", BIND_OPCODE_FN(OP_TXA), AddressMode::IMP, 2, false } },

		{ 0x9A, { "TXS", BIND_OPCODE_FN(OP_TXS), AddressMode::IMP, 2, false } },

		{ 0x98, { "TYA", BIND_OPCODE_FN(OP_TYA), AddressMode::IMP, 2, false } },
	};
}

CPU::~CPU()
{
}

uint8_t* CPU::Read(uint16_t address)
{
	address = GetMirrorAddress(address);
	return m_Bus->Read(address);
}

void CPU::Write(uint16_t address, uint8_t data)
{
	address = GetMirrorAddress(address);
	return m_Bus->Write(address, data);
}

void CPU::Write(uint16_t address, uint8_t* data, unsigned int size)
{
	address = GetMirrorAddress(address);
	m_Bus->Write(address, data, size);
}

void CPU::Reset()
{
	m_PC = PC_START_ADDRESS;
	m_SP = STACK_START_ADDRESS;

	m_F.Hex = 0x00;

	// Set Memory to 0
	memset(Read(MEMORY_START_ADDRESS), 0, MEMORY_SIZE);
}

void CPU::NMI()
{
}

void CPU::IRQ()
{
}

bool CPU::Cycle()
{
	if (m_Cycles > 0)
		m_Cycles--;
	
	// IRQ + 1 because addresses are two bytes long
	if (m_PC >= NMI_INTERRUPT_ADDRESS && m_PC <= IRQ_INTERRUPT_ADDRESS + 1)
		m_PC = GetAddress(m_PC);

	uint8_t opcode = *Read(m_PC++);

	// Decode
	if (m_Instructions.find(opcode) == m_Instructions.end())
	{
		std::cout << "Could not find instruction for 0x" << std::hex << opcode << std::endl;
		return false;
	}

	m_CurrentInstruction = &m_Instructions[opcode];

	std::cout << "Instruction: " << m_CurrentInstruction->Name << " Executed!" << std::endl;

	// Execute
	m_Cycles += m_CurrentInstruction->Cycles;
	m_CurrentInstruction->Func();

	return true;
}

// Absolute only return 16 bit. rest return 8 bit
uint16_t CPU::FetchAddress()
{
	switch (m_CurrentInstruction->AddressMode)
	{
		// 8 Bit Address 0x00 to 0xFF
		case AddressMode::ZP:
		{
			return *Read(m_PC++);
		}
		// Memory comes from 0x00 - 0xFF with X offset
		case AddressMode::ZPX:
		{
			uint8_t address = *Read(m_PC++) + m_X;
			return address;
		}
		// Memory comes from 0x00 - 0xFF with Y offset
		case AddressMode::ZPY:
		{
			uint8_t address = *Read(m_PC++) + m_Y;
			return address;
		}
		// Returns the absolute address
		case AddressMode::ABS:
		{
			return GetAddress(m_PC);
		}
		// Returns the absolute address with X offset
		case AddressMode::ABSX:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_X;

			// If page boundary was crossed by adding X
			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanAddAdditionalCycles)
					m_Cycles++;
			}

			return addrAbs;
		}
		// Returns the absolute address with Y offset
		case AddressMode::ABSY:
		{
			uint16_t addrRel = GetAddress(m_PC);
			uint16_t addrAbs = addrRel + m_Y;

			// If page boundary was crossed by adding Y
			if ((addrAbs & 0xFF) != (addrRel & 0xFF))
			{
				if (m_CurrentInstruction->CanAddAdditionalCycles)
					m_Cycles++;
			}

			return addrAbs;
		}
		// Pointer to actual address
		case AddressMode::IND:
		{
			uint16_t ptr = GetAddress(m_PC);
			return GetAddress(ptr);
		}
		// Pointer to actual address with X Offset
		// Points to 0x00 to 0xFF (Page Zero)
		case AddressMode::INDX:
		{
			uint16_t ptr = *Read(m_PC++) + m_X;

			// Wrapping if adding X goes beyond Zero Page
			if (ptr > 0xFF)
				ptr = ptr - 0xFF;

			uint8_t address = GetAddress(ptr);
			return address;
		}
		// Pointer to actual address with Y Offset
		// Probably Wrong. Very confused
		case AddressMode::INDY:
		{
			uint16_t ptr = *Read(m_PC++) + m_Y;

			// ptr goes past Zero Page
			if (ptr > 0xFF)
			{
				if (m_CurrentInstruction->CanAddAdditionalCycles)
					m_Cycles++;
			}

			uint8_t address = GetAddress(ptr);
			return address;
		}
		default:
		{
			std::cout << "Addressing Mode is Not Implemented for FetchAddress" << std::endl;
			return 0;
		}
	}
}

uint8_t& CPU::FetchByte()
{
	switch (m_CurrentInstruction->AddressMode)
	{
		case AddressMode::ACC:
		{
			return m_A;
		}
		// Returns signed byte that needs to be cast
		case AddressMode::REL:
		// Value Passed in Memory
		case AddressMode::IMM:
		{
			return *Read(m_PC++);
		}
		// Memory comes from 0x00 - 0xFF
		case AddressMode::ZP:
		{
			return *Read(FetchAddress());
		}
		// Memory comes from 0x00 - 0xFF with X offset
		case AddressMode::ZPX:
		{
			return *Read(FetchAddress());
		}
		// Memory comes from 0x00 - 0xFF with Y offset
		case AddressMode::ZPY:
		{
			return *Read(FetchAddress());
		}
		// Returns the absolute address
		case AddressMode::ABS:
		{
			return *Read(FetchAddress());
		}
		// Returns the absolute address with X offset
		case AddressMode::ABSX:
		{
			return *Read(FetchAddress());
		}
		// Returns the absolute address with Y offset
		case AddressMode::ABSY:
		{
			return *Read(FetchAddress());
		}
		// Pointer to actual address
		case AddressMode::IND:
		{
			return *Read(FetchAddress());
		}
		// Pointer to actual address with X Offset
		// Points to 0x00 to 0xFF (Page Zero)
		case AddressMode::INDX: 
		{
			return *Read(FetchAddress());
		}
		// Pointer to actual address with Y Offset
		// Probably Wrong. Very confused
		case AddressMode::INDY:
		{
			return *Read(FetchAddress());
		}
		default:
		{
			std::cout << "Addressing Mode is Not Implemented for FetchByte" << std::endl;
			return *Read(0x00);		// Just to pass the function return. WILL NOT BE CORRECT
		}
	}
}

uint16_t CPU::GetAddress(uint16_t& ptr)
{
	uint8_t lo = *Read(ptr++);
	uint8_t hi = *Read(ptr++);

	return (hi << 8) | lo;
}

uint16_t CPU::GetMirrorAddress(uint16_t address) const
{
	// System memory mirroring
	if (address >= MEMORY_START_ADDRESS && address <= MEMORY_MIRROR_END_ADDRESS)
		return address & MEMORY_END_ADDRESS;

	// PPU Registers
	if (address >= PPU_REGISTERS_START_ADDRESS && address <= PPU_REGISTERS_MIRROR_END_ADDRESS)
		return address & PPU_REGISTERS_END_ADDRESS;

	// OTHER

	return address;
}

bool CPU::CheckInterruptFlags()
{
	if (m_IF.RESET)
	{
		Reset();
		return true;
	}

	if (m_IF.NMI)
	{
		NMI();
		return true;
	}

	if (m_IF.IRQ)
	{
		IRQ();
		return true;
	}

	return false;
}

#pragma region Stack

void CPU::PushToStack(uint8_t value)
{
	if (m_SP + 1 > STACK_END_ADDRESS)
	{
		std::cout << "Stack Limited Reached!" << std::endl;
		return;
	}

	Write(m_SP++, value);
}

void CPU::PushToStackAddress(uint16_t value)
{
	uint8_t lo = value;
	uint8_t hi = (value >> 4);

	PushToStack(lo);
	PushToStack(hi);
}

uint8_t CPU::PopFromStack()
{
	return *Read(--m_SP);
}

uint16_t CPU::PopFromStackAddress()
{
	uint8_t lo = *Read(--m_SP);
	uint8_t hi = *Read(--m_SP);

	return (hi << 8) | lo;
}

#pragma endregion

#pragma region Op Codes

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
	uint8_t byte = FetchByte();
	
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

	m_PC = *Read(IRQ_INTERRUPT_ADDRESS);
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
	uint8_t& byte = FetchByte();
	Helper_Decrement(byte);
}

void CPU::OP_DEX()
{
	Helper_Decrement(m_X);
}

void CPU::OP_DEY()
{
	Helper_Decrement(m_Y);
}

void CPU::OP_EOR()
{
	uint8_t byte = FetchByte();
	m_A ^= byte;

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
}

void CPU::OP_INC()
{
	uint8_t& byte = FetchByte();
	Helper_Increment(byte);
}

void CPU::OP_INX()
{
	Helper_Increment(m_X);
}

void CPU::OP_INY()
{
	Helper_Increment(m_Y);
}

void CPU::OP_JMP()
{
	m_PC = FetchAddress();
}

void CPU::OP_JSR()
{
	PushToStackAddress(m_PC - 1);
	m_PC = FetchAddress();
}

void CPU::OP_LDA()
{
	Helper_Load(m_A);
}

void CPU::OP_LDX()
{
	Helper_Load(m_X);
}

void CPU::OP_LDY()
{
	Helper_Load(m_Y);
}

void CPU::OP_LSR()
{
	uint8_t& byte = FetchByte();

	m_F.C = byte & 0x01;
	byte >>= 1;

	m_F.Z = byte == 0;
	m_F.N = byte & 0x80;
}

void CPU::OP_NOP()
{
	m_PC++;
}

void CPU::OP_ORA()
{
	m_A |= FetchByte();

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
}

void CPU::OP_PHA()
{
	PushToStack(m_A);
}

void CPU::OP_PHP()
{
	PushToStack(m_F.Hex);
}

void CPU::OP_PLA()
{
	m_A = PopFromStack();

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
}

void CPU::OP_PLP()
{
	m_F.Hex = PopFromStack();
}

void CPU::OP_ROL()
{
	uint8_t& byte = FetchByte();

	m_F.C = byte & 0x80;

	byte <<= 1;
	byte |= m_F.C;

	m_F.Z = m_A == 0;
	m_F.N = byte & 0x80;
}

void CPU::OP_ROR()
{
	uint8_t& byte = FetchByte();

	m_F.C = byte & 0x01;

	byte >>= 1;
	byte |= (m_F.C << 7);

	m_F.Z = m_A == 0;
	m_F.N = byte & 0x80;
}

void CPU::OP_RTI()
{
	m_F.Hex = PopFromStack();
	m_PC = PopFromStack();
}

void CPU::OP_RTS()
{
	m_PC = PopFromStack();
}

void CPU::OP_SBC()
{
	uint8_t byte = FetchByte();
	uint8_t result = m_A - byte - (1 - m_F.C);

	// If Overflow
	if ((result & 0x80) != (m_A & 0x80))
	{
		m_F.C = 0;
		m_F.V = 1;
	}

	m_F.Z = result == 0;
	m_F.N = result & 0x80;

	m_A = result;
}

void CPU::OP_SEC()
{
	m_F.C = 1;
}

void CPU::OP_SED()
{
	m_F.D = 1;
}

void CPU::OP_SEI()
{
	m_F.I = 1;
}

void CPU::OP_STA()
{
	FetchByte() = m_A;
}

void CPU::OP_STX()
{
	FetchByte() = m_X;
}

void CPU::OP_STY()
{
	FetchByte() = m_Y;
}

void CPU::OP_TAX()
{
	Helper_TransferAccumulator(m_X);
}

void CPU::OP_TAY()
{
	Helper_TransferAccumulator(m_Y);
}

void CPU::OP_TSX()
{
	m_X = m_SP;

	m_F.Z = m_X == 0;
	m_F.N = m_X & 0x80;
}

void CPU::OP_TXA()
{
	m_A = m_X;

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
}

void CPU::OP_TXS()
{
	m_SP = m_X;
}

void CPU::OP_TYA()
{
	m_A = m_Y;

	m_F.Z = m_A == 0;
	m_F.N = m_A & 0x80;
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

void CPU::Helper_Increment(uint8_t& value)
{
	value++;

	m_F.Z = value == 0;
	m_F.N = value & 0x80;
}

void CPU::Helper_Load(uint8_t& value)
{
	value = FetchByte();

	m_F.Z = value == 0;
	m_F.N = value & 0x80;
}

void CPU::Helper_TransferAccumulator(uint8_t& value)
{
	value = m_A;

	m_F.Z = value == 0;
	m_F.N = value & 0x80;
}

#pragma endregion
