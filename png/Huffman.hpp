
#ifndef HUFFMAN_HPP
# define HUFFMAN_HPP
# include "uint.hpp"
# include "BitStream.hpp"

class HuffmanTree
{
	private:
		static uint8	get_max_BitLen(uint8 * codeBitLen, uint32 len);
		static void		get_BitLen_Count(uint32 *codeCount, uint8 * codeBitLen, uint32 len);
		static void		first_code_for_BitLen(uint32 *firstCodes, uint32 *codeCount, uint32 len);
		static void		assing_HuffmanCode(uint32 *assignCodes, uint32 *firstCodes, uint8 *codeBitLen, uint32 len);

	public:
		uint32	Len;
		uint8	*BitLens;
		uint32	*Codes;

	public:
		HuffmanTree(uint8 * codeBitLen, uint32 len);
		~HuffmanTree();

		uint32	decode(BitStream & bits);
};

#endif
