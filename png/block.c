
#include "png.h"

uint32_t len_base[] = {
    3, 4, 5, 6, 7, 8, 9, 10, //257 - 264
    11, 13, 15, 17,          //265 - 268
    19, 23, 27, 31,          //269 - 273 
    35, 43, 51, 59,          //274 - 276
    67, 83, 99, 115,         //278 - 280
    131, 163, 195, 227,      //281 - 284
    258                      //285
};

uint32_t len_base_extra_bits[] = {
    0, 0, 0, 0, 0, 0, 0, 0, //257 - 264
    1, 1, 1, 1, //265 - 268
    2, 2, 2, 2, //269 - 273 
    3, 3, 3, 3, //274 - 276
    4, 4, 4, 4, //278 - 280
    5, 5, 5, 5, //281 - 284
    0           //285
};

uint32_t dist_base[] = {
    /*0*/ 1, 2, 3, 4,    //0-3
    /*1*/ 5, 7,          //4-5
    /*2*/ 9, 13,         //6-7
    /*3*/ 17, 25,        //8-9
    /*4*/ 33, 49,        //10-11
    /*5*/ 65, 97,        //12-13
    /*6*/ 129, 193,      //14-15
    /*7*/ 257, 385,      //16-17
    /*8*/ 513, 769,      //18-19
    /*9*/ 1025, 1537,    //20-21
    /*10*/ 2049, 3073,   //22-23
    /*11*/ 4097, 6145,   //24-25
    /*12*/ 8193, 12289,  //26-27
    /*13*/ 16385, 24577, //28-29
             0   , 0      //30-31, error, shouldn't occur
};

uint32_t dist_base_extra_bits[] = {
    /*0*/ 0, 0, 0, 0, //0-3
    /*1*/ 1, 1,       //4-5
    /*2*/ 2, 2,       //6-7
    /*3*/ 3, 3,       //8-9
    /*4*/ 4, 4,       //10-11
    /*5*/ 5, 5,       //12-13
    /*6*/ 6, 6,       //14-15
    /*7*/ 7, 7,       //16-17
    /*8*/ 8, 8,       //18-19
    /*9*/ 9, 9,       //20-21
    /*10*/ 10, 10,    //22-23
    /*11*/ 11, 11,    //24-25
    /*12*/ 12, 12,    //26-27
    /*13*/ 13, 13,     //28-29
            0 , 0      //30-31 error, they shouldn't occur
};

void	decompress_block(data_block *bit_data, data_block *decompressed, huff_code_tree literal, huff_code_tree distance)
{
	// zlib deflate
	while (1)
	{
		uint32_t	decode_value;
		decode_value = decode_HuffCode(bit_data, literal);
		//printf("decode T val %10u : %u\n", block_idx, decode_value);

		if (decode_value == 256)
		{
			break;
		}
		else if (decode_value < 256)
		{
			decompressed -> data[decompressed -> index] = decode_value;
			decompressed -> index++;
		}
		else if (decode_value < 286)
		{
			uint32_t	len_idx = decode_value - 257;
			uint32_t	len_len = len_base[len_idx] + bits_RtL_next(bit_data, len_base_extra_bits[len_idx]);

			uint32_t	dist_idx = decode_HuffCode(bit_data, distance);
			uint32_t	dist_len = dist_base[dist_idx] + bits_RtL_next(bit_data, dist_base_extra_bits[dist_idx]);

			//printf("len %u : dist %u\n", len_len, dist_len);

			uint32_t	back_idx = decompressed -> index - dist_len;
			while (len_len != 0)
			{
				len_len--;
				decompressed -> data[decompressed -> index] = decompressed -> data[back_idx];
				decompressed -> index++;
				back_idx++;
			}
		}
		else
		{
			printf("error : bad decode\n");
		}
	}
}

uint8_t *decompress_bit_lens(data_block *bit_data, uint32_t h_clen, uint32_t h_lit, uint32_t h_dist)
{
	uint8_t code_len_code_len_order[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	uint8_t code_len_code_len[19] = {};
	for (uint32_t j = 0; j < h_clen; j++)
	{
		code_len_code_len[code_len_code_len_order[j]] = bits_RtL_next(bit_data, 3);
	}

	//printf("  Tree trees\n");
	huff_code_tree	trees;
	uint8_t			*HuffCode_BitLen_trees;
	trees = build_HuffCode(code_len_code_len, 19);
	HuffCode_BitLen_trees = (uint8_t *)mem_init(h_lit + h_dist, sizeof(uint8_t));
	//printf("\n");

	//	decode	trees
	uint32_t	code_idx = 0;
	while (code_idx < (h_dist + h_lit))
	{
		uint32_t	decode_value;
		decode_value = decode_HuffCode(bit_data, trees);
		//printf("decode TT val %3i : %u\n", code_idx, decode_value);

		if (decode_value < 16)
		{
			HuffCode_BitLen_trees[code_idx] = decode_value;
			code_idx++;
		}
		else
		{
			uint32_t	repeat_count = 0;
			uint8_t		repeat_data = 0;
			if (decode_value == 16)
			{
				repeat_count = bits_RtL_next(bit_data, 2) + 3;
				repeat_data = HuffCode_BitLen_trees[code_idx - 1];
			}
			else if (decode_value == 17)
				repeat_count = bits_RtL_next(bit_data, 3) + 3;
			else if (decode_value == 18)
				repeat_count = bits_RtL_next(bit_data, 7) + 11;
			else
				printf("error : bad decode\n");
			for (uint32_t r = 0; r < repeat_count; r++)
			{
				HuffCode_BitLen_trees[code_idx] = repeat_data;
				code_idx++;
			}
		}
	}
	free(trees.codes);
	return (HuffCode_BitLen_trees);
}

data_block decompress_all_blocks(data_block *bit_data)
{
	data_block	decompressed;
	decompressed.index = 0;
	decompressed.data = (uint8_t *)malloc(0xFFFFFFFF);
	if (decompressed.data == NULL)
	{
		printf("no buffer\n");
		decompressed.index = -1;
		return (decompressed);
	}

	uint8_t	b_final = 0;
	uint8_t	b_type;

	while (b_final == 0)
	{
		b_final = bits_RtL_next(bit_data, 1);
		b_type = bits_RtL_next(bit_data, 2);
		printf("B final : %u\n", b_final);
		printf("B type  : %u\n", b_type);

		if (b_type == 0b00)
			printf("block type not implemented\n");
		else if (b_type == 0b01)
			printf("block type not implemented\n");
		else if (b_type == 0b10)
		{
			uint32_t		h_lit;
			uint32_t		h_dist;
			uint32_t		h_clen;
			h_lit = bits_RtL_next(bit_data, 5) + 257;
			h_dist = bits_RtL_next(bit_data, 5) + 1;
			h_clen = bits_RtL_next(bit_data, 4) + 4;

			printf("Decode Trees\n");
			uint8_t			*HuffCode_BitLen_trees;
			HuffCode_BitLen_trees = decompress_bit_lens(bit_data, h_clen, h_lit, h_dist);

			huff_code_tree	literal;
			huff_code_tree	distance;
			literal = build_HuffCode(&HuffCode_BitLen_trees[0], h_lit);
			distance = build_HuffCode(&HuffCode_BitLen_trees[h_lit], h_dist);

			printf("Decode Block\n");
			decompress_block(bit_data, &decompressed, literal, distance);

			mem_free(HuffCode_BitLen_trees);
			mem_free(literal.codes);
			mem_free(distance.codes);
		}
		else
		{
			printf("block type invalid\n");
		}

		printf("\n");
	}
	return (decompressed);
}
