
#include "ZLIB.hpp"

ZLIB::ZLIB(BitStream & bits)
{
	CMF = bits.byte8();
	FLG = bits.byte8();

	if ((FLG >> 5) & 0b1)
	{
		DICTID = bits.byte32();
		Length = bits.Len - 10;
	}
	else
	{
		DICTID = 0;
		Length = bits.Len - 6;
	}

	Data = bits.DataAtIndex();
	ADLER32 = bits.byte32(Length);
}

BitStream	ZLIB::ToBitStream() const
{
	return (BitStream(Data, Length));
}



std::string	ZLIB::ToString() const
{
	uint8	CM = (CMF >> 0) & 0b1111;
	uint8	CINFO = (CMF >> 4) & 0b1111;
	std::cout << "CMF   : " << uint_Bit(CMF) << "\n";
	std::cout << "CM    : "    << uint_Bit(CM, 3) << "\n";
	std::cout << "CINFO : " << uint_Bit(CINFO, 3) << "\n";

	uint8	FCHECK = (FLG >> 0) & 0b11111;
	uint8	FDICT = (FLG >> 5) & 0b1;
	uint8	FLEVEL = (FLG >> 6) & 0b11;
	std::cout << "FLG    : " << uint_Bit(FLG) << "\n";
	std::cout << "FCHECK : "    << uint_Bit(FCHECK, 4) << "\n";
	std::cout << "FDICT  : " << uint_Bit(FDICT, 0) << "\n";
	std::cout << "FLEVEL : " << uint_Bit(FLEVEL, 1) << "\n";

	std::cout << "DICTID  : " << uint_Hex(DICTID) << "\n";
	std::cout << "ADLER32 : " << uint_Hex(ADLER32) << "\n";

	std::cout << "Length : " << Length << "\n";

	return (std::string());
}
