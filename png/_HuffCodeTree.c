
#include "_png.h"

uint8_t get_max_bit_len(uint8_t *code_bit_len, uint32_t len)
{
	uint8_t max_bit = 0;
	uint32_t i = 0;
	while (i < len)
	{
		if (max_bit < code_bit_len[i])
			max_bit = code_bit_len[i];
		i++;
	}
	return (max_bit);
}

void get_bit_len_count(uint32_t *code_count, uint8_t *code_bit_len, uint32_t len)
{
	uint32_t i = 0;
	while (i < len)
	{
		code_count[code_bit_len[i]]++;
		i++;
	}
}

void first_code_for_bitlen(uint32_t *first_codes, uint32_t *code_count, uint32_t len)
{
	uint32_t code = 0;
	uint32_t i = 0;
	while (i < len)
	{
		code = (code + code_count[i]) << 1;
		if (code_count[i + 1] > 0)
			first_codes[i + 1] = code;
		i++;
	}
}

void assign_Huffman_code(uint32_t *assign_codes, uint32_t *first_codes, uint8_t *code_bit_len, uint32_t len)
{
	uint32_t i = 0;
	while (i < len)
	{
		if (code_bit_len[i] != 0)
			assign_codes[i] = first_codes[code_bit_len[i]]++;
		i++;
	}
}

huff_code_tree build_HuffCode(uint8_t *code_bit_len, uint32_t len)
{
	static uint32_t yes = 1;

	huff_code_tree	tree;

	uint32_t max_bit_len = get_max_bit_len(code_bit_len, len);

	if (yes == 0)
	{
		printf("max len %u\n\n", max_bit_len);
		for (uint32_t j = 0; j < len; j++)
		{
			if (code_bit_len[j] != 0)
				printf("bit len %3i : %u\n", j, code_bit_len[j]);
		}
		printf("\n");
	}

	uint32_t *code_count = (uint32_t *)mem_init((max_bit_len + 1), sizeof(uint32_t));
	uint32_t *first_codes = (uint32_t *)mem_init((max_bit_len + 1), sizeof(uint32_t));
	tree.codes = (uint32_t *)mem_init((len), sizeof(uint32_t));

	get_bit_len_count(code_count, code_bit_len, len);
	code_count[0] = 0;
	if (yes == 0)
	{
		for (uint32_t j = 0; j < max_bit_len + 1; j++)
			printf("count %3i : %u\n", j, code_count[j]);
		printf("\n");
	}

	first_code_for_bitlen(first_codes, code_count, max_bit_len);
	char bits[33];
	if (yes == 0)
	{
		for (uint32_t j = 0; j < max_bit_len + 1; j++)
			printf("first %3i : %s\n", j, bits_str(first_codes[j], bits, j));
		printf("\n");
	}

	assign_Huffman_code(tree.codes, first_codes, code_bit_len, len);
	if (yes == 0)
	{
		for (uint32_t j = 0; j < len; j++)
		{
			if (code_bit_len[j] != 0)
				printf("assign %3i : %s\n", j, bits_str(tree.codes[j], bits, code_bit_len[j]));
		}
		printf("\n");
	}

	mem_free(code_count);
	mem_free(first_codes);

	tree.bit_lens = code_bit_len,
	tree.len = len;

	yes = 1;

	return (tree);
}

uint32_t decode_HuffCode(data_block *bits, huff_code_tree tree)
{
	char bits1[33];
	char bits2[33];
	static uint32_t yes = 0;

	uint32_t	i = 0;
	while (i < tree.len)
	{
		if (tree.bit_lens[i] != 0)
		{
			uint32_t code;
			code = bits_LtR_none(bits, tree.bit_lens[i]);

			if (yes < 16)
			{
				bits_str(code, bits1, tree.bit_lens[i]);
				bits_str(tree.codes[i], bits2, tree.bit_lens[i]);
				//printf("code [%2u] %8s =?= %8s\n", i, bits1, bits2);
				yes++;
			}

			if (tree.codes[i] == code)
			{
				bits -> index += tree.bit_lens[i];
				return (i);
			}
		}
		i++;
	}
	return (0);
}
