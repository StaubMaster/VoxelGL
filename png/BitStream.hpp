
#ifndef BITSTREAM_HPP
# define BITSTREAM_HPP
# include "uint.hpp"

# define BITSTREAM_STAY 0b01
# define BITSTREAM_REV 0b10

class BitStream
{
	public:
		const uint8*	Data;
		const uint32	Len;
		uint32			Index;

	public:
		BitStream(const uint8 * ptr, uint32 len);
		BitStream(const std::string & str);

	public:
		uint32	get_BitIndex() const;
		void	set_BitIndex(uint32 idx);
		uint32	get_ByteIndex() const;
		void	set_ByteIndex(uint32 idx);
		void	set_Index(uint32 bits, uint32 bytes);

	public:
		uint32	bits(uint32 num, uint8 extra = 0, uint32 skipBytes = 0, uint32 skipBits = 0);

		uint8	byte8( uint8 extra = 0, uint32 skipBytes = 0);
		uint16	byte16(uint8 extra = 0, uint32 skipBytes = 0);
		uint32	byte32(uint8 extra = 0, uint32 skipBytes = 0);
		uint64	byte64(uint8 extra = 0, uint32 skipBytes = 0);

	public:
		void			moveIndex(uint32 skip);
		const uint8 *	DataAtIndex(uint32 skipBytes = 0) const;

	private:
		class LenReachedException : public std::exception { public: const char * what() const throw(); };
};

#endif
