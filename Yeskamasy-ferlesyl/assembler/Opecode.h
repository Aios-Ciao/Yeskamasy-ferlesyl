#pragma once
#include <list>
#include "Instruction.h"

class Opecode : public Instruction
{
public:
	using tCodeBytes = std::list<uint8_t>;
	using tCodeLength = tCodeBytes::size_type;

	virtual bool Encode(Parameter::tParamList &prm, Opecode::tCodeBytes &bytes) { return false; };
};

