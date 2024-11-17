
#include "PNG.hpp"

std::string	read_whole_file(const std::string & file_path)
{
	std::ifstream file(file_path, std::ios::binary);

	std::string	file_data;
	char	binary_block[1024];

	file.read(binary_block, 1024);
	while (!file.eof())
	{
		file_data += std::string(binary_block, 1024);
		file.read(binary_block, 1024);
	}
	file_data += std::string(binary_block, file.gcount());

	return (file_data);
}



IHDR	load_IHDR(BitStream & bits)
{
	IHDR	ihdr;

	ihdr.width = bits.byte32(BITSTREAM_REV);
	ihdr.height = bits.byte32(BITSTREAM_REV);

	ihdr.bit_depth = bits.byte8();
	ihdr.color_type = bits.byte8();

	ihdr.compression_method = bits.byte8();
	ihdr.filter_method = bits.byte8();
	ihdr.interlace_method = bits.byte8();

	std::cout << " width: " << ihdr.width << "\n";
	std::cout << "height: " << ihdr.height << "\n";

	std::cout << " bit_depth: " << (uint16)ihdr.bit_depth << "\n";
	std::cout << "color_type: " << (uint16)ihdr.color_type << "\n";

	std::cout << "compression_method: " << (uint16)ihdr.compression_method << "\n";
	std::cout << "     filter_method: " << (uint16)ihdr.filter_method << "\n";
	std::cout << "  interlace_method: " << (uint16)ihdr.interlace_method << "\n";

	return (ihdr);
}
uint8 * decompress_BitLens(BitStream & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN)
{
	uint8 codeLenCodeLenOrder[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	uint8 codeLenCodeLen[19];
	for (uint32 i = 0; i < 18; i++)
		codeLenCodeLen[i] = 0;
	for (uint32 i = 0; i < H_CLEN; i++)
		codeLenCodeLen[codeLenCodeLenOrder[i]] = bits.bits(3);
	//for (uint32 i = 0; i < H_CLEN; i++)
	//	std::cout << "TreeCode [" << std::setw(2) << i << "] " << (uint16)codeLenCodeLen[i] << "\n";

	HuffmanTree	Trees(codeLenCodeLen, 19);
	uint8 * Huffman_BitLen_Trees = new uint8[H_LIT + H_DIST];
	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
		Huffman_BitLen_Trees[i] = 0;

	static uint32 yes = 16;

	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
	{
		uint32	decode_value = Trees.decode(bits);
		if (yes < 16)
		{
			//std::cout << "decode: " << decode_value << "\n";
			yes++;
		}

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
				std::cout << "\e[31mError Invalid Value\e[m\n";
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
    /*13*/ 13, 13,     //28-29
            0 , 0      //30-31 error, they shouldn't occur
};


void	decompress_block(BitStream & bits, HuffmanTree & literal, HuffmanTree & distance)
{
	static uint32 yes = 0;

	while (1)
	{
		uint32	decode_value = literal.decode(bits);
		if (yes < 16)
		{
			//std::cout << "decode: " << decode_value << "\n";
			yes++;
		}

		if (decode_value == 256)
		{
			break;
		}
		else if (decode_value < 256)
		{
			
		}
		else if (decode_value < 286)
		{
			uint32 len_idx = decode_value - 257;
			uint32 len_len = len_base[len_idx] + bits.bits(len_base_extra_bits[len_idx]);

			uint32 dist_idx = distance.decode(bits);
			uint32 dist_len = dist_base[dist_idx] + bits.bits(dist_base_extra_bits[dist_idx]);

			(void)len_len;
			(void)dist_len;
		}
		else
		{
			std::cout << "\e[31mError Block \e[m\n";
		}
	}
}
void	load_IDAT(BitStream & bits, uint8 *mem)
{
	ZLIB zlib(bits);
	zlib.ToString();
	std::cout << "\n";

	BitStream deflate = zlib.ToBitStream();

//	const uint8 * ptr = deflate.Data + deflate.get_ByteIndex();
//	std::cout << "[0]" << uint_Hex(ptr[0]) << "(" << uint_Bit(ptr[0]) << ")\n";
//	std::cout << "[1]" << uint_Hex(ptr[1]) << "(" << uint_Bit(ptr[1]) << ")\n";
//	std::cout << "[2]" << uint_Hex(ptr[2]) << "(" << uint_Bit(ptr[2]) << ")\n";
//	std::cout << "[3]" << uint_Hex(ptr[3]) << "(" << uint_Bit(ptr[3]) << ")\n";
//	std::cout << "[4]" << uint_Hex(ptr[4]) << "(" << uint_Bit(ptr[4]) << ")\n";
//	std::cout << "[5]" << uint_Hex(ptr[5]) << "(" << uint_Bit(ptr[5]) << ")\n";
//	std::cout << "[6]" << uint_Hex(ptr[6]) << "(" << uint_Bit(ptr[6]) << ")\n";
//	std::cout << "[7]" << uint_Hex(ptr[7]) << "(" << uint_Bit(ptr[7]) << ")\n";

	uint8	BFINAL;
	uint8	BTYPE;

	do
	{
		std::cout << "\n";
		BFINAL = deflate.bits(1);
		BTYPE = deflate.bits(2);
		std::cout << "BFINAL : " << uint_Bit(BFINAL, 0) << "\n";
		std::cout << "BTYPE  : " << uint_Bit(BTYPE, 1) << "\n";

		if (BTYPE == 0b00)
		{
			std::cout << "\e[32mnon Compressed\e[m\n";
		}
		else if (BTYPE == 0b01)
		{
			std::cout << "\e[32mstatic Huffman\e[m\n";
		}
		else if (BTYPE == 0b10)
		{
			std::cout << "\e[32mdynamic Huffman\e[m\n";

			uint32	H_LIT = deflate.bits(5);
			uint32	H_DIST = deflate.bits(5);
			uint32	H_CLEN = deflate.bits(4);
			std::cout << "H_LIT  : " << H_LIT << "(" << uint_Bit(H_LIT, 4) << ")\n";
			std::cout << "H_DIST : " << H_DIST << "(" << uint_Bit(H_DIST, 4) << ")\n";
			std::cout << "H_CLEN : " << H_CLEN << "(" << uint_Bit(H_CLEN, 3) << ")\n";
			H_LIT += 257;
			H_DIST += 1;
			H_CLEN += 4;

			uint8 * bitLens = decompress_BitLens(deflate, H_LIT, H_DIST, H_CLEN);

			HuffmanTree	literal(&bitLens[0], H_LIT);
			HuffmanTree	distance(&bitLens[H_LIT], H_DIST);

			//std::cout << "\n";
			//for (uint32 i = 0; i < 24; i++)
			//	std::cout << "\e[34m" << uint_Hex(bitLens[i]) << "\e[m\n";
			//std::cout << "\n";
			//for (uint32 i = 0; i < 24; i++)
			//	std::cout << "\e[34m" << uint_Hex((uint8)literal.Codes[i]) << "\e[m\n";
			//std::cout << "\n";

			std::cout << "\e[34mDecode Block ... \e[m\n";
			decompress_block(deflate, literal, distance);
			std::cout << "\e[34mDecode Block done \e[m\n";

			delete [] bitLens;
		}
		else
		{
			std::cout << "\e[31mError Block Type\e[m\n";
		}
		std::cout << "\n";
	}
	while (BFINAL == 0);

	(void)deflate;
	(void)bits;
	(void)mem;
}



void	load_png_better(const std::string & file_path)
{
	std::cout << "loading '" << file_path << "' ...\n";
	const std::string file_str = read_whole_file(file_path);
	std::cout << "file length: " << file_str.size() << "\n";
	BitStream file(file_str);

	std::cout << "\n";
	{
		uint64	signature_template = 0x0A1A0A0D474E5089;
		uint64	signature_received;

		signature_received = file.byte64();
		std::cout << "signature\n";
		std::cout << "template: " << uint_Hex(signature_template) << "\n";
		std::cout << "received: " << uint_Hex(signature_received) << "\n";

		if (signature_received != signature_template)
		{
			std::cout << "\e[31mSignature Wrong\e[m\n";
			return;
		}
		else
		{
			std::cout << "\e[32mSignature Match\e[m\n";
		}
	}
	std::cout << "\n";


	uint8	* mem = new uint8[0xFFFFFFFF];

	while (1)
	{
		std::cout << "\n";
		Chunk chunk(file);
		BitStream chunk_stream = chunk.ToBitStream();
		std::cout << chunk.ToString();
		std::cout << "\n";

		if (chunk.isIHRD())
			load_IHDR(chunk_stream);
		if (chunk.isIDAT())
			load_IDAT(chunk_stream, mem);
		if (chunk.isIEND())
			break;
	}

	delete [] mem;

	std::cout << "\n";
}
