
#ifndef PNG_IMAGE_HPP
# define PNG_IMAGE_HPP
# include <iostream>
# include <fstream>
# include <sstream>

# include "../DebugManager.hpp"
# include "../uint.hpp"
# include "../BitStream.hpp"

class PNG_Image
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

		PNG_Image * Scale(uint32 new_w, uint32 new_h);

	private:
		struct IHDR
		{
			uint32	width;
			uint32	height;

			uint8	bit_depth;
			uint8	color_type;

			uint8	compression_method;
			uint8	filter_method;
			uint8	interlace_method;

			IHDR();
			IHDR(BitStream & bits);

			void	ToString(std::ostream & os) const;
		};

	private:
		static std::string	ReadFile(const std::string & file_path);
	public:
		static PNG_Image * Load(const std::string & file_path, bool debug = false);
		static PNG_Image * Load(const char * file_path, bool debug = false);

		static PNG_Image * Missing();


		class PNG_Exception_NotImplemented : public std::exception { public: const char * what() const throw(); };
		class PNG_Exception_InvalidData : public std::exception { public: const char * what() const throw(); };
		class PNG_Exception_BadFile : public std::exception { public: const char * what() const throw(); };
		class PNG_Exception_Signature : public std::exception { public: const char * what() const throw(); };
};

#endif
