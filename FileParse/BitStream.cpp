
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


uint32	reverse(uint32 bits)
{
	bits = ((bits & 0xFFFF0000) >> 16) | ((bits & 0x0000FFFF) << 16);
	bits = ((bits & 0xFF00FF00) >> 8) | ((bits & 0x00FF00FF) << 8);
	bits = ((bits & 0xF0F0F0F0) >> 4) | ((bits & 0x0F0F0F0F) << 4);
	bits = ((bits & 0xCCCCCCCC) >> 2) | ((bits & 0x33333333) << 2);
	bits = ((bits & 0xAAAAAAAA) >> 1) | ((bits & 0x55555555) << 1);
	return (bits);
}

uint32	BitStream::bits(uint32 num, uint8 extra)
{
	if (num == 0)
		return (0);
	num = ((num - 1) & 0b11111) + 1;
	uint32	mun = 32 - num;

	uint32	bitI = get_BitIndex();
	uint32	byteI = get_ByteIndex();

	uint32 sum;
	if (bitI == 0)
	{
		sum =
			(((uint32)Data[byteI + 0]) >> (bitI)) |
			(((uint32)Data[byteI + 1]) << (8 - bitI)) |
			(((uint32)Data[byteI + 2]) << (16 - bitI)) |
			(((uint32)Data[byteI + 3]) << (24 - bitI));
	}
	else
	{
		sum =
			(((uint32)Data[byteI + 0]) >> (bitI)) |
			(((uint32)Data[byteI + 1]) << (8 - bitI)) |
			(((uint32)Data[byteI + 2]) << (16 - bitI)) |
			(((uint32)Data[byteI + 3]) << (24 - bitI)) |
			(((uint32)Data[byteI + 4]) << (32 - bitI));
	}

	if ((extra & BITSTREAM_REV) != 0)
		sum = (reverse(sum) >> mun);
	sum = sum & (0xFFFFFFFF >> mun);

	if ((extra & BITSTREAM_STAY) == 0)
		Index += num;

	if (get_ByteIndex() > Len)
		throw LenReachedException();

	return (sum);
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
	if (get_BitIndex() != 0)
		idx++;
	idx += skip;
	if (idx > Len)
		throw LenReachedException();
	set_Index(0, idx);
}


const char * BitStream::LenReachedException::what() const throw() { return "BitStream Length reached"; }
