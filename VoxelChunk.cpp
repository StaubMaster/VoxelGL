
#include "VoxelChunk.hpp"

unsigned int VoxelChunk::XYZ_to_VoxelIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Voxel_per_Side) * Voxel_per_Side);
}
unsigned int VoxelChunk::XYZ_to_VertexIndex(unsigned int x, unsigned int y, unsigned int z)
{
	return (x + (y + (z) * Vertex_per_Side) * Vertex_per_Side);
}
unsigned int VoxelChunk::XYZ_to_VoxelIndex(Undex3D udx)
{
	return (udx.x + (udx.y + (udx.z) * Voxel_per_Side) * Voxel_per_Side);
}


void	VoxelChunk::Loop_Index(unsigned int & vox, int & ch)
{
	if (vox == 0xFFFFFFFF)
	{
		vox = Voxel_per_Side - 1;
		ch--;
	}
	else if (vox == Voxel_per_Side)
	{
		vox = 0;
		ch++;
	}
}
void	VoxelChunk::Loop_Index(Undex3D & vox, Index3D & ch)
{
	Loop_Index(vox.x, ch.x);
	Loop_Index(vox.y, ch.y);
	Loop_Index(vox.z, ch.z);
}
void	VoxelChunk::Voxel_Neighbour(char cardinal, Undex3D & vox, Index3D & ch)
{
	if (cardinal == CARDINAL_X_NEGATIVE)
		vox.x--;
	if (cardinal == CARDINAL_X_POSITIVE)
		vox.x++;
	if (cardinal == CARDINAL_Y_NEGATIVE)
		vox.y--;
	if (cardinal == CARDINAL_Y_POSITIVE)
		vox.y++;
	if (cardinal == CARDINAL_Z_NEGATIVE)
		vox.z--;
	if (cardinal == CARDINAL_Z_POSITIVE)
		vox.z++;

	Loop_Index(vox, ch);
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

void VoxelChunk::IndexFaceX(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceXn(index, idx, x, y, z);
			idx += 6;
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceXp(index, idx, x, y, z);
			idx += 6;
		}
	}
}
void VoxelChunk::IndexFaceY(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceYn(index, idx, x, y, z);
			idx += 6;
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceYp(index, idx, x, y, z);
			idx += 6;
		}
	}
}
void VoxelChunk::IndexFaceZ(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceZn(index, idx, x, y, z);
			idx += 6;
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceZp(index, idx, x, y, z);
			idx += 6;
		}
	}
}

void VoxelChunk::IndexFaceX(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (x == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(Voxel_per_Side - 1, y, z);
			vp = &t -> get(0, y, z);
		}
	}
	else if (x == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(Voxel_per_Side, y, z);
			vp = &p -> get(0, y, z);
		}
	}
	else
	{
		vn = &t -> get(x - 1, y, z);
		vp = &t -> get(x - 0, y, z);
	}
	IndexFaceX(index, idx, x, y, z, vn, vp);
}
void VoxelChunk::IndexFaceY(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (y == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(x, Voxel_per_Side - 1, z);
			vp = &t -> get(x, 0, z);
		}
	}
	else if (y == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(x, Voxel_per_Side, z);
			vp = &p -> get(x, 0, z);
		}
	}
	else
	{
		vn = &t -> get(x, y - 1, z);
		vp = &t -> get(x, y - 0, z);
	}
	IndexFaceY(index, idx, x, y, z, vn, vp);
}
void VoxelChunk::IndexFaceZ(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (z == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(x, y, Voxel_per_Side - 1);
			vp = &t -> get(x, y, 0);
		}
	}
	else if (z == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(x, y, Voxel_per_Side);
			vp = &p -> get(x, y, 0);
		}
	}
	else
	{
		vn = &t -> get(x, y, z - 1);
		vp = &t -> get(x, y, z - 0);
	}
	IndexFaceZ(index, idx, x, y, z, vn, vp);
}



VoxelChunk::VoxelChunk(int x, int y, int z) :
	Chunk_X(x), Chunk_Y(y), Chunk_Z(z)
{
	/*std::cout
		<< "++++ VoxelChunk "
		<< Chunk_X << ":" << Chunk_Y << ":" << Chunk_Z
		<< "\n";*/

	Data = new Voxel[Voxel_per_Chunk];

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

	Data = new Voxel[Voxel_per_Chunk];

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
const Voxel	& VoxelChunk::get(unsigned int x, unsigned int y, unsigned int z) const
{
	return (Data[XYZ_to_VoxelIndex(x, y, z)]);
}



bool	VoxelChunk::isChunkIndex(int x, int y, int z) const
{
	return ((Chunk_X == x) && (Chunk_Y == y) && (Chunk_Z == z));
}
bool	VoxelChunk::isChunkIndex(Index3D idx) const
{
	return ((Chunk_X == idx.x) && (Chunk_Y == idx.y) && (Chunk_Z == idx.z));
}
void	VoxelChunk::getChunkIndex(int & x, int & y, int & z) const
{
	x = Chunk_X;
	y = Chunk_Y;
	z = Chunk_Z;
}
Point	VoxelChunk::getChunkOffset() const
{
	return Point(
		Chunk_X * ((int)Voxel_per_Side),
		Chunk_Y * ((int)Voxel_per_Side),
		Chunk_Z * ((int)Voxel_per_Side)
	);
}
void	VoxelChunk::FillRandom()
{
	Index3D chunk_idx;
	chunk_idx.x = Chunk_X * Voxel_per_Side;
	chunk_idx.y = Chunk_Y * Voxel_per_Side;
	chunk_idx.z = Chunk_Z * Voxel_per_Side;

	Undex3D voxel_idx;
	voxel_idx.x = 0;
	voxel_idx.y = 0;
	voxel_idx.z = 0;

	Index3D global_idx;
	unsigned int i;

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = XYZ_to_VoxelIndex(voxel_idx);

		char axis = 0;
		axis += (voxel_idx.x == 0 || voxel_idx.x == Voxel_per_Side - 1);
		axis += (voxel_idx.y == 0 || voxel_idx.y == Voxel_per_Side - 1);
		axis += (voxel_idx.z == 0 || voxel_idx.z == Voxel_per_Side - 1);
		if (axis >= 3)
		{
			Data[i] = Voxel(1);
		}
		else
		{
			Data[i] = Voxel(0);
		}
	}
	while (Undex3D_loop(voxel_idx, 0, Voxel_per_Side));

	(void) global_idx;

	/*Index3D box_min;
	box_min.x = -10;
	box_min.y = -10;
	box_min.z = -10;

	Index3D box_max;
	box_max.x = +10;
	box_max.y = +10;
	box_max.z = +10;

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = XYZ_to_VoxelIndex(voxel_idx);

		if (!Index3D_box_inlusive(global_idx, box_min, box_max))
		{
			Data[i] = Voxel(0);
		}
		else if (Index3D_box_exlusive(global_idx, box_min, box_max))
		{
			Data[i] = Voxel(1);
		}
		else
		{
			Data[i] = Voxel(std::rand() & 1);
		}
	}
	while (Undex3D_loop(voxel_idx, 0, Voxel_per_Side));*/

}
int		VoxelChunk::CheckVoxel(Index3D idx)
{
	if ((idx.x < -1) || (idx.x >= (int)(Voxel_per_Side + 1)) ||
		(idx.y < -1) || (idx.y >= (int)(Voxel_per_Side + 1)) ||
		(idx.z < -1) || (idx.z >= (int)(Voxel_per_Side + 1)))
	{
		//std::cout << "outside\n";
		return (-1);
	}

	if ((idx.x < 0) || (idx.x >= (int)(Voxel_per_Side)) ||
		(idx.y < 0) || (idx.y >= (int)(Voxel_per_Side)) ||
		(idx.z < 0) || (idx.z >= (int)(Voxel_per_Side)))
	{
		//std::cout << "edge\n";
		return (0);
	}

	if (Data[XYZ_to_VoxelIndex(idx.x, idx.y, idx.z)].isSolid())
	{
		return (+1);
	}

	return (0);
}

char	VoxelChunk::tryReplace(Undex3D idx, char d)
{
	unsigned int i = XYZ_to_VoxelIndex(idx);

	char t = Data[i].isSolid();
	Data[i] = Voxel(d);
	return (t);
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

	for (unsigned int z = 0; z < Voxel_per_Side; z++)
	{
		for (unsigned int y = 0; y < Voxel_per_Side; y++)
		{
			for (unsigned int x = 0; x < Voxel_per_Side; x++)
			{
				IndexFaceX(index, index_count, x, y, z, this, Xn, Xp);
				IndexFaceY(index, index_count, x, y, z, this, Yn, Yp);
				IndexFaceZ(index, index_count, x, y, z, this, Zn, Zp);
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
