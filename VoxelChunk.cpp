
#include "VoxelChunk.hpp"

VoxelChunk::VoxelChunk()
{
	Data = new char[Data_Size];

	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Corner);
	glGenBuffers(1, &Buffer_Index);
}
VoxelChunk::~VoxelChunk()
{
	delete [] Data;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Corner);
	glDeleteBuffers(1, &Buffer_Index);
	glDeleteVertexArrays(1, &Buffer_Array);
}



void	VoxelChunk::FillRandom()
{
	for (unsigned i = 0; i < Data_Size; i++)
	{
		Data[i] = std::rand() & 1;
	}
}




void	VoxelChunk::UpdateBufferCorner()
{
	unsigned int corner_count = (Side_Len + 1) * (Side_Len + 1) * (Side_Len + 1);
	Point * corner = new Point[corner_count];
	Point c;

	for (unsigned int z = 0; z <= Side_Len; z++)
	{
		c.z = z;
		for (unsigned int y = 0; y <= Side_Len; y++)
		{
			c.y = y;
			for (unsigned int x = 0; x <= Side_Len; x++)
			{
				c.x = x;
				corner[z * (Side_Len + 1) * (Side_Len + 1) + y * (Side_Len + 1) + x] = c;
			}
		}
	}

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);

	glBufferData(GL_ARRAY_BUFFER, corner_count * 3 * sizeof(float), corner, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0 * sizeof(float)));

	delete [] corner;
}
void	VoxelChunk::UpdateBufferIndex()
{
	unsigned int index_count = 6;
	unsigned int * index = new unsigned int[index_count];

	index[0] = 1;
	index[1] = 2;
	index[2] = Side_Len + 2;

	index[3] = 1;
	index[4] = Side_Len + 2;
	index[5] = Side_Len + 3;

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer_Index);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), index, GL_STATIC_DRAW);
	Index_Count = index_count;

	delete [] index;
}
void	VoxelChunk::Draw()
{
	glBindVertexArray(Buffer_Array);
	glDrawElements(GL_TRIANGLES, Index_Count, GL_UNSIGNED_INT, (void*)0);
}


