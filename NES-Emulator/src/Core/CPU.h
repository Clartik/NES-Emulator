#pragma once

#include <stdint.h>
#include <map>
#include <functional>

const unsigned int MEMORY_SIZE = 2048;

// Stack is 256 to 511 (0x0100 - 0x01FF)
const unsigned int STACK_START_ADDRESS = 0x0100;
const unsigned int PC_START_ADDRESS = 0xFFFC;
const unsigned int IRQ_INTERRUPT_ADDRESS = 0xFFFE;

class CPU
{
private:
	using OpCodeFn = std::function<void()>;
public:
	CPU();
	~CPU();

	// Get 8-bit Byte
	inline uint8_t& Read(uint16_t& address) { return m_RAM[address++]; }
	inline void Write(uint16_t address, uint8_t data) { m_RAM[address] = data; }
	void Write(uint16_t address, uint8_t* data, unsigned int size);

	void Reset();
private:
	void Cycle();

	// Fetches the memory needed for certain instructions
	uint8_t& FetchByte();
	uint16_t GetAddress(uint16_t& ptr);

	// Decided to implement stack by hand for "F U N"
	#pragma region Stack

	void PushToStack(uint8_t value);
	void PushToStack(uint16_t value);

	uint8_t PopFromStack();
	uint16_t PopFromStackAddress();

#pragma endregion

	#pragma region OPCodes

	void OP_ADC();
	void OP_AND();
	void OP_ASL();
	void OP_BCC();
	void OP_BCS();
	void OP_BEQ();
	void OP_BIT();
	void OP_BMI();
	void OP_BNE();
	void OP_BPL();
	void OP_BRK();
	void OP_BVC();
	void OP_BVS();
	void OP_CLC();
	void OP_CLD();
	void OP_CLI();
	void OP_CLV();
	void OP_CMP();
	void OP_CPX();
	void OP_CPY();
	void OP_DEC();

	// Implements Generic Instructions for instructions that change very little
	void Helper_BranchIf(bool condition);
	void Helper_Compare(uint8_t value);
	void Helper_Decrement(uint8_t& value);

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
		NONE = 0,
		IMP, IMM,
		ZP, ZPX, ZPY,
		ABS, ABSX, ABSY,
		IND, INDX, INDY,
		ACC, REL
	};

	struct Instruction
	{
		OpCodeFn Func;
		int Cycles;
		AddressMode AddressMode;
		bool CanIncreaseCycles;				// Needed because Certain instructions increment cycles
	};

	std::map<uint8_t, Instruction> m_Instructions;
	Instruction* m_CurrentInstruction;
};