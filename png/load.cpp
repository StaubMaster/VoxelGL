
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
void	load_IDAT(BitStream & bits, DataStream & data)
{
	ZLIB zlib(bits);
	zlib.ToString();
	std::cout << "\n";

	BitStream deflate = zlib.ToBitStream();
	DEFLATE::Blocks(deflate, data);
}


PNG_Image *	load_png_better(const std::string & file_path)
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
		}
		else
		{
			std::cout << "\e[32mSignature Match\e[m\n";
		}
	}
	std::cout << "\n";


	IHDR ihdr;
	DataStream * data = NULL;

	while (1)
	{
		std::cout << "\n";
		Chunk chunk(file);
		BitStream chunk_stream = chunk.ToBitStream();
		std::cout << chunk.ToString();
		std::cout << "\n";

		if (chunk.isIHRD())
		{
			ihdr = load_IHDR(chunk_stream);
			//data = new DataStream(ihdr.width * (ihdr.height + 1) * 4);
			data = new DataStream(0xFFFFFFFF);
		}
		if (chunk.isIDAT())
			load_IDAT(chunk_stream, *data);
		if (chunk.isIEND())
			break;
	}

	PNG_Image * img = new PNG_Image();
	img -> w = ihdr.width;
	img -> h = ihdr.height;
	img -> data = new uint8[img -> w * img -> h * 4];
	PNG_Filter::filter(*data, *img);

	delete data;

	return (img);
}
