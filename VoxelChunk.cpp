
#include "VoxelChunk.hpp"

unsigned int VoxelChunk::XYZ_to_VoxelIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Voxel_per_Side) * Voxel_per_Side);
}
unsigned int VoxelChunk::XYZ_to_VertexIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Vertex_per_Side) * Vertex_per_Side);
}


VoxelChunk::VoxelChunk()
{
	Data = new char[Voxel_per_Chunk];

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
	/*for (unsigned i = 0; i < Voxel_per_Chunk; i++)
	{
		Data[i] = std::rand() & 1;
	}*/
	for (unsigned int z = 0; z < Voxel_per_Side; z++)
	{
		for (unsigned int y = 0; y < Voxel_per_Side; y++)
		{
			for (unsigned int x = 0; x < Voxel_per_Side; x++)
			{
				unsigned int i = XYZ_to_VoxelIndex(x, y, z);
				if (y < 1)
					Data[i] = 0;
				else if (y > 1)
					Data[i] = 1;
				else
					Data[i] = std::rand() & 1;
				//std::cout << "[" << i << "] " << (int)(Data[i]) << "\n";
			}
		}
	}
}




void	VoxelChunk::UpdateBufferVertex()
{
	unsigned int vertex_count = Vertex_per_Chunk;
	Point * vertex = new Point[vertex_count];
	Point c;

	for (unsigned int z = 0; z < Vertex_per_Side; z++)
	{
		c.z = z * 4;
		for (unsigned int y = 0; y < Vertex_per_Side; y++)
		{
			c.y = y * 4;
			for (unsigned int x = 0; x < Vertex_per_Side; x++)
			{
				c.x = x * 4;
				vertex[XYZ_to_VertexIndex(x, y, z)] = c;
				//std::cout << x << ":" << y << ":" << z << " [" << XYZ_to_VertexIndex(x, y, z) << "] " << c.x << ":" << c.y << ":" << c.z << "\n";
			}
		}
	}
	std::cout << "Vertex:" << vertex_count << "\n";

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);

	glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0 * sizeof(float)));

	delete [] vertex;
}
void	VoxelChunk::UpdateBufferIndex()
{
	unsigned int * index = new unsigned int[Voxel_per_Chunk * 6 * 3];
	unsigned int index_count = 0;

	char c1, c2;
	for (unsigned int z = 0; z < Voxel_per_Side; z++)
	{
		for (unsigned int y = 0; y < Voxel_per_Side; y++)
		{
			for (unsigned int x = 0; x < Voxel_per_Side; x++)
			{
				if (x != Voxel_per_Side - 1)
				{
					c1 = Data[XYZ_to_VoxelIndex(x + 0, y, z)];
					c2 = Data[XYZ_to_VoxelIndex(x + 1, y, z)];
					if (c1 == 1 && c2 == 0)
					{
						//std::cout << "X+ " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 1, y + 0, z + 0);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
					if (c1 == 0 && c2 == 1)
					{
						//std::cout << "X- " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 1, y + 0, z + 0);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
				}

				if (y != Voxel_per_Side - 1)
				{
					c1 = Data[XYZ_to_VoxelIndex(x, y + 0, z)];
					c2 = Data[XYZ_to_VoxelIndex(x, y + 1, z)];
					if (c1 == 0 && c2 == 1)
					{
						//std::cout << "Y+ " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 0, y + 1, z + 0);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
					if (c1 == 1 && c2 == 0)
					{
						//std::cout << "Y- " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 0, y + 1, z + 0);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 1, y + 1, z + 0);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
				}

				if (z != Voxel_per_Side - 1)
				{
					c1 = Data[XYZ_to_VoxelIndex(x, y, z + 0)];
					c2 = Data[XYZ_to_VoxelIndex(x, y, z + 1)];
					if (c1 == 1 && c2 == 0)
					{
						//std::cout << "Z+ " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 0, y + 0, z + 1);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
					if (c1 == 0 && c2 == 1)
					{
						//std::cout << "Z- " << x << ":" << y << ":" << z << "\n";
						index[index_count + 0] = XYZ_to_VertexIndex(x + 0, y + 0, z + 1);
						index[index_count + 1] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 2] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 3] = XYZ_to_VertexIndex(x + 1, y + 0, z + 1);
						index[index_count + 4] = XYZ_to_VertexIndex(x + 0, y + 1, z + 1);
						index[index_count + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z + 1);
						index_count += 6;
					}
				}
			}
		}
	}
	std::cout << "index_count: " << index_count << "/" << (Voxel_per_Chunk * 6 * 3) << "\n";

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


