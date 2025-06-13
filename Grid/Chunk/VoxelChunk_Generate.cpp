#include "VoxelChunk.hpp"



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


