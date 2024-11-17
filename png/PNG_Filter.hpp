
#ifndef PNG_FILTER_HPP
# define PNG_FILTER_HPP
# include "DataStream.hpp"
# include "PNG_Image.hpp"

class PNG_Filter
{
	private:
		static const uint8	rel_X = 0b01;
		static const uint8	rel_Y = 0b10;
		static const uint8	rel_XY = 0b11;

	private:
		struct PixelData
		{
			uint32		x;
			uint32		y;
			uint8		col;
			PNG_Image &	img;

			PixelData(PNG_Image & img);
		};

		static uint32	PixelIndex(PixelData pxl);

		static uint8	getPixel(PixelData pxl, uint8 rel);

		static void		filter_None(PixelData pxl, uint8 byte);
		static void		filter_Sub(PixelData pxl, uint8 byte);
		static void		filter_Up(PixelData pxl, uint8 byte);
		static void		filter_Avg(PixelData pxl, uint8 byte);
		static void		filter_Paeth(PixelData pxl, uint8 byte);

	public:
		static void		filter(DataStream & data, PNG_Image & img);
};

#endif
