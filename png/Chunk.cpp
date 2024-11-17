
#include "Chunk.hpp"

const char * knownChunkTypes[] = {
	"IHDR",
	"IDAT",
	"IEND",
};

uint8	Chunk::knownTypeIndex(uint32 type)
{
	const uint8 * p = (const uint8 *)&type;
	const uint8 * k;

	for (uint8 i = 0; i < 3; i++)
	{
		k = (const uint8 *)knownChunkTypes[i];
		if (k[0] == p[0] && 
			k[1] == p[1] &&
			k[2] == p[2] &&
			k[3] == p[3])
		{
			return (i);
		}
	}
	return (0xFF);
}





Chunk::Chunk(BitStream & bits) :
	Length(bits.byte32(BITSTREAM_REV)),
	Type(bits.byte32()),
	Data(bits.DataAtIndex()),
	CRC(bits.byte32(0, Length)),
	typeIndex(knownTypeIndex(Type))
{

}


BitStream	Chunk::ToBitStream() const
{
	return (BitStream(Data, Length));
}


std::string	Chunk::ToString() const
{
	std::stringstream ss;

	ss << "Length: " << Length << "\n";

	ss << "Type: " << uint_Chr(Type);
	ss << " (";
	if (typeIndex == 0xFF)
		ss << "\e[31mUnknown\e[m";
	else
		ss << "\e[32mKnown\e[m";
	ss << ")\n";

	ss << "CRC: " << uint_Hex(CRC) << "\n";

	return (ss.str());
}

bool	Chunk::isIHRD() const
{
	return (typeIndex == 0);
}
bool	Chunk::isIDAT() const
{
	return (typeIndex == 1);
}
bool	Chunk::isIEND() const
{
	return (typeIndex == 2);
}
