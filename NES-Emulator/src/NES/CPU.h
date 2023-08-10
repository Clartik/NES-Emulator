#pragma once

#include <stdint.h>
#include <map>
#include <functional>
#include <string>

#include "Bus.h"

const unsigned int MEMORY_SIZE = 2048;

const unsigned int MEMORY_START_ADDRESS = 0x0000;
const unsigned int MEMORY_END_ADDRESS = 0x07FF;
const unsigned int MEMORY_MIRROR_END_ADDRESS = 0x1FFFF;

// Stack is 256 to 511 (0x0100 - 0x01FF)
const unsigned int STACK_START_ADDRESS = 0x0100;
const unsigned int STACK_END_ADDRESS = 0x01FF;

const uint16_t PPU_REGISTERS_START_ADDRESS = 0x2000;
const uint16_t PPU_REGISTERS_END_ADDRESS = 0x2007;
const uint16_t PPU_REGISTERS_MIRROR_END_ADDRESS = 0x3FFF;

const unsigned int PC_START_ADDRESS = 0xFFFC;

const uint16_t NMI_INTERRUPT_ADDRESS = 0xFFFA;
const uint16_t RESET_INTERRUPT_ADDRESS = 0xFFFC;
const uint16_t IRQ_INTERRUPT_ADDRESS = 0xFFFE;

#define BIND_OPCODE_FN(x) std::bind(&CPU::x, this)

class CPU
{
private:
	using OpCodeFn = std::function<void()>;
public:
	CPU(Bus* bus);
	~CPU();

	// Always check if it is null
	uint8_t* Read(uint16_t address);
	void Write(uint16_t address, uint8_t data);
	void Write(uint16_t address, uint8_t* data, unsigned int size);

	void Reset();
	void NMI();
	void IRQ();

	bool Cycle();
private:
	// Fetches the address needed for certain instructions
	uint16_t FetchAddress();
	// Fetches the byte needed for certain instructions
	uint8_t& FetchByte();

	uint16_t GetAddress(uint16_t& ptr);
	uint16_t GetMirrorAddress(uint16_t address) const;

	bool CheckInterruptFlags();

	#pragma region Stack

	void PushToStack(uint8_t value);
	void PushToStackAddress(uint16_t value);

	uint8_t PopFromStack();
	uint16_t PopFromStackAddress();

	#pragma endregion

	#pragma region Op Codes

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
	void OP_DEX();
	void OP_DEY();
	void OP_EOR();
	void OP_INC();
	void OP_INX();
	void OP_INY();
	void OP_JMP();
	void OP_JSR();
	void OP_LDA();
	void OP_LDX();
	void OP_LDY();
	void OP_LSR();
	void OP_NOP();
	void OP_ORA();
	void OP_PHA();
	void OP_PHP();
	void OP_PLA();
	void OP_PLP();
	void OP_ROL();
	void OP_ROR();
	void OP_RTI();
	void OP_RTS();
	void OP_SBC();
	void OP_SEC();
	void OP_SED();
	void OP_SEI();
	void OP_STA();
	void OP_STX();
	void OP_STY();
	void OP_TAX();
	void OP_TAY();
	void OP_TSX();
	void OP_TXA();
	void OP_TXS();
	void OP_TYA();

	// Implements Generic Instructions for instructions that change very little
	void Helper_BranchIf(bool condition);
	void Helper_Compare(uint8_t value);
	void Helper_Decrement(uint8_t& value);
	void Helper_Increment(uint8_t& value);
	void Helper_Load(uint8_t& value);
	void Helper_TransferAccumulator(uint8_t& value);

	#pragma endregion
private:
	// Registers:
	// Acuumlator, X-Index, Y-Index, Stack Pointer
	uint8_t m_A, m_X, m_Y, m_SP;
	uint16_t m_PC;

	union Flags
	{
		struct
		{
			uint8_t Z : 1;		// Zero
			uint8_t I : 1;		// Interrupt Disable
			uint8_t D : 1;		// Decimal
			uint8_t B : 1;		// Break
			uint8_t R : 1;		// Reserved (Not Used)
			uint8_t C : 1;		// Carry
			uint8_t V : 1;		// Overflow
			uint8_t N : 1;		// Negative
		};

		uint8_t Hex;
	};
	Flags m_F;

	struct InterruptFlags
	{
		uint8_t RESET : 1;
		uint8_t NMI : 1;
		uint8_t IRQ : 1;
	};
	InterruptFlags m_IF;

	unsigned int m_Cycles = 0;

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
		std::string Name;
		OpCodeFn Func;
		AddressMode AddressMode;
		uint8_t Cycles;
		bool CanAddAdditionalCycles;		// Needed because certain instructions add additional cycles
	};

	// 1 Byte is taken up instruction number, Instruction specifies the remaining bytes needed
	// 2 Byte is taken up for interrupts
	std::map<uint8_t, Instruction> m_Instructions;
	Instruction* m_CurrentInstruction;

	Bus* m_Bus = nullptr;
};