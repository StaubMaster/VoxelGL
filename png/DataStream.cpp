
#include "DataStream.hpp"

DataStream::DataStream(uint32 len)
{
	Len = len;
	Data = new uint8[Len];
	Index = 0;
}
DataStream::~DataStream()
{
	delete [] Data;
}

void	DataStream::Insert(uint8 data)
{
	if (Index >= Len)
		std::cout << "\e[31mDataStream Limit\e[m\n";

	Data[Index] = data;
	Index++;
}
uint8	DataStream::Exsert()
{
	if (Index >= Len)
		std::cout << "\e[31mDataStream Limit\e[m\n";

	uint8 data = Data[Index];
	Index++;
	return (data);
}
