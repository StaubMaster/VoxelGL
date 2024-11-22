
#include "DEFLATE.hpp"

static uint32 len_base[] = {
    3, 4, 5, 6, 7, 8, 9, 10, //257 - 264
    11, 13, 15, 17,          //265 - 268
    19, 23, 27, 31,          //269 - 273
    35, 43, 51, 59,          //274 - 276
    67, 83, 99, 115,         //278 - 280
    131, 163, 195, 227,      //281 - 284
    258                      //285
};

static uint32 len_base_extra_bits[] = {
    0, 0, 0, 0, 0, 0, 0, 0, //257 - 264
    1, 1, 1, 1, //265 - 268
    2, 2, 2, 2, //269 - 273 
    3, 3, 3, 3, //274 - 276
    4, 4, 4, 4, //278 - 280
    5, 5, 5, 5, //281 - 284
    0           //285
};

static uint32 dist_base[] = {
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
           0    , 0      //30-31, error, shouldn't occur
};

static uint32 dist_base_extra_bits[] = {
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
    /*13*/ 13, 13,    //28-29
            0 , 0     //30-31 error, they shouldn't occur
};

void	DEFLATE::decode_Huffman(BitStream & bits, HuffmanTree & literal, HuffmanTree & distance, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mHuffman decode ... \e[m\n";

	uint32	decode_value;

	uint32	len_idx;
	uint32	len_len;

	uint32	dist_idx;
	uint32	dist_len;

	uint32	back_idx;

	while (1)
	{
		decode_value = literal.decode(bits);

		if (decode_value == 256)
		{
			break;
		}
		else if (decode_value < 256)
		{
			data.Insert(decode_value);
		}
		else if (decode_value < 286)
		{
			len_idx = decode_value - 257;
			len_len = len_base[len_idx] + bits.bits(len_base_extra_bits[len_idx]);

			dist_idx = distance.decode(bits);
			dist_len = dist_base[dist_idx] + bits.bits(dist_base_extra_bits[dist_idx]);

			back_idx = data.Index - dist_len;
			while (len_len != 0)
			{
				len_len--;
				data.Insert(data.Data[back_idx]);
				back_idx++;
			}
		}
		else
		{
			throw PNG_Image::PNG_Exception_InvalidData();
			os << "\e[31mError: Invalid Huffman Decode\e[m\n";
		}
	}

	os << "\e[34mHuffman decode done \e[m\n";
}



uint8 *	DEFLATE::dynamic_Huffman(BitStream & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN)
{
	std::ostream & os = DebugManager::GetOut();

	uint8 codeLenCodeLenOrder[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	uint8 codeLenCodeLen[19];
	for (uint32 i = 0; i < 19; i++)
		codeLenCodeLen[i] = 0;
	for (uint32 i = 0; i < H_CLEN; i++)
		codeLenCodeLen[codeLenCodeLenOrder[i]] = bits.bits(3);

	HuffmanTree	Trees(codeLenCodeLen, 19);
	uint8 * Huffman_BitLen_Trees = new uint8[H_LIT + H_DIST];
	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
		Huffman_BitLen_Trees[i] = 0;

	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
	{
		uint32	decode_value = Trees.decode(bits);

		if (decode_value < 16)
		{
			Huffman_BitLen_Trees[i] = decode_value;
		}
		else
		{
			uint32	repeat_count = 0;
			uint8	repeat_data = 0;
			if (decode_value == 16)
			{
				repeat_count = bits.bits(2) + 3;
				repeat_data = Huffman_BitLen_Trees[i - 1];
			}
			else if (decode_value == 17)
			{
				repeat_count = bits.bits(3) + 3;
			}
			else if (decode_value == 18)
			{
				repeat_count = bits.bits(7) + 11;
			}
			else
			{
				os << "\e[31mError: Invalid Huffman Decode\e[m\n";
				throw PNG_Image::PNG_Exception_InvalidData();
			}

			for (uint32 r = 0; r < repeat_count; r++)
			{
				Huffman_BitLen_Trees[i] = repeat_data;
				i++;
			}
			i--;
		}
	}

	return (Huffman_BitLen_Trees);
}



void	DEFLATE::Block_direct(BitStream & bits, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mdirect Data ...\e[m\n";

	throw PNG_Image::PNG_Exception_NotImplemented();

	os << "\e[34mdirect Data done\e[m\n";
	(void)bits;
	(void)data;
}
void	DEFLATE::Block_static(BitStream & bits, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mstatic Huffman ...\e[m\n";

	throw PNG_Image::PNG_Exception_NotImplemented();

	os << "\e[34mstatic Huffman done\e[m\n";
	(void)bits;
	(void)data;
}
void	DEFLATE::Block_dynamic(BitStream & bits, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mdynamic Huffman ...\e[m\n";

	uint32	H_LIT = bits.bits(5) + 257;
	uint32	H_DIST = bits.bits(5) + 1;
	uint32	H_CLEN = bits.bits(4) + 4;
	os << "H_LIT  : " << H_LIT  << "\n";
	os << "H_DIST : " << H_DIST << "\n";
	os << "H_CLEN : " << H_CLEN << "\n";

	uint8 * bitLens = DEFLATE::dynamic_Huffman(bits, H_LIT, H_DIST, H_CLEN);

	HuffmanTree	literal(&bitLens[0], H_LIT);
	HuffmanTree	distance(&bitLens[H_LIT], H_DIST);

	DEFLATE::decode_Huffman(bits, literal, distance, data);

	delete [] bitLens;

	os << "\e[34mdynamic Huffman done\e[m\n";
}

void	DEFLATE::Blocks(BitStream & bits, DataStream & data)
{
	std::ostream & os = DebugManager::GetOut();

	uint8	BFINAL;
	uint8	BTYPE;

	do
	{
		os << "decoding ...  " << bits.get_ByteIndex() << "/" << bits.Len << "\n";

		BFINAL = bits.bits(1);
		BTYPE = bits.bits(2);
		os << "BFINAL : " << uint_Bit(BFINAL, 0) << "\n";
		os << "BTYPE  : " << uint_Bit(BTYPE, 1) << "\n";

		if (BTYPE == 0b00)
		{
			Block_direct(bits, data);
		}
		else if (BTYPE == 0b01)
		{
			Block_static(bits, data);
		}
		else if (BTYPE == 0b10)
		{
			Block_dynamic(bits, data);
		}
		else
		{
			throw PNG_Image::PNG_Exception_InvalidData();
			os << "\e[31mError: Invalid Block Type\e[m\n";
		}
		os << "\n";
	}
	while (BFINAL == 0);
	os << "decoding done " << bits.get_ByteIndex() << "/" << bits.Len << "\n";
}
