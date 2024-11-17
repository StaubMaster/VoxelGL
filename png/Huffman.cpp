
#include "Huffman.hpp"

uint8	HuffmanTree::get_max_BitLen(uint8 * codeBitLen, uint32 len)
{
	uint8	maxBit = 0;
	for (uint32 i = 0; i < len; i++)
	{
		if (maxBit < codeBitLen[i])
			maxBit = codeBitLen[i];
	}
	return (maxBit);
}
void	HuffmanTree::get_BitLen_Count(uint32 *codeCount, uint8 * codeBitLen, uint32 len)
{
	for (uint32 i = 0; i < len; i++)
	{
		codeCount[codeBitLen[i]]++;
	}
}
void	HuffmanTree::first_code_for_BitLen(uint32 *firstCodes, uint32 *codeCount, uint32 len)
{
	uint32	code = 0;
	for (uint32 i = 0; i < len; i++)
	{
		code = (code + codeCount[i]) << 1;
		if (codeCount[i + 1] > 0)
			firstCodes[i + 1] = code;
	}
}
void	HuffmanTree::assing_HuffmanCode(uint32 *assignCodes, uint32 *firstCodes, uint8 *codeBitLen, uint32 len)
{
	for (uint32 i = 0; i < len; i++)
	{
		if (codeBitLen[i] != 0)
			assignCodes[i] = firstCodes[codeBitLen[i]]++;
	}
}

HuffmanTree::HuffmanTree(uint8 * codeBitLen, uint32 len)
{
	static uint32 yes = 1;

	Len = len;
	BitLens = codeBitLen;
	Codes = new uint32[Len];
	for (uint32 i = 0; i < Len; i++)
		Codes[i] = 0;

	uint32	maxBitLen = get_max_BitLen(BitLens, Len);
	if (yes == 0)
	{
		std::cout << "maxLen " << maxBitLen << "\n";
		std::cout << "\n";
		for (uint32 i = 0; i < Len; i++)
		{
			if (codeBitLen[i] != 0)
				std::cout << "codeBitLen [" << std::setw(3) << i << "] " << (uint16)codeBitLen[i] << "\n";
		}
		std::cout << "\n";
	}

	uint32 * codeCount = new uint32[maxBitLen + 1];
	uint32 * firstCodes = new uint32[maxBitLen + 1];
	for (uint32 i = 0; i <= maxBitLen; i++)
	{
		codeCount[i] = 0;
		firstCodes[i] = 0;
	}

	get_BitLen_Count(codeCount, BitLens, Len);
	codeCount[0] = 0;
	if (yes == 0)
	{
		for (uint32 i = 0; i <= maxBitLen; i++)
			std::cout << "count [" << std::setw(3) << i << "] " << codeCount[i] << "\n";
		std::cout << "\n";
	}

	first_code_for_BitLen(firstCodes, codeCount, maxBitLen);
	if (yes == 0)
	{
		for (uint32 i = 0; i <= maxBitLen; i++)
			std::cout << "first [" << std::setw(3) << i << "] " << uint_Bit(firstCodes[i], i) << "\n";
		std::cout << "\n";
	}

	assing_HuffmanCode(Codes, firstCodes, BitLens, Len);
	if (yes == 0)
	{
		for (uint32 i = 0; i < Len; i++)
		{
			if (codeBitLen[i] != 0)
				std::cout << "assign [" << std::setw(3) << i << "] " << uint_Bit(Codes[i], codeBitLen[i]) << "\n";
		}
		std::cout << "\n";
	}

	yes = 1;

	delete [] codeCount;
	delete [] firstCodes;
}
HuffmanTree::~HuffmanTree()
{
	delete [] Codes;
}

uint32	HuffmanTree::decode(BitStream & bits)
{
	static uint32	yes = 0;

/*
code [ 0]    01111 =?=    00110
code [ 3]   011110 =?=   011100
code [ 4]    01111 =?=    00111
code [ 5]   011110 =?=   011101
code [ 6]   011110 =?=   011110
code [ 0]    01101 =?=    00110
code [ 3]   011010 =?=   011100
code [ 4]    01101 =?=    00111
code [ 5]   011010 =?=   011101
code [ 6]   011010 =?=   011110
code [ 7]    01101 =?=    01000
code [ 8]    01101 =?=    01001
code [ 9]    01101 =?=    01010
code [10]    01101 =?=    01011
code [11]    01101 =?=    01100
code [12]     0110 =?=     0000

[ 0]    01111 =!=    00110
[ 3]   011110 =!=   011100
[ 4]    01111 =!=    00111
[ 5]   011110 =!=   011101
[ 6]   011110 =!=   011110
[ 0]    01101 =!=    00110
[ 3]   011010 =!=   011100
[ 4]    01101 =!=    00111
[ 5]   011010 =!=   011101
[ 6]   011010 =!=   011110
[ 7]    01101 =!=    01000
[ 8]    01101 =!=    01001
[ 9]    01101 =!=    01010
[10]    01101 =!=    01011
[11]    01101 =!=    01100
[12]     0110 =!=     0000
*/

	for (uint32 i = 0; i < Len; i++)
	{
		if (BitLens[i] != 0)
		{
			uint32 code = bits.bits(BitLens[i], BITSTREAM_STAY | BITSTREAM_REV);

			if (yes < 16)
			{
				//std::cout << "[" << std::setw(2) << i << "] " << std::setw(8) << uint_Bit(code, BitLens[i]) << " =!= " << std::setw(8) << uint_Bit(Codes[i], BitLens[i]) << "\n";
				yes++;
			}

			if (Codes[i] == code)
			{
				bits.Index += BitLens[i];
				return (i);
			}
		}
	}

	return (0);
}
