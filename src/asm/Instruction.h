/*
 * Author: doe300
 *
 * See the file "LICENSE" for the full license governing this code.
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../Bitfield.h"
#include "CompilationError.h"
#include "OpCodes.h"

#include <string>

namespace vc4c
{

	namespace qpu_asm
	{

		class Instruction : protected Bitfield<uint64_t>
		{
		public:

			Instruction();
			explicit Instruction(uint64_t code);
			virtual ~Instruction();

			virtual std::string toASMString() const = 0;
			virtual bool isValidInstruction() const = 0;

			uint64_t toBinaryCode() const;
			std::string toHexString(bool withAssemblerCode) const;

			static Instruction* readFromBinary(uint64_t binary);

			BITFIELD_ENTRY(Sig, Signaling, 60, Quadruple)
			BITFIELD_ENTRY(WriteSwap, WriteSwap, 44, Bit)
			BITFIELD_ENTRY(AddOut, Address, 38, Sextuple)
			BITFIELD_ENTRY(MulOut, Address, 32, Sextuple)

		protected:

			static std::string toInputRegister(InputMutex mutex, Address regA, Address regB, bool hasImmediate = false);
			static std::string toOutputRegister(bool regFileA, Address reg);
			static std::string toExtrasString(Signaling sig, ConditionCode cond = COND_ALWAYS, SetFlag flags = SetFlag::DONT_SET, Unpack unpack = UNPACK_NOP, Pack pack = PACK_NOP, bool usesOutputA = true, bool usesInputAOrR4 = true);
		};

		std::string toHexString(uint64_t code);
	} // namespace qpu_asm
} // namespace vc4c

#endif /* INSTRUCTION_H */

