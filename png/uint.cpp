
#include "uint.hpp"

std::string	uint_Bit(uint8 val, uint8 num)
{
	num = num & 0b111;
	std::stringstream ss;

	for (uint8 i = num; i <= num; i--)
	{
		if ((val >> i) & 1)
			ss << "1";
		else
			ss << "0";
	}

	return (ss.str());
}
std::string	uint_Chr(uint8 val)
{
	std::stringstream ss;

	ss << val;

	return (ss.str());
}
std::string	uint_Hex(uint8 val)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex;

	ss << std::setfill('0') << std::setw(2) << (uint16)(val);

	return (ss.str());
}


std::string	uint_Bit(uint32 val, uint8 num)
{
	num = num & 0b11111;
	std::stringstream ss;

	for (uint8 i = num; i <= num; i--)
	{
		if ((num - i) == 8)
			ss << " ";

		if ((val >> i) & 1)
			ss << "1";
		else
			ss << "0";
	}

	return (ss.str());
}
std::string	uint_Chr(uint32 val)
{
	std::stringstream ss;

	uint8 * ptr = (uint8 *)&val;
	for (int i = 0; i < 4; i++)
	{
		ss << ptr[i];
	}

	return (ss.str());
}
std::string	uint_Hex(uint32 val)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex;

	uint8 * ptr = (uint8 *)&val;
	for (int i = 0; i < 4; i++)
	{
		if (i != 0)
			ss << " ";
		ss << std::setfill('0') << std::setw(2) << (uint16)(ptr[i]);
	}

	return (ss.str());
}



std::string	uint_Hex(uint64 val)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex;

	uint8 * ptr = (uint8 *)&val;
	for (int i = 0; i < 8; i++)
	{
		if (i != 0)
			ss << " ";
		ss << std::setfill('0') << std::setw(2) << (uint16)(ptr[i]);
	}

	return (ss.str());
}
