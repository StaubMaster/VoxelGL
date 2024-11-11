
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
	/*std::cout
		<< "++++ VoxelChunk "
		<< Chunk_X << ":" << Chunk_Y << ":" << Chunk_Z
		<< "\n";*/

	Data = new char[Voxel_per_Chunk];

	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Corner);
	glGenBuffers(1, &Buffer_Index);
}
VoxelChunk::~VoxelChunk()
{
	/*std::cout
		<< "---- VoxelChunk "
		<< Chunk_X << ":" << Chunk_Y << ":" << Chunk_Z
		<< "\n";*/

	delete [] Data;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Corner);
	glDeleteBuffers(1, &Buffer_Index);
	glDeleteVertexArrays(1, &Buffer_Array);
}
VoxelChunk::VoxelChunk(const VoxelChunk & other) :
	Chunk_X(other.Chunk_X), Chunk_Y(other.Chunk_Y), Chunk_Z(other.Chunk_Z)
{
	/*std::cout
		<< "==== VoxelChunk "
		<< Chunk_X << ":" << Chunk_Y << ":" << Chunk_Z
		<< "\n";*/

	Data = new char[Voxel_per_Chunk];

	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Corner);
	glGenBuffers(1, &Buffer_Index);
}
const VoxelChunk & VoxelChunk::operator =(const VoxelChunk & other)
{
	std::cout << "= VoxelChunk\n";
	(void)other;
	return (*this);
}




bool	VoxelChunk::isChunkIndex(int x, int y, int z) const
{
	return ((Chunk_X == x) && (Chunk_Y == y) && (Chunk_Z == z));
}
void	VoxelChunk::getChunkIndex(int & x, int & y, int & z) const
{
	x = Chunk_X;
	y = Chunk_Y;
	z = Chunk_Z;
}
void	VoxelChunk::FillRandom()
{
	/*for (unsigned i = 0; i < Voxel_per_Chunk; i++)
	{
		Data[i] = std::rand() & 1;
	}*/
	unsigned int half = Voxel_per_Side / 2;
	for (unsigned int z = 0; z < Voxel_per_Side; z++)
	{
		for (unsigned int y = 0; y < Voxel_per_Side; y++)
		{
			for (unsigned int x = 0; x < Voxel_per_Side; x++)
			{
				unsigned int i = XYZ_to_VoxelIndex(x, y, z);
				if (y < half)
					Data[i] = 0;
				else if (y > half)
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
	//std::cout << "Vertex Count:" << vertex_count << " (" << (vertex_count * sizeof(unsigned int)) << "B)\n";
	//std::cout << "Vertex Count:" << vertex_count << " (" << mem_size_1024(vertex_count * sizeof(unsigned int)) << ")\n";

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
	//std::cout << "Index Count: " << index_count << "/" << (Voxel_per_Chunk * 6 * 3) << " (" << (index_count * sizeof(unsigned int)) << "B)\n";

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
/*		Better Buffers
	IndexUnCompressed[MaxIndexCount] = 0xFFFFFFFF
	FaceIndexUnCompressed[MaxFaceCount]

	fill FaceIndexUnCompressed as in UpdateBufferIndex()
		each index used, set IndexUnCompressed[index] = 0
	count IndexFaceCount

	IndexCount = 0
	IndexCompressionMap[MaxIndexCount]
	for each IndexUnCompressed
		if (IndexUnCompressed[i] == 0)
		{
			IndexCompressionMap[i] = IndexCount
			IndexCount++
		}

	VertexCompressed[IndexCount]
	for each IndexUnCompressed
		if IndexUnCompressed[index] == 0
			VertexCompressed[index] = setForVertex(IndexCompressionMap[index])

	FaceIndexCompressed[FaceIndexCount]
	for each FaceIndexUnCompressed
		FaceIndexCompressed[index] = IndexCompressionMap[FaceIndexUnCompressed[index]]

	put VertexCompressed into Buffer
	put FaceIndexCompressed into Buffer
*/
void	VoxelChunk::Draw(int Uni_Chunk_Pos) const
{
	glUniform3i(Uni_Chunk_Pos, Chunk_X, Chunk_Y, Chunk_Z);

	glBindVertexArray(Buffer_Array);
	glDrawElements(GL_TRIANGLES, Index_Count, GL_UNSIGNED_INT, (void*)0);
}

VoxelChunk::ChunkIndex	VoxelChunk::Cross(Point pos, Point dir)
{
	dir.x = -dir.x;
	dir.y = -dir.y;
	//dir.y = 0;

	Point ray_pos = pos;
	Point ray_dir = dir;

	int	ray_grid_idx_x = (int)pos.x;
	int	ray_grid_idx_y = (int)pos.y;
	int	ray_grid_idx_z = (int)pos.z;
	dir = dir / (dir.length());

	float	ray_side_len_x;
	float	ray_side_len_y = 0;
	float	ray_side_len_z;

	//if (dir.x != 0) { ray_side_len_x = dir.z / dir.x; } else { ray_side_len_x = 0xFFFFFFFF; }
	//if (dir.z != 0) { ray_side_len_z = dir.x / dir.z; } else { ray_side_len_z = 0xFFFFFFFF; }
	if (dir.x != 0) { ray_side_len_x = sqrt(dir.y * dir.y + dir.z * dir.z) / dir.x; } else { ray_side_len_x = 0xFFFFFFFF; }
	if (dir.y != 0) { ray_side_len_y = sqrt(dir.z * dir.z + dir.x * dir.x) / dir.y; } else { ray_side_len_y = 0xFFFFFFFF; }
	if (dir.z != 0) { ray_side_len_z = sqrt(dir.x * dir.x + dir.y * dir.y) / dir.z; } else { ray_side_len_z = 0xFFFFFFFF; }

	ray_side_len_x = sqrt(1 + ray_side_len_x * ray_side_len_x);
	ray_side_len_y = sqrt(1 + ray_side_len_y * ray_side_len_y);
	ray_side_len_z = sqrt(1 + ray_side_len_z * ray_side_len_z);

	float ray_sum = 0;



	int	ray_grid_dir_x;
	int	ray_grid_dir_y;
	int	ray_grid_dir_z;

	float	ray_side_sum_x;
	float	ray_side_sum_y;
	float	ray_side_sum_z;

	int	ray_cardinal_side_x;
	int	ray_cardinal_side_y;
	int	ray_cardinal_side_z;

	if (dir.x > 0)
	{
		ray_grid_dir_x = +1;
		ray_side_sum_x = ((ray_grid_idx_x + 1) - pos.x) * ray_side_len_x;
		ray_cardinal_side_x = 1;
	}
	else
	{
		ray_grid_dir_x = -1;
		ray_side_sum_x = (pos.x - ray_grid_idx_x) * ray_side_len_x;
		ray_cardinal_side_x = 2;
	}

	if (dir.y > 0)
	{
		ray_grid_dir_y = +1;
		ray_side_sum_y = ((ray_grid_idx_y + 1) - pos.y) * ray_side_len_y;
		ray_cardinal_side_y = 3;
	}
	else
	{
		ray_grid_dir_y = -1;
		ray_side_sum_y = (pos.y - ray_grid_idx_y) * ray_side_len_y;
		ray_cardinal_side_y = 4;
	}

	if (dir.z > 0)
	{
		ray_grid_dir_z = +1;
		ray_side_sum_z = ((ray_grid_idx_z + 1) - pos.z) * ray_side_len_z;
		ray_cardinal_side_z = 5;
	}
	else
	{
		ray_grid_dir_z = -1;
		ray_side_sum_z = (pos.z - ray_grid_idx_z) * ray_side_len_z;
		ray_cardinal_side_z = 6;
	}

	int	ray_cardinal_dir = 0;



	//Point chunk_off(
	//	Chunk_X * Voxel_per_Side,
	//	Chunk_Y * Voxel_per_Side,
	//	Chunk_Z * Voxel_per_Side
	//);

	while (ray_sum < 100)
	{
		/*if (ray_side_sum_x < ray_side_sum_z)
		{
			ray_sum = ray_side_sum_x;
			ray_side_sum_x += ray_side_len_x;
			ray_grid_idx_x += ray_grid_dir_x;
			ray_cardinal_dir = ray_cardinal_side_x;
		}
		else
		{
			ray_sum = ray_side_sum_z;
			ray_side_sum_z += ray_side_len_z;
			ray_grid_idx_z += ray_grid_dir_z;
			ray_cardinal_dir = ray_cardinal_side_z;
		}*/
		if (ray_side_sum_x < ray_side_sum_y && ray_side_sum_x < ray_side_sum_z)
		{
			ray_sum = ray_side_sum_x;
			ray_side_sum_x += ray_side_len_x;
			ray_grid_idx_x += ray_grid_dir_x;
			ray_cardinal_dir = ray_cardinal_side_x;
		}
		else if (ray_side_sum_y < ray_side_sum_z && ray_side_sum_y < ray_side_sum_z)
		{
			ray_sum = ray_side_sum_y;
			ray_side_sum_y += ray_side_len_y;
			ray_grid_idx_y += ray_grid_dir_y;
			ray_cardinal_dir = ray_cardinal_side_y;
		}
		else
		{
			ray_sum = ray_side_sum_z;
			ray_side_sum_z += ray_side_len_z;
			ray_grid_idx_z += ray_grid_dir_z;
			ray_cardinal_dir = ray_cardinal_side_z;
		}

		if (ray_grid_idx_x < 0 || (unsigned int)ray_grid_idx_x >= Voxel_per_Side ||
			ray_grid_idx_y < 0 || (unsigned int)ray_grid_idx_y >= Voxel_per_Side ||
			ray_grid_idx_z < 0 || (unsigned int)ray_grid_idx_z >= Voxel_per_Side)
		{
			return (ChunkIndex){ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
		}

		if (Data[XYZ_to_VoxelIndex(ray_grid_idx_x, ray_grid_idx_y, ray_grid_idx_z)] != 0)
		{
			Point hit = ray_pos + (ray_dir * ray_sum);
			Box box(
				Point((hit.x - 0.01f), (hit.y - 0.01f), (hit.z - 0.01f)),
				Point((hit.x + 0.01f), (hit.y + 0.01f), (hit.z + 0.01f))
			);
			box.CreateBuffer();
			box.UpdateBuffer();
			box.Draw();
			return (ChunkIndex){ ray_grid_idx_x, ray_grid_idx_y, ray_grid_idx_z };
		}

		/*Box box(
			Point((ray_grid_idx_x + 0), (ray_grid_idx_y + 0), (ray_grid_idx_z + 0)),
			Point((ray_grid_idx_x + 1), (ray_grid_idx_y + 1), (ray_grid_idx_z + 1))
		);
		box.CreateBuffer();
		box.UpdateBuffer();
		box.Draw();*/
	}
	return (ChunkIndex){ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
}

int			VoxelChunk::CheckVoxel(const void * p, int x, int y, int z)
{
	if (x < 0 || x >= (int)Voxel_per_Side ||
		y < 0 || y >= (int)Voxel_per_Side ||
		z < 0 || z >= (int)Voxel_per_Side)
	{
		return (-1);
	}

	VoxelChunk * ch = (VoxelChunk *)p;
	if (ch -> Data[XYZ_to_VoxelIndex(x, y, z)] != 0)
	{
		return (1);
	}

	return (0);
}
