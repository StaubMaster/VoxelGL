
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



void	DataStream::Concatenation(const uint8 * data, uint32 len)
{
	uint8	* newData = new uint8[Len + len];

	for (uint32 i = 0; i < Len; i++)
	{
		newData[i] = Data[i];
	}
	for (uint32 i = 0; i < len; i++)
	{
		newData[i + Len] = data[i];
	}

	Len = Len + len;
	delete [] Data;
	Data = newData;
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
