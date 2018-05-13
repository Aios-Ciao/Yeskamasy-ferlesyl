#pragma once
#include <list>

class Opecode
{
public:
	using tCodeBytes = std::list<uint8_t>;
	using tCodeLength = tCodeBytes::size_type;
};

