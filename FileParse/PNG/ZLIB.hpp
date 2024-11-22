
#ifndef ZLIB_HPP
# define ZLIB_HPP
# include "../DebugManager.hpp"
# include "../uint.hpp"
# include "../BitStream.hpp"
# include "../DataStream.hpp"

# include "DEFLATE.hpp"

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

		static void	decompress(BitStream & bits, DataStream & data);
};

#endif
