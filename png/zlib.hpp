
#ifndef ZLIB_HPP
# define ZLIB_HPP
# include "uint.hpp"
# include "BitStream.hpp"

class ZLIB
{
	public:
		uint8	CMF;
		uint8	FLG;

		const uint8	*Data;
		uint32		Length;

		uint32	DICTID;
		uint32	ADLER32;

		ZLIB(BitStream & bits);

		BitStream	ToBitStream() const;

		std::string	ToString() const;
};

#endif
