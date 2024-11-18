
#ifndef PNG_IMAGE_HPP
# define PNG_IMAGE_HPP
# include "uint.hpp"

struct PNG_Image
{
	public:
		const uint32	w;
		const uint32	h;
		uint8	*data;

	public:
		PNG_Image(uint32 w, uint32 h);
		~PNG_Image();

	public:
		uint32	DataIndex(uint32 x, uint32 y);

		void	setPixelRGBA(uint32 x, uint32 y, uint32 pxl);

	public:
		static PNG_Image * Missing();
};

#endif
