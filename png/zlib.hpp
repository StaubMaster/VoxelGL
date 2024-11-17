
#ifndef ZLIB_HPP
# define ZLIB_HPP
# include "uint.hpp"
# include "BitStream.hpp"

class zlib
{
	public:
		const uint8	CMF;
		const uint8	FLG;

		const uint8	*Data;

		const uint32	DICTID;
		const uint32	ADLER32;

		zlib(BitStream & bits);

		std::string	ToString() const;
};

#endif
