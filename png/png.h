
#ifndef PNG_H
# define PNG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <string.h>
# include <errno.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct s_chunk
{
	uint32_t	length;
	uint32_t	type;
	uint8_t		*data;
	uint32_t	crc;
}	chunk;

typedef struct s_image_header
{
	chunk			chunk;
	uint32_t	width;
	uint32_t	hight;

	uint8_t		bit_depth;
	uint8_t		color_type;

	uint8_t		method_compression;
	uint8_t		method_filter;
	uint8_t		method_interlace;
}	image_header;

typedef struct s_image_data
{
	chunk		chunk;
}	image_data;

typedef struct s_zlib_block
{
	uint8_t		cmf;
	uint8_t		extra_flags;
	uint8_t		*data;
	uint16_t	check_value;
}	zlib_block;

typedef struct s_data_block
{
	uint32_t	index;
	uint8_t		*data;
}	data_block;

typedef struct s_huff_code_tree
{
	uint32_t	*codes;
	uint8_t		*bit_lens;
	uint32_t	len;
}	huff_code_tree;

typedef struct s_image
{
	uint32_t	w;
	uint32_t	h;
	uint8_t		*data;
}	image;

//	mem.c
void	mem_free(void *p);
void	mem_zero(void *ptr, uint32_t len);
void	mem_copy(void *ptr_src, void *ptr_dst, uint32_t len);
void	*mem_init(uint32_t num, uint32_t siz);

//	read.c
uint32_t	read_4(int fd);
uint32_t	char4_to_uint(uint8_t	 *val);

//	bits.c
uint32_t	bits_RtL_next(data_block *bits, uint8_t num);
uint32_t	bits_RtL_none(data_block *bits, uint8_t num);
uint32_t	bits_LtR_next(data_block *bits, uint8_t num);
uint32_t	bits_LtR_none(data_block *bits, uint8_t num);
char		*bits_str(uint32_t data, char bits[33], uint8_t num);

chunk	chunk_read(int fd);
void	chunk_print(chunk ch);
void	image_header_data(image_header *ihdr);

//	HuffCodeTree.c
huff_code_tree	build_HuffCode(uint8_t *code_bit_len, uint32_t len);
uint32_t		decode_HuffCode(data_block *bits, huff_code_tree tree);

//	block.c
data_block decompress_all_blocks(data_block *bit_data);

//void	filter_None(uint8_t	 byte, uint32_t x, uint32_t y, image *img);
//void	filter_Sub(uint8_t	 byte, uint32_t x, uint32_t y, image *img);
//void	filter_Up(uint8_t	 byte, uint32_t x, uint32_t y, image *img);
//void	filter_Avg(uint8_t	 byte, uint32_t x, uint32_t y, image *img);
//void	filter_Paeth(uint8_t	 byte, uint32_t x, uint32_t y, image *img);
void	filter(data_block decompressed, image *img);

//	sixel.c
void	sixel_draw(uint8_t *data, uint32_t w, uint32_t h);
void	sixel_draw_r(uint8_t *data, uint32_t w, uint32_t h);
void	sixel_draw_g(uint8_t *data, uint32_t w, uint32_t h);
void	sixel_draw_b(uint8_t *data, uint32_t w, uint32_t h);

#endif
