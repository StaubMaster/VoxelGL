
#include "png.h"

//	foreward
uint32_t bits_RtL_next(data_block *bits, uint8_t num)
{
	uint32_t	idx_byte;
	uint32_t	idx_bit;
	uint32_t	bit;
	uint32_t	bit_data;
	uint8_t		mun;

	bit_data = 0;
	mun = 0;
	while (num != 0)
	{
		idx_byte = (bits -> index) >> 3;
		idx_bit = (bits -> index) & 0b111;
		bit = ((bits -> data[idx_byte] >> idx_bit) & 1);
		bit_data = bit_data | (bit << mun);
		(bits -> index)++;
		num--;
		mun++;
	}
	return (bit_data);
}

//	foreward
uint32_t bits_RtL_none(data_block *bits, uint8_t num)
{
	uint32_t	idx_byte;
	uint32_t	idx_bit;
	uint32_t	bit;
	uint32_t	bit_data;
	uint8_t		mun;

	bit_data = 0;
	mun = 0;
	while (num != 0)
	{
		idx_byte = (bits -> index) >> 3;
		idx_bit = (bits -> index) & 0b111;
		bit = ((bits -> data[idx_byte] >> idx_bit) & 1);
		bit_data = bit_data | (bit << mun);
		(bits -> index)++;
		num--;
		mun++;
	}
	(bits -> index) -= mun;
	return (bit_data);
}

//	backward
uint32_t bits_LtR_next(data_block *bits, uint8_t num)
{
	uint32_t	idx_byte;
	uint32_t	idx_bit;
	uint32_t	bit;
	uint32_t	bit_data;
	uint8_t		mun;

	bit_data = 0;
	mun = 0;
	while (num != 0)
	{
		idx_byte = (bits -> index) >> 3;
		idx_bit = (bits -> index) & 0b111;
		bit = ((bits -> data[idx_byte] >> idx_bit) & 1);
		(bits -> index)++;
		num--;
		mun++;
		bit_data = bit_data | (bit << num);
	}
	return (bit_data);
}

//	backward
uint32_t bits_LtR_none(data_block *bits, uint8_t num)
{
	uint32_t	idx_byte;
	uint32_t	idx_bit;
	uint32_t	bit;
	uint32_t	bit_data;
	uint8_t		mun;

	bit_data = 0;
	mun = 0;
	while (num != 0)
	{
		idx_byte = (bits -> index) >> 3;
		idx_bit = (bits -> index) & 0b111;
		bit = ((bits -> data[idx_byte] >> idx_bit) & 1);
		(bits -> index)++;
		num--;
		mun++;
		bit_data = bit_data | (bit << num);
	}
	(bits -> index) -= mun;
	return (bit_data);
}

char	*bits_str(uint32_t data, char bits[33], uint8_t num)
{
	uint8_t		idx;
	uint32_t	mask;

	idx = 0;
	mask = 1 << num;
	while (mask != 0)
	{
		bits[idx] = '0' + ((data & mask) != 0);
		mask >>= 1;
		idx++;
	}
	bits[idx] = '\0';
	return (bits);
}
