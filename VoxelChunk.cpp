
#include "VoxelChunk.hpp"



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
	return (Data[idx.ToIndex(Voxel_per_Side)]);
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

void	VoxelChunk::GenerateChunkLimit(char axis_limit)
{
	Index3D chunk_idx;
	chunk_idx.x = Index.x * Voxel_per_Side;
	chunk_idx.y = Index.y * Voxel_per_Side;
	chunk_idx.z = Index.z * Voxel_per_Side;

	Undex3D voxel_idx;
	Index3D global_idx;
	unsigned int i;

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = voxel_idx.ToIndex(Voxel_per_Side);

		char axis = 0;
		axis += (voxel_idx.x == 0 || voxel_idx.x == Voxel_per_Side - 1);
		axis += (voxel_idx.y == 0 || voxel_idx.y == Voxel_per_Side - 1);
		axis += (voxel_idx.z == 0 || voxel_idx.z == Voxel_per_Side - 1);
		if (axis >= axis_limit)
		{
			Data[i] = Voxel(1);
		}
		else
		{
			Data[i] = Voxel(0);
		}
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
}
void	VoxelChunk::GenerateFuzzyCenterCube(int size2)
{
	Index3D chunk_idx;
	chunk_idx.x = Index.x * Voxel_per_Side;
	chunk_idx.y = Index.y * Voxel_per_Side;
	chunk_idx.z = Index.z * Voxel_per_Side;

	Undex3D voxel_idx;
	Index3D global_idx;
	unsigned int i;

	Index3D box_min(-size2);
	Index3D box_max(+size2);

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = voxel_idx.ToIndex(Voxel_per_Side);

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
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
}
void	VoxelChunk::GenerateVoxelRotationTest()
{
	Index3D chunk_idx;
	chunk_idx.x = Index.x * Voxel_per_Side;
	chunk_idx.y = Index.y * Voxel_per_Side;
	chunk_idx.z = Index.z * Voxel_per_Side;

	Undex3D voxel_idx;
	Index3D global_idx;
	unsigned int i;

	int X, Y, Z;

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = voxel_idx.ToIndex(Voxel_per_Side);

		Data[i] = Voxel(0);
		if (global_idx.x % 2 == 0 && global_idx.y % 2 == 0 && global_idx.z % 2 == 0)
		{
			X = global_idx.x / 2;
			Y = global_idx.y / 2;
			Z = global_idx.z / 2;

			if (X >= 1 && X <= 4 && Y == 0 && Z == 0)
			{
				char rot = X - 1;
				Data[i] = Voxel(1, rot);
			}

			if (Y >= 1 && Y <= 4 && X == 0 && Z == 0)
			{
				char rot = (Y - 1) + 4;
				Data[i] = Voxel(1, rot);
			}
			
			if (Z >= 1 && Z <= 4 && X == 0 && Y == 0)
			{
				char rot = (Z - 1) + 8;
				Data[i] = Voxel(1, rot);
			}
		}
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
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

	if (Data[idx.ToIndex(Voxel_per_Side)].isSolid())
	{
		return (+1);
	}

	return (0);
}
char	VoxelChunk::tryReplace(Undex3D idx, char d)
{
	unsigned int i = idx.ToIndex(Voxel_per_Side);

	char t = Data[i].isSolid();
	Data[i] = Voxel(d);
	return (t);
}



void	VoxelChunk::UpdateBuffer(
	const VoxelChunk * Xn, const VoxelChunk * Xp,
	const VoxelChunk * Yn, const VoxelChunk * Yp,
	const VoxelChunk * Zn, const VoxelChunk * Zp)
{
	//std::cout << "UpdateBuffer() " << Index << " ...\n";

	//VoxelRenderData * data = new VoxelRenderData[Vertex_per_Chunk * 6 * 6];
	//unsigned int vertex_count = 0;

	VoxelRenderData::DataStream	data(Vertex_per_Chunk * 6 * 6);

	Undex3D voxel_idx;
	do
	{
		data.FaceX(voxel_idx, this, Xn, Xp);
		data.FaceY(voxel_idx, this, Yn, Yp);
		data.FaceZ(voxel_idx, this, Zn, Zp);
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side + 1));

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);

	data.ToBuffer(Vertex_Count);

	//std::cout << "UpdateBuffer() " << Index << " done\n";
}
void	VoxelChunk::Draw(int Uni_Chunk_Pos) const
{
	//std::cout << "draw\n";
	glUniform3i(Uni_Chunk_Pos, Index.x, Index.y, Index.z);

	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_TRIANGLES, 0, Vertex_Count);
}
