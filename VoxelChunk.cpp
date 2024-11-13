
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



void VoxelChunk::IndexFaceXn(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 0);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 1);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 1);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 0);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 1);
	idx += 6;
}
void VoxelChunk::IndexFaceXp(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 1);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 0);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 0);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x, vox.y + 0, vox.z + 1);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x, vox.y + 1, vox.z + 1);
	idx += 6;
}
void VoxelChunk::IndexFaceYn(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 1);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 0);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 0);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 1);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 1);
	idx += 6;
}
void VoxelChunk::IndexFaceYp(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 0);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 0);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 1);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x + 0, vox.y, vox.z + 1);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 0);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x + 1, vox.y, vox.z + 1);
	idx += 6;
}
void VoxelChunk::IndexFaceZn(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 0, vox.z);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 0, vox.z);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 1, vox.z);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 1, vox.z);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 0, vox.z);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 1, vox.z);
	idx += 6;
}
void VoxelChunk::IndexFaceZp(unsigned int * index, unsigned int & idx, Undex3D vox)
{
	index[idx + 0] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 0, vox.z);
	index[idx + 1] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 1, vox.z);
	index[idx + 2] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 0, vox.z);
	index[idx + 3] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 0, vox.z);
	index[idx + 4] = XYZ_to_VertexIndex(vox.x + 0, vox.y + 1, vox.z);
	index[idx + 5] = XYZ_to_VertexIndex(vox.x + 1, vox.y + 1, vox.z);
	idx += 6;
}

void VoxelChunk::IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceXn(index, idx, vox);
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceXp(index, idx, vox);
		}
	}
}
void VoxelChunk::IndexFaceY(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceYn(index, idx, vox);
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceYp(index, idx, vox);
		}
	}
}
void VoxelChunk::IndexFaceZ(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp)
{
	if (vn != NULL && vp != NULL)
	{
		if (vn -> isSolid() && !vp -> isSolid())
		{
			IndexFaceZn(index, idx, vox);
		}
		if (!vn -> isSolid() && vp -> isSolid())
		{
			IndexFaceZp(index, idx, vox);
		}
	}
}

void VoxelChunk::IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	if (vox.y == Voxel_per_Side || vox.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox.x == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(vox.set_get_X(Voxel_per_Side - 1));
			vp = &t -> get(vox.set_get_X(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox.x == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(vox.set_get_X(Voxel_per_Side - 1));
			vp = &p -> get(vox.set_get_X(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &t -> get(vox.set_get_X(vox.x - 1));
		vp = &t -> get(vox.set_get_X(vox.x - 0));
	}
	IndexFaceX(index, idx, vox, vn, vp);
}
void VoxelChunk::IndexFaceY(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	if (vox.x == Voxel_per_Side || vox.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox.y == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(vox.set_get_Y(Voxel_per_Side - 1));
			vp = &t -> get(vox.set_get_Y(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox.y == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(vox.set_get_Y(Voxel_per_Side - 1));
			vp = &p -> get(vox.set_get_Y(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &t -> get(vox.set_get_Y(vox.y - 1));
		vp = &t -> get(vox.set_get_Y(vox.y - 0));
	}
	IndexFaceY(index, idx, vox, vn, vp);
}
void VoxelChunk::IndexFaceZ(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p)
{
	if (vox.x == Voxel_per_Side || vox.y == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox.z == 0)
	{
		if (n != NULL)
		{
			vn = &n -> get(vox.set_get_Z(Voxel_per_Side - 1));
			vp = &t -> get(vox.set_get_Z(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox.z == Voxel_per_Side)
	{
		if (p != NULL)
		{
			vn = &t -> get(vox.set_get_Z(Voxel_per_Side - 1));
			vp = &p -> get(vox.set_get_Z(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &t -> get(vox.set_get_Z(vox.z - 1));
		vp = &t -> get(vox.set_get_Z(vox.z - 0));
	}
	IndexFaceZ(index, idx, vox, vn, vp);
}



VoxelChunk::VoxelChunk(Index3D idx) :
	Index(idx)
{
	/*std::cout
		<< "++++ VoxelChunk "
		<< Index.x << ":" << Index.y << ":" << Index.z
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
		<< Index.x << ":" << Index.y << ":" << Index.z
		<< "\n";*/

	delete [] Data;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Corner);
	glDeleteBuffers(1, &Buffer_Index);
	glDeleteVertexArrays(1, &Buffer_Array);
}
VoxelChunk::VoxelChunk(const VoxelChunk & other) :
	Index(other.Index)
{
	/*std::cout
		<< "==== VoxelChunk "
		<< Index.x << ":" << Index.y << ":" << Index.z
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
const Voxel	& VoxelChunk::get(Undex3D idx) const
{
	return (Data[XYZ_to_VoxelIndex(idx.x, idx.y, idx.z)]);
}



bool	VoxelChunk::isChunkIndex(Index3D idx) const
{
	return ((Index.x == idx.x) && (Index.y == idx.y) && (Index.z == idx.z));
}
Index3D	VoxelChunk::getChunkIndex3D() const
{
	return Index3D(Index.x, Index.y, Index.z);
}
Point	VoxelChunk::getChunkOffset() const
{
	return Point(
		Index.x * ((int)Voxel_per_Side),
		Index.y * ((int)Voxel_per_Side),
		Index.z * ((int)Voxel_per_Side)
	);
}



void	VoxelChunk::FillRandom()
{
	Index3D chunk_idx;
	chunk_idx.x = Index.x * Voxel_per_Side;
	chunk_idx.y = Index.y * Voxel_per_Side;
	chunk_idx.z = Index.z * Voxel_per_Side;

	Undex3D voxel_idx;

	Index3D global_idx;
	unsigned int i;

	/*do
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
	while (Undex3D::loop(voxel_idx, 0, Voxel_per_Side));*/

	Index3D box_min;
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

		if (!Index3D::Box_inclusive(global_idx, box_min, box_max))
		{
			Data[i] = Voxel(0);
		}
		else if (Index3D::Box_exclusive(global_idx, box_min, box_max))
		{
			Data[i] = Voxel(1);
		}
		else
		{
			Data[i] = Voxel(std::rand() & 1);
		}
	}
	while (Undex3D::loop(voxel_idx, 0, Voxel_per_Side));

	(void)global_idx;
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

	Undex3D voxel_idx;
	do
	{
		IndexFaceX(index, index_count, voxel_idx, this, Xn, Xp);
		IndexFaceY(index, index_count, voxel_idx, this, Yn, Yp);
		IndexFaceZ(index, index_count, voxel_idx, this, Zn, Zp);
	}
	while (Undex3D::loop(voxel_idx, 0, Voxel_per_Side + 1));

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
	glUniform3i(Uni_Chunk_Pos, Index.x, Index.y, Index.z);

	glBindVertexArray(Buffer_Array);
	glDrawElements(GL_TRIANGLES, Index_Count, GL_UNSIGNED_INT, (void*)0);
}
