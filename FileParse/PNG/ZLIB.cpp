
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
	std::ostream & os = DebugManager::GetOut();

	uint8	CM = (CMF >> 0) & 0b1111;
	uint8	CINFO = (CMF >> 4) & 0b1111;
	os << "CMF   : " << uint_Bit(CMF) << "\n";
	os << "CM    : "    << uint_Bit(CM, 3) << "\n";
	os << "CINFO : " << uint_Bit(CINFO, 3) << "\n";

	uint8	FCHECK = (FLG >> 0) & 0b11111;
	uint8	FDICT = (FLG >> 5) & 0b1;
	uint8	FLEVEL = (FLG >> 6) & 0b11;
	os << "FLG    : " << uint_Bit(FLG) << "\n";
	os << "FCHECK : "    << uint_Bit(FCHECK, 4) << "\n";
	os << "FDICT  : " << uint_Bit(FDICT, 0) << "\n";
	os << "FLEVEL : " << uint_Bit(FLEVEL, 1) << "\n";

	os << "DICTID  : " << uint_Hex(DICTID) << "\n";
	os << "ADLER32 : " << uint_Hex(ADLER32) << "\n";

	os << "Length : " << Length << "\n";

	return (std::string());
}


void	ZLIB::decompress(BitStream & bits, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mzlib ...\e[m\n";

	ZLIB zlib(bits);
	zlib.ToString();
	os << "\n";

	BitStream deflate = zlib.ToBitStream();
	DEFLATE::Blocks(deflate, data);

	os << "\e[34mzlib done\e[m\n";
}
