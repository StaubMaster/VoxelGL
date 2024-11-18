
#include "BitStream.hpp"

BitStream::BitStream(const uint8 * ptr, uint32 len) :
	Data(ptr),
	Len(len),
	Index(0)
{

}

BitStream::BitStream(const std::string & str) :
	Data((const uint8 *)str.c_str()),
	Len(str.size()),
	Index(0)
{
	
}



uint32	BitStream::get_BitIndex() const
{
	return (Index & 0b111);
}
/*void	BitStream::set_BitIndex(uint32 idx)
{
	Index = ((Index | 0b111) ^ 0b111) | (idx & 0b111);
}*/
uint32	BitStream::get_ByteIndex() const
{
	return (Index >> 3);
}
/*void	BitStream::set_ByteIndex(uint32 idx)
{
	Index = (Index & 0b111) | (idx << 3);
}*/
void	BitStream::set_Index(uint32 bits, uint32 bytes)
{
	Index = (bytes << 3) | (bits & 0b111);
}



uint32	BitStream::bits(uint32 num, uint8 extra, uint32 skipBytes, uint32 skipBits)
{
	if (num == 0)
		return (0);
	num--;
	num = num & 0b11111;

	uint32	n = 0;
	uint32	bit;

	uint32	bitI;
	uint32	byteI;
	uint32	idx = Index;

	uint32	j;
	for (uint32 i = 0; i <= num; i++)
	{
		j = num - i;

		bitI = get_BitIndex();
		byteI = get_ByteIndex();

		if (byteI > Len)
		{
			std::cout << "here 1\n";
			throw LenReachedException();
		}

		bit = (Data[byteI] >> bitI) & 1;

		if (extra & BITSTREAM_REV)
			n = n | (bit << j);
		else
			n = n | (bit << i);

		Index++;
	}

	if ((extra & BITSTREAM_STAY))
		Index = idx;

	if (get_ByteIndex() > Len)
	{
		std::cout << "here 2\n";
		throw LenReachedException();
	}

	return (n);
	(void)j;
	(void)skipBits;
	(void)skipBytes;
}



/// @brief Gets the next 8 Byte-aligned Bits
/// @param skipBytes Bytes to skip (until read)
/// @param move Weather the the Index should be moved (by 1 Bytes)
/// @return The 1 Bytes read
uint8	BitStream::byte8(uint8 extra, uint32 skipBytes)
{
	const uint8 * idx8 = Data + get_ByteIndex() + skipBytes;

	uint8 n = 0;
	if (extra & BITSTREAM_REV)
	{
		n = (n << 8) | idx8[0];
	}
	else
	{
		n = (n << 8) | idx8[0];
	}

	if (!(extra & BITSTREAM_STAY))
		moveIndex(1 + skipBytes);
	return (n);
}
/// @brief Gets the next 32 Byte-aligned Bits
/// @param skipBytes Bytes to skip (until read)
/// @param move Weather the the Index should be moved (by 4 Bytes)
/// @return The 4 Bytes read
uint32	BitStream::byte32(uint8 extra, uint32 skipBytes)
{
	const uint8 * idx8 = Data + get_ByteIndex() + skipBytes;

	uint32 n = 0;
	if (extra & BITSTREAM_REV)
	{
		n = (n << 8) | idx8[0];
		n = (n << 8) | idx8[1];
		n = (n << 8) | idx8[2];
		n = (n << 8) | idx8[3];
	}
	else
	{
		n = (n << 8) | idx8[3];
		n = (n << 8) | idx8[2];
		n = (n << 8) | idx8[1];
		n = (n << 8) | idx8[0];
	}

	if (!(extra & BITSTREAM_STAY))
		moveIndex(4 + skipBytes);
	return (n);
}
/// @brief Gets the next 64 Byte-aligned Bits
/// @param skipBytes Bytes to skip (until read)
/// @param move Weather the the Index should be moved (by 8 Bytes)
/// @return The 8 Bytes read
uint64	BitStream::byte64(uint8 extra, uint32 skipBytes)
{
	const uint8 * idx8 = Data + get_ByteIndex() + skipBytes;

	uint64 n = 0;
	if (extra & BITSTREAM_REV)
	{
		n = (n << 8) | idx8[0];
		n = (n << 8) | idx8[1];
		n = (n << 8) | idx8[2];
		n = (n << 8) | idx8[3];
		n = (n << 8) | idx8[4];
		n = (n << 8) | idx8[5];
		n = (n << 8) | idx8[6];
		n = (n << 8) | idx8[7];
	}
	else
	{
		n = (n << 8) | idx8[7];
		n = (n << 8) | idx8[6];
		n = (n << 8) | idx8[5];
		n = (n << 8) | idx8[4];
		n = (n << 8) | idx8[3];
		n = (n << 8) | idx8[2];
		n = (n << 8) | idx8[1];
		n = (n << 8) | idx8[0];
	}

	if (!(extra & BITSTREAM_STAY))
		moveIndex(8 + skipBytes);
	return (n);
}



const uint8 *	BitStream::DataAtIndex(uint32 skipBytes) const
{
	return Data + get_ByteIndex() + skipBytes;
}
void	BitStream::moveIndex(uint32 skip)
{
	uint32	idx = get_ByteIndex();
	std::cout << "\e[34mskip Byte\e[m\n";
	if (get_BitIndex() != 0)
		idx++;
	idx += skip;
	if (idx > Len)
		throw LenReachedException();
	set_Index(0, idx);
}


const char * BitStream::LenReachedException::what() const throw() { return "BitStream Length reached"; }
