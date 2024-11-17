
#include "uint.hpp"



std::string	uint_Chr(uint32 num)
{
	std::stringstream ss;

	uint8 * ptr = (uint8 *)&num;
	for (int i = 0; i < 4; i++)
	{
		ss << ptr[i];
	}

	return (ss.str());
}
std::string	uint_Hex(uint32 num)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex;

	uint8 * ptr = (uint8 *)&num;
	for (int i = 0; i < 4; i++)
	{
		if (i != 0)
			ss << " ";
		ss << std::setfill('0') << std::setw(2) << (uint16)(ptr[i]);
	}

	return (ss.str());
}



std::string	uint_Hex(uint64 num)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex;

	uint8 * ptr = (uint8 *)&num;
	for (int i = 0; i < 8; i++)
	{
		if (i != 0)
			ss << " ";
		ss << std::setfill('0') << std::setw(2) << (uint16)(ptr[i]);
	}

	return (ss.str());
}
