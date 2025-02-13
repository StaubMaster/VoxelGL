
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



#pragma region RenderData
VoxelChunk::RenderData::RenderData()
{
	//std::cout << "++++ VoxelChunk::RenderData\n";
	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Corner);
	glGenBuffers(1, &Buffer_Index);
	Vertex_Count = 0;

	NeedsUpdate = false;
	NeedsBind = false;
	BufferStream = NULL;
}
VoxelChunk::RenderData::~RenderData()
{
	//std::cout << "---- VoxelChunk::RenderData\n";
	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Corner);
	glDeleteBuffers(1, &Buffer_Index);
	glDeleteVertexArrays(1, &Buffer_Array);
}
void	VoxelChunk::RenderData::RequestUpdate()
{
	NeedsUpdate = true;
}
void	VoxelChunk::RenderData::Update(const VoxelChunk * here,
	const VoxelChunk * Xn, const VoxelChunk * Xp,
	const VoxelChunk * Yn, const VoxelChunk * Yp,
	const VoxelChunk * Zn, const VoxelChunk * Zp)
{
	if (NeedsUpdate && BufferStream == NULL)
	{
		//std::cout << "BufferUpdate() " << Index << " ...\n";
		NeedsUpdate = false;
		BufferStream = new VoxelRenderData::DataStream(Vertex_per_Chunk * 6 * 6);

		Undex3D voxel_idx;
		do
		{
			BufferStream -> FaceX(voxel_idx, here, Xn, Xp);
			BufferStream -> FaceY(voxel_idx, here, Yn, Yp);
			BufferStream -> FaceZ(voxel_idx, here, Zn, Zp);
		}
		while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side + 1));

		NeedsBind = true;
		//std::cout << "BufferUpdate() " << Index << " done\n";
	}
}
void	VoxelChunk::RenderData::Bind()
{
	if (NeedsBind && BufferStream != NULL)
	{
		//std::cout << "BufferBind() " << Index << " ...\n";
		NeedsBind = false;

		glBindVertexArray(Buffer_Array);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);
		BufferStream -> ToBuffer(Vertex_Count);

		delete BufferStream;
		BufferStream = NULL;
		//std::cout << "BufferBind() " << Index << " done\n";
	}
}
void	VoxelChunk::RenderData::Draw() const
{
	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_TRIANGLES, 0, Vertex_Count);
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



#pragma region Generate
void	VoxelChunk::GenerateChunkLimit(VoxelDataTable & table, char axis_limit)
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
			Data[i] = Voxel();
		}
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
	(void)table;
}
void	VoxelChunk::GenerateFuzzyCenterCube(VoxelDataTable & table, int size2)
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

	VoxelOrientation	ori(0, 0);

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = voxel_idx.ToIndex(Voxel_per_Side);

		if (!Index3D::Box_inclusive(global_idx, box_min, box_max))
		{
			Data[i] = Voxel();
		}
		else if (Index3D::Box_exclusive(global_idx, box_min, box_max))
		{
			//ori = ((std::rand() % 6) + 1) | ((std::rand() % 4) << 3);
			ori = VoxelOrientation(AXIS_BITS_RAND, AXIS_BITS_RAND);
			Data[i] = Voxel(1, 0, ori);
		}
		else
		{
			if ((std::rand() & 1) == 0)
			{
				Data[i] = Voxel();
			}
			else
			{
				//ori = ((std::rand() % 6) + 1) | ((std::rand() % 4) << 3);
				ori = VoxelOrientation(AXIS_BITS_RAND, AXIS_BITS_RAND);
				Data[i] = Voxel(1, 0, ori);
			}
		}
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
	(void)table;
}
void	VoxelChunk::GenerateVoxelRotationTest(VoxelDataTable & table)
{
	Index3D chunk_idx;
	chunk_idx.x = Index.x * Voxel_per_Side;
	chunk_idx.y = Index.y * Voxel_per_Side;
	chunk_idx.z = Index.z * Voxel_per_Side;

	Undex3D voxel_idx;
	Index3D global_idx;
	unsigned int i;

	int X, Y, Z;
	char ori;

	do
	{
		global_idx.x = chunk_idx.x + voxel_idx.x;
		global_idx.y = chunk_idx.y + voxel_idx.y;
		global_idx.z = chunk_idx.z + voxel_idx.z;
		i = voxel_idx.ToIndex(Voxel_per_Side);

		Data[i] = Voxel();
		if (global_idx.x % 2 == 0 && global_idx.y % 4 == 0 && global_idx.z % 2 == 0)
		//if (global_idx.x % 2 == 0 && global_idx.z % 2 == 0)
		{
			X = global_idx.x / 2;
			Y = global_idx.y / 4;
			//Y = global_idx.y;
			Z = global_idx.z / 2;

			if (X >= 0 && X < 6 && Z >= 0 && Z < 4 && Y >= 0 && Y < 5)
			{
				ori = (X + 1) | (Z << 3);
				//Data[i] = Voxel(Y, 0, ori);
				Data[i] = table.Get(Y).ToVoxelForce(Y, ori);
			}
		}
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));
	(void)table;
}
void	VoxelChunk::GenerateTree(VoxelDataTable & table, Index3D tree_base)
{
	unsigned int i;

	Index3D min;
	Index3D max;

	min = tree_base;
	max = tree_base;
	max.y += 10;

	do
	{
		i = tree_base.ToIndex(Voxel_per_Side);
		//if (Data[i].getID() == table.Get(2))
		Data[i] = table.Get(2).ToVoxel(2, AXIS_BITS_YN | (std::rand() % 4) << 3);
	}
	while (Index3D::loop_inclusive(tree_base, min, max));
}
void	VoxelChunk::set(VoxelChunk * * chunks, Undex3D udx, Voxel vox)
{
	if (udx.x >= Voxel_per_Side)
	{
		udx.x -= Voxel_per_Side;
		if (udx.z >= Voxel_per_Side)
		{
			udx.z -= Voxel_per_Side;
			chunks[3] -> Data[udx.ToIndex(Voxel_per_Side)] = vox;
		}
		else
		{
			chunks[1] -> Data[udx.ToIndex(Voxel_per_Side)] = vox;
		}
	}
	else
	{
		if (udx.z >= Voxel_per_Side)
		{
			udx.z -= Voxel_per_Side;
			chunks[2] -> Data[udx.ToIndex(Voxel_per_Side)] = vox;
		}
		else
		{
			chunks[0] -> Data[udx.ToIndex(Voxel_per_Side)] = vox;
		}
	}
}
void	VoxelChunk::GenerateFeature(VoxelDataTable & table, VoxelChunk * * chunks)
{
	if (chunks[0] -> Index.y != 0)
		return;

	//std::cout << "new ...\n";
	StructureData structData;
	structData.Size = Undex3D(5, 5, 5);
	structData.Data = new Voxel[5 * 5 * 5];
	structData.Default = Voxel();
	//std::cout << "ptr " << structData.Data << "\n";
	//std::cout << "new done\n";

	//std::cout << "Data ...\n";
	Undex3D zero;
	Undex3D structPos = zero;
	unsigned int idx = 0;
	do
	{
		//if (!Undex3D::loop_inclusive(structPos, zero, structData.Size))
		if (zero.x == structPos.x || structPos.x == structData.Size.x - 1 ||
			zero.y == structPos.y || structPos.y == structData.Size.y - 1 ||
			zero.z == structPos.z || structPos.z == structData.Size.z - 1)
		{
			structData.Data[idx] = table.Get(2).ToVoxel(2, AXIS_BITS_RAND);
		}
		else
		{
			structData.Data[idx] = Voxel();
		}
		idx++;
	}
	while (Undex3D::loop_exclusive(structPos, zero, structData.Size));
	//std::cout << "Data done\n";

	//std::cout << "Structure ...\n";
	Index3D	offset = chunks[0] -> getChunkVoxelIndex3D();
	Structure structure(structData, offset + Index3D(2, 2, 2));
	//std::cout << "Structure done\n";

	Index3D	global_idx;
	Undex3D	voxel_idx;
	//std::cout << "set ...\n";
	do
	{
		global_idx.x = offset.x + voxel_idx.x;
		global_idx.y = offset.y + voxel_idx.y;
		global_idx.z = offset.z + voxel_idx.z;
		idx = voxel_idx.ToIndex(Voxel_per_Side);

		if (structure.relativeBool(global_idx))
		{
			//std::cout << "glob: " << voxel_idx << "\n";
			//std::cout << "idx " << idx << "\n";
			chunks[0] -> Data[idx] = structure.relative(global_idx);
		}
	}
	while (Undex3D::loop_inclusive(voxel_idx, 0, Voxel_per_Side - 1));
	//std::cout << "set done\n";

	//std::cout << "delete ...\n";
	//std::cout << "ptr " << structData.Data << "\n";
	delete [] structData.Data;
	//std::cout << "delete done\n";

	//Voxel stem = table.Get(2).ToVoxel(2, AXIS_BITS_YN | (std::rand() % 4) << 3);
	//Voxel leave = table.Get(3).ToVoxel(3, AXIS_BITS_YN | (std::rand() % 4) << 3);

	/*Undex3D udx;

	Undex3D	tree_base(std::rand() % Voxel_per_Side, 2, std::rand() % Voxel_per_Side);
	tree_base.x += Voxel_per_Side / 2;
	tree_base.z += Voxel_per_Side / 2;

	Undex3D	tree_crown = tree_base;
	tree_crown.y += 3 + (std::rand() % 7);

	Undex3D leaves_min;
	leaves_min.x = tree_crown.x - 2;
	leaves_min.y = tree_crown.y - 2;
	leaves_min.z = tree_crown.z - 2;
	Undex3D leaves_max;
	leaves_max.x = tree_crown.x + 2;
	leaves_max.y = tree_crown.y + 2;
	leaves_max.z = tree_crown.z + 2;

	udx = leaves_min;
	do
	{
		Point diff;
		diff.x = ((float)udx.x) - ((float)tree_crown.x);
		diff.y = ((float)udx.y) - ((float)tree_crown.y);
		diff.z = ((float)udx.z) - ((float)tree_crown.z);

		float dist = diff.length();

		if (dist <= 2)
		{
			set(chunks, udx, table.Get(3).ToVoxel(3, AXIS_BITS_YN | (std::rand() % 4) << 3));
		}
	}
	while (Undex3D::loop_inclusive(udx, leaves_min, leaves_max));

	udx = tree_base;
	do
	{
		set(chunks, udx, table.Get(2).ToVoxel(2, AXIS_BITS_YN | (std::rand() % 4) << 3));
	}
	while (Undex3D::loop_inclusive(udx, tree_base, tree_crown));*/
}
void	VoxelChunk::GeneratePlane(VoxelDataTable & table)
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

		//if (global_idx.y >= -16 && global_idx.y < 16)
		if (global_idx.y >= -1 && global_idx.y < 1)
		{
			Data[i] = table.Get(1).ToVoxel(1, 0);
			continue;
		}
		Data[i] = Voxel();
	}
	while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side));

	/*if (chunk_idx.y == 0)
	{
		Index3D tree_base(std::rand() % Voxel_per_Side, 1, std::rand() % Voxel_per_Side);
		GenerateTree(table, tree_base);
	}*/
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
