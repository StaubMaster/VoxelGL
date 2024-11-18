
#ifndef DATASTREAM_HPP
# define DATASTREAM_HPP
# include "uint.hpp"

class DataStream
{
	public:
		uint32	Len;
		uint8	*Data;
		uint32	Index;

	public:
		DataStream(uint32 len);
		~DataStream();

		void	Concatenation(const uint8 * data, uint32 len);

		void	Insert(uint8 data);
		uint8	Exsert();
};

#endif
