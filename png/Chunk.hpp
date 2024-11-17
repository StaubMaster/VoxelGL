
#ifndef PNG_CHUNKS_HPP
# define PNG_CHUNKS_HPP
# include "uint.hpp"
# include "BitStream.hpp"

class Chunk
{
	static uint8	knownTypeIndex(uint32 type);

	public:
		const uint32	Length;
		const uint32	Type;
		const uint8 *	Data;
		const uint32	CRC;

		const uint8		typeIndex;

		Chunk(BitStream & bits);

		BitStream	ToBitStream() const;

		std::string	ToString() const;

		bool		isIHRD() const;
		bool		isIDAT() const;
		bool		isIEND() const;
};

#endif
