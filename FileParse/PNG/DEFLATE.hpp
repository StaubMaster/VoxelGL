
#ifndef DEFLATE_HPP
# define DEFLATE_HPP
# include "../DebugManager.hpp"
# include "../uint.hpp"
# include "../BitStream.hpp"
# include "../DataStream.hpp"

# include "Huffman.hpp"
# include "PNG_Image.hpp"

class DEFLATE
{
	public:
		static uint8 *	dynamic_Huffman(BitStream & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN);
		static void		decode_Huffman(BitStream & bits, HuffmanTree & literal, HuffmanTree & distance, DataStream & data);

	public:
		static void	Block_direct(BitStream & bits, DataStream & data);
		static void	Block_static(BitStream & bits, DataStream & data);
		static void	Block_dynamic(BitStream & bits, DataStream & data);
		static void	Blocks(BitStream & bits, DataStream & data);
};

#endif
