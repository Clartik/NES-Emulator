#pragma once

#include <stdint.h>
#include <map>

const unsigned int MEMORY_SIZE = 2048;

// Stack is 256 to 511 (0x0100 - 0x01FF)
const unsigned int STACK_START_ADDRESS = 0x0100;
const unsigned int PC_START_ADDRESS = 0xFFFC;

class CPU
{
public:
	CPU();
	~CPU();

	// Get Byte
	inline uint8_t Read(uint8_t address) const { return m_RAM[address]; }
	inline void Write(uint8_t address, uint8_t data) { m_RAM[address] = data; }
	void Write(uint8_t address, uint8_t* data, unsigned int size);

	void Reset();
private:
	void Cycle();
	uint16_t FetchOPCode();
	void DecodeAndExecute(uint16_t instruction);

	uint16_t FetchByte();
	uint16_t GetAddress(uint16_t& ptr);

	#pragma region OPCodes

	void OP_ADC();
	void OP_AND();
	void OP_ASL();
	void OP_BCC();
	void OP_BCS(); 

	#pragma endregion
private:
	// Acuumlator, X-Index, Y-Index, Stack Pointer
	uint8_t m_A, m_X, m_Y, m_SP;
	uint16_t m_PC;

	union Flags
	{
		struct
		{
			uint8_t N : 1;		// Negative
			uint8_t V : 1;		// Overflow
			uint8_t R : 1;		// Reserved (Not Used)
			uint8_t B : 1;		// Break
			uint8_t D : 1;		// Decimal
			uint8_t I : 1;		// Interrupt Disable
			uint8_t Z : 1;		// Zero
			uint8_t C : 1;		// Carry
		};

		uint8_t Hex;
	};

	Flags m_F;

	uint8_t m_RAM[MEMORY_SIZE];

	unsigned int m_Cycles;

	enum class AddressMode
	{
		IMP = 0, IMM,
		ZP, ZPX, ZPY,
		ABS, ABSX, ABSY,
		IND, INDX, INDY,
		ACC, REL
	};

	struct Instruction
	{
		int Cycles;
		AddressMode AddressMode;
		bool CanIncreaseCycles;
	};

	std::map<uint16_t, Instruction> m_Instructions;
	Instruction* m_CurrentInstruction;
};