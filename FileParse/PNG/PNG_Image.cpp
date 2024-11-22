
#include "../DataStream.hpp"
#include "PNG_Image.hpp"
#include "Chunk.hpp"
#include "ZLIB.hpp"
#include "Huffman.hpp"
#include "DEFLATE.hpp"
#include "PNG_Filter.hpp"

PNG_Image::PNG_Image(uint32 w, uint32 h) :
	w(w), h(h)
{
	data = new uint8[w * h * 4];
}
PNG_Image::~PNG_Image()
{
	delete [] data;
}



uint32	PNG_Image::DataIndex(uint32 x, uint32 y)
{
	return ((x + y * w) * 4);
}

void	PNG_Image::setPixelRGBA(uint32 x, uint32 y, uint32 pxl)
{
	uint8 * ptr = (uint8 *)&pxl;
	uint32 idx = DataIndex(x, y);

	data[idx + 0] = ptr[3];
	data[idx + 1] = ptr[2];
	data[idx + 2] = ptr[1];
	data[idx + 3] = ptr[0];
}


PNG_Image * PNG_Image::Scale(uint32 new_w, uint32 new_h)
{
	PNG_Image * img = new PNG_Image(new_w, new_h);

	float scale_x;
	float scale_y;
	uint32	idx_old;
	uint32	idx_new;
	for (uint32 y = 0; y < new_h; y++)
	{
		scale_y = (((float)y) / ((float)new_h)) * ((float)h);

		for (uint32 x = 0; x < new_w; x++)
		{
			scale_x = (((float)x) / ((float)new_w)) * ((float)w);

			idx_old = DataIndex(scale_x, scale_y);
			idx_new = img -> DataIndex(x, y);

			img -> data[idx_new + 0] = data[idx_old + 0];
			img -> data[idx_new + 1] = data[idx_old + 1];
			img -> data[idx_new + 2] = data[idx_old + 2];
			img -> data[idx_new + 3] = data[idx_old + 3];
		}
	}

	return (img);
}



std::string	PNG_Image::ReadFile(const std::string & file_path)
{
	std::ifstream file(file_path, std::ios::binary);
	if (!file.is_open())
		throw PNG_Exception_BadFile();

	std::string file_data;
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





PNG_Image::IHDR::IHDR()
{
	
}
PNG_Image::IHDR::IHDR(BitStream & bits)
{
	width = bits.byte32(BITSTREAM_REV);
	height = bits.byte32(BITSTREAM_REV);

	bit_depth = bits.byte8();
	color_type = bits.byte8();

	compression_method = bits.byte8();
	filter_method = bits.byte8();
	interlace_method = bits.byte8();
}
void	PNG_Image::IHDR::ToString(std::ostream & os) const
{
	os << " width: " << width << "\n";
	os << "height: " << height << "\n";

	os << " bit_depth: " << (uint16)bit_depth << "\n";
	os << "color_type: " << (uint16)color_type << "\n";

	os << "compression_method: " << (uint16)compression_method << "\n";
	os << "     filter_method: " << (uint16)filter_method << "\n";
	os << "  interlace_method: " << (uint16)interlace_method << "\n";
}



PNG_Image * PNG_Image::Load(const std::string & file_path, bool debug)
{
	(void)debug;
	DebugManager::SetOut(false);
	std::ostream & os = DebugManager::GetOut();

	try
	{
		os << "loading '" << file_path << "' ...\n";
		std::string file_str = ReadFile(file_path);

		os << "file length: " << file_str.size() << "\n";
		BitStream file(file_str);

		os << "\n";
		{
			uint64	signature_template = 0x0A1A0A0D474E5089;
			uint64	signature_received;

			signature_received = file.byte64();
			os << "signature\n";
			os << "template: " << uint_Hex(signature_template) << "\n";
			os << "received: " << uint_Hex(signature_received) << "\n";

			if (signature_received != signature_template)
				throw PNG_Exception_Signature();
		}
		os << "\n";

		IHDR imageHead;
		DataStream imageData(0);

		while (1)
		{
			os << "\n";
			Chunk chunk(file);
			BitStream chunk_stream = chunk.ToBitStream();
			os << chunk.ToString();
			os << "\n";
			if (chunk.isIHRD())
			{
				imageHead = IHDR(chunk_stream);
				imageHead.ToString(os);
			}
			if (chunk.isIDAT())
			{
				imageData.Concatenation(chunk_stream.Data, chunk_stream.Len);
			}
			if (chunk.isIEND())
				break;
		}

		BitStream bits(imageData.Data, imageData.Len);

		DataStream * data = new DataStream(0xFFFFFFFF);
		ZLIB::decompress(bits, *data);

		PNG_Image * img = new PNG_Image(imageHead.width, imageHead.height);
		PNG_Filter::filter(*data, *img);
		delete data;

		return (img);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception while loading Image: " << e.what() << "\n";
	}
	return (PNG_Image::Missing());
}
PNG_Image * PNG_Image::Load(const char * file_path, bool debug)
{
	if (file_path != NULL)
		return Load(std::string(file_path), debug);
	return PNG_Image::Missing();
}




PNG_Image * PNG_Image::Missing()
{
	PNG_Image * img = new PNG_Image(8, 4);

	for (uint32 y = 0; y < 4; y++)
	{
		for (uint32 x = 0; x < 8; x++)
		{
			uint32 pxl;
			if ((x & 1) == (y & 1))
				pxl = 0x000000FF;
			else
				pxl = 0xFF00FFFF;
			img -> setPixelRGBA(x, y, pxl);
		}
	}

	return (img);
}

const char * PNG_Image::PNG_Exception_NotImplemented::what() const throw() { return "Not Implemented"; }
const char * PNG_Image::PNG_Exception_InvalidData::what() const throw() { return "Invalid Data"; }
const char * PNG_Image::PNG_Exception_BadFile::what() const throw() { return "Bad File"; }
const char * PNG_Image::PNG_Exception_Signature::what() const throw() { return "Bad Signature"; }

