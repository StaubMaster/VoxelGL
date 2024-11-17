
#ifndef UINT_HPP
# define UINT_HPP
# include <iostream>
# include <iomanip>
# include <sstream>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

//	uint8
std::string	uint_Bit(uint8 val, uint8 num = 7);
std::string	uint_Chr(uint8 val);
std::string	uint_Hex(uint8 val);

//	uint32
std::string	uint_Bit(uint32 val, uint8 num = 31);
std::string	uint_Chr(uint32 val);
std::string	uint_Hex(uint32 val);

//	uint64
std::string	uint_Hex(uint64 val);

#endif
