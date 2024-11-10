
#include "VoxelChunk.hpp"

unsigned int VoxelChunk::XYZ_to_VoxelIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Voxel_per_Side) * Voxel_per_Side);
}
unsigned int VoxelChunk::XYZ_to_VertexIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Vertex_per_Side) * Vertex_per_Side);
}

void VoxelChunk::IndexFaceXn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x, y + 0, z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(x, y + 1, z + 0);
	index[idx + 2] = XYZ_to_VertexIndex(x, y + 0, z + 1);
	index[idx + 3] = XYZ_to_VertexIndex(x, y + 0, z + 1);
	index[idx + 4] = XYZ_to_VertexIndex(x, y + 1, z + 0);
	index[idx + 5] = XYZ_to_VertexIndex(x, y + 1, z + 1);
}
void VoxelChunk::IndexFaceXp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x, y + 0, z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(x, y + 0, z + 1);
	index[idx + 2] = XYZ_to_VertexIndex(x, y + 1, z + 0);
	index[idx + 3] = XYZ_to_VertexIndex(x, y + 1, z + 0);
	index[idx + 4] = XYZ_to_VertexIndex(x, y + 0, z + 1);
	index[idx + 5] = XYZ_to_VertexIndex(x, y + 1, z + 1);
}
void VoxelChunk::IndexFaceYn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x + 0, y, z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(x + 0, y, z + 1);
	index[idx + 2] = XYZ_to_VertexIndex(x + 1, y, z + 0);
	index[idx + 3] = XYZ_to_VertexIndex(x + 1, y, z + 0);
	index[idx + 4] = XYZ_to_VertexIndex(x + 0, y, z + 1);
	index[idx + 5] = XYZ_to_VertexIndex(x + 1, y, z + 1);
}
void VoxelChunk::IndexFaceYp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x + 0, y, z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(x + 1, y, z + 0);
	index[idx + 2] = XYZ_to_VertexIndex(x + 0, y, z + 1);
	index[idx + 3] = XYZ_to_VertexIndex(x + 0, y, z + 1);
	index[idx + 4] = XYZ_to_VertexIndex(x + 1, y, z + 0);
	index[idx + 5] = XYZ_to_VertexIndex(x + 1, y, z + 1);
}
void VoxelChunk::IndexFaceZn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x + 0, y + 0, z);
	index[idx + 1] = XYZ_to_VertexIndex(x + 1, y + 0, z);
	index[idx + 2] = XYZ_to_VertexIndex(x + 0, y + 1, z);
	index[idx + 3] = XYZ_to_VertexIndex(x + 0, y + 1, z);
	index[idx + 4] = XYZ_to_VertexIndex(x + 1, y + 0, z);
	index[idx + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z);
}
void VoxelChunk::IndexFaceZp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z)
{
	index[idx + 0] = XYZ_to_VertexIndex(x + 0, y + 0, z);
	index[idx + 1] = XYZ_to_VertexIndex(x + 0, y + 1, z);
	index[idx + 2] = XYZ_to_VertexIndex(x + 1, y + 0, z);
	index[idx + 3] = XYZ_to_VertexIndex(x + 1, y + 0, z);
	index[idx + 4] = XYZ_to_VertexIndex(x + 0, y + 1, z);
	index[idx + 5] = XYZ_to_VertexIndex(x + 1, y + 1, z);
}




VoxelChunk::VoxelChunk(int x, int y, int z) :
	Chunk_X(x), Chunk_Y(y), Chunk_Z(z)
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
	unsigned int * vertex = new unsigned int[vertex_count];

	for (unsigned int z = 0; z < Vertex_per_Side; z++)
	{
		for (unsigned int y = 0; y < Vertex_per_Side; y++)
		{
			for (unsigned int x = 0; x < Vertex_per_Side; x++)
			{
				vertex[XYZ_to_VertexIndex(x, y, z)] = x | (y << 8) | (z << 16);
			}
		}
	}
	std::cout << "Vertex:" << vertex_count << "\n";

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);

	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(unsigned int), vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 1 * sizeof(unsigned int), (void *)0);

	delete [] vertex;
}
void	VoxelChunk::UpdateBufferIndex(
	const VoxelChunk * Xn, const VoxelChunk * Xp,
	const VoxelChunk * Yn, const VoxelChunk * Yp,
	const VoxelChunk * Zn, const VoxelChunk * Zp)
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
				c1 = 0;
				c2 = 0;
				if (x == 0)
				{
					if (Xn != NULL)
					{
						c1 = Xn -> Data[XYZ_to_VoxelIndex(Voxel_per_Side - 1, y, z)];
						c2 = Data[XYZ_to_VoxelIndex(0, y, z)];
					}
				}
				else if (x == Voxel_per_Side)
				{
					if (Xp != NULL)
					{
						c1 = Data[XYZ_to_VoxelIndex(Voxel_per_Side, y, z)];
						c2 = Xp -> Data[XYZ_to_VoxelIndex(0, y, z)];
					}
				}
				else
				{
					c1 = Data[XYZ_to_VoxelIndex(x - 1, y, z)];
					c2 = Data[XYZ_to_VoxelIndex(x - 0, y, z)];
				}

				if (c1 == 1 && c2 == 0)
				{
					IndexFaceXn(index, index_count, x, y, z);
					index_count += 6;
				}
				if (c1 == 0 && c2 == 1)
				{
					IndexFaceXp(index, index_count, x, y, z);
					index_count += 6;
				}



				c1 = 0;
				c2 = 0;
				if (y == 0)
				{
					if (Yn != NULL)
					{
						c1 = Yn -> Data[XYZ_to_VoxelIndex(x, Voxel_per_Side - 1, z)];
						c2 = Data[XYZ_to_VoxelIndex(x, 0, z)];
					}
				}
				else if (y == Voxel_per_Side)
				{
					if (Yp != NULL)
					{
						c1 = Data[XYZ_to_VoxelIndex(x, Voxel_per_Side, z)];
						c2 = Yp -> Data[XYZ_to_VoxelIndex(x, 0, z)];
					}
				}
				else
				{
					c1 = Data[XYZ_to_VoxelIndex(x, y - 1, z)];
					c2 = Data[XYZ_to_VoxelIndex(x, y - 0, z)];
				}

				if (c1 == 1 && c2 == 0)
				{
					IndexFaceYn(index, index_count, x, y, z);
					index_count += 6;
				}
				if (c1 == 0 && c2 == 1)
				{
					IndexFaceYp(index, index_count, x, y, z);
					index_count += 6;
				}



				c1 = 0;
				c2 = 0;
				if (z == 0)
				{
					if (Zn != NULL)
					{
						c1 = Zn -> Data[XYZ_to_VoxelIndex(x, y, Voxel_per_Side - 1)];
						c2 = Data[XYZ_to_VoxelIndex(x, y, 0)];
					}
				}
				else if (z == Voxel_per_Side)
				{
					if (Zp != NULL)
					{
						c1 = Data[XYZ_to_VoxelIndex(x, y, Voxel_per_Side)];
						c2 = Zp -> Data[XYZ_to_VoxelIndex(x, y, 0)];
					}
				}
				else
				{
					c1 = Data[XYZ_to_VoxelIndex(x, y, z - 1)];
					c2 = Data[XYZ_to_VoxelIndex(x, y, z - 0)];
				}

				if (c1 == 1 && c2 == 0)
				{
					IndexFaceZn(index, index_count, x, y, z);
					index_count += 6;
				}
				if (c1 == 0 && c2 == 1)
				{
					IndexFaceZp(index, index_count, x, y, z);
					index_count += 6;
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

	(void)Xn;
	(void)Yn;
	(void)Zn;
	(void)Xp;
	(void)Yp;
	(void)Zp;
}
void	VoxelChunk::Draw(int Uni_Chunk_Pos)
{
	glUniform3i(Uni_Chunk_Pos, Chunk_X, Chunk_Y, Chunk_Z);

	glBindVertexArray(Buffer_Array);
	glDrawElements(GL_TRIANGLES, Index_Count, GL_UNSIGNED_INT, (void*)0);
}


