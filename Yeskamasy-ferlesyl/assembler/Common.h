#pragma once
#include <cstdint>
#include <string>

namespace lk
{
	using tAddressHalf = uint16_t;
	using tAddressFull = uint32_t;

	using tModuleID = uint16_t;				/// モジュール番号(0：main 1～255：周辺)
	using tModuleName = std::string;
};

