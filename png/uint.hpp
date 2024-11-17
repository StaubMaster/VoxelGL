
#ifndef UINT_HPP
# define UINT_HPP
# include <iostream>
# include <iomanip>
# include <sstream>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

//	uint32
std::string	uint_Chr(uint32 num);
std::string	uint_Hex(uint32 num);

//	uint64
std::string	uint_Hex(uint64 num);

#endif
