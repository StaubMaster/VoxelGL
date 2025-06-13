
#include "VoxelChunk.hpp"



#pragma region Loop Neighbour
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
	if (cardinal == AXIS_BITS_XN)
		vox.x--;
	if (cardinal == AXIS_BITS_XP)
		vox.x++;
	if (cardinal == AXIS_BITS_YN)
		vox.y--;
	if (cardinal == AXIS_BITS_YP)
		vox.y++;
	if (cardinal == AXIS_BITS_ZN)
		vox.z--;
	if (cardinal == AXIS_BITS_ZP)
		vox.z++;

	Loop_Index(vox, ch);
}
#pragma endregion



#pragma region Canonical
VoxelChunk::VoxelChunk(Index3D idx) :
	Index(idx)
{
	/*std::cout
		<< "++++ VoxelChunk "
		<< Index.x << ":" << Index.y << ":" << Index.z
		<< "\n";*/

	Data = new Voxel[Voxel_per_Chunk];

	NeedsGeneration1 = true;
	NeedsGeneration2 = false;
}
VoxelChunk::~VoxelChunk()
{
	/*std::cout
		<< "---- VoxelChunk "
		<< Index.x << ":" << Index.y << ":" << Index.z
		<< "\n";*/

	delete [] Data;
}
//VoxelChunk::VoxelChunk(const VoxelChunk & other) :
//	Index(other.Index)
//{
//	/*std::cout
//		<< "==== VoxelChunk "
//		<< Index.x << ":" << Index.y << ":" << Index.z
//		<< "\n";*/
//
//	Data = new Voxel[Voxel_per_Chunk];
//
//	glGenVertexArrays(1, &Buffer_Array);
//	glGenBuffers(1, &Buffer_Corner);
//	glGenBuffers(1, &Buffer_Index);
//}
//const VoxelChunk & VoxelChunk::operator =(const VoxelChunk & other)
//{
//	std::cout << "= VoxelChunk\n";
//	(void)other;
//	return (*this);
//}
#pragma endregion



#pragma region Miscellaneous
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
Index3D	VoxelChunk::getChunkVoxelIndex3D() const
{
	return Index3D(
		Index.x * ((int)Voxel_per_Side),
		Index.y * ((int)Voxel_per_Side),
		Index.z * ((int)Voxel_per_Side)
	);
}
Point	VoxelChunk::getChunkOffset() const
{
	return Point(
		Index.x * ((int)Voxel_per_Side),
		Index.y * ((int)Voxel_per_Side),
		Index.z * ((int)Voxel_per_Side)
	);
}

#pragma endregion



#pragma region Hover
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
#pragma endregion



#pragma region Change
void	VoxelChunk::tryAdd(VoxelDataTable & table, VoxelHover hover, char id)
{
	unsigned int i = hover.voxel_idx.ToIndex(Voxel_per_Side);

	if (!Data[i].isSolid())
	{
		//Data[i] = Voxel(id, 0, (axis | ((std::rand() % 4) << 3)));
		Data[i] = table.Get(id).ToVoxel(id, hover);
	}
}
char	VoxelChunk::trySub(VoxelHover hover)
{
	unsigned int i = hover.voxel_idx.ToIndex(Voxel_per_Side);

	char t = Data[i].isSolid();
	Data[i] = Voxel(0);
	return (t);
}
#pragma endregion



#pragma region Collision
bool	VoxelChunk::IntersektBool(AxisBox & box)
{
	Point offset = getChunkOffset();
	Index3D voxel_min = Index3D::Floor(box.Min - offset);
	Index3D voxel_max = Index3D::Ceil(box.Max - offset);
	voxel_min.Clamp(0, Voxel_per_Side - 1);
	voxel_max.Clamp(0, Voxel_per_Side - 1);

	Index3D i = voxel_min;
	do
	{
		Voxel & vox = Data[i.ToIndex(Voxel_per_Side)];
		if (vox.isDraw())
		{
			AxisBox	vox_box = AxisBox::UnitBox(i);
			vox_box.Move(offset);

			if (AxisBox::IntersektBool(vox_box, box))
				return (true);
		}
	}
	while (Index3D::loop_exclusive(i, voxel_min, voxel_max));

	return (false);
}
char	VoxelChunk::TouchVoxel(AxisBox & box, float size)
{
	Point offset = getChunkOffset();
	Index3D voxel_min = Index3D::Floor((box.Min - offset) - size);
	Index3D voxel_max = Index3D::Ceil((box.Max - offset) - size);
	voxel_min.Clamp(0, Voxel_per_Side - 1);
	voxel_max.Clamp(0, Voxel_per_Side - 1);

	char	bits = 0;
	Index3D i = voxel_min;
	do
	{
		Voxel & vox = Data[i.ToIndex(Voxel_per_Side)];
		if (vox.isDraw())
		{
			AxisBox	vox_box = AxisBox::UnitBox(i);
			vox_box.Move(offset);

			vox_box.CreateBuffer();
			vox_box.UpdateBuffer();
			vox_box.Draw();

			bits |= AxisBox::TouchBits(vox_box, box, size);
		}
	}
	while (Index3D::loop_inclusive(i, voxel_min, voxel_max));

	return (bits);
}
#pragma endregion



#pragma region Rendering
void	VoxelChunk::RequestBufferUpdate()
{
	if (!NeedsGeneration1 && !NeedsGeneration2)
	{
		Render.RequestUpdate();
	}
}
void	VoxelChunk::Draw(int Uni_Chunk_Pos) const
{
	//std::cout << "draw\n";
	glUniform3i(Uni_Chunk_Pos, Index.x, Index.y, Index.z);
	Render.Draw();
}
#pragma endregion



#pragma region Info
unsigned int	VoxelChunk::GeneralInfoMemData()
{
	return (Voxel_per_Chunk * sizeof(Voxel));
}
unsigned int	VoxelChunk::GeneralInfoMemBuff()
{
	return (Render.Vertex_Count * sizeof(VoxelRenderData));
}
#pragma endregion
