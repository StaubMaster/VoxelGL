
#include "Structure.hpp"

Structure::Structure(StructureData & data, Index3D global) :
	structureData(data),
	globalPos(global)
{

}

bool	Structure::relativeBool(Index3D global)
{
	Index3D rel_pos = global - globalPos;
	if (rel_pos.x < 0 || rel_pos.x >= (int)structureData.Size.x ||
		rel_pos.y < 0 || rel_pos.y >= (int)structureData.Size.y ||
		rel_pos.z < 0 || rel_pos.z >= (int)structureData.Size.z)
	{
		return false;
	}

	return true;
}
Voxel	Structure::relative(Index3D global)
{
	Index3D rel_pos = global - globalPos;
	if (rel_pos.x < 0 || rel_pos.x >= (int)structureData.Size.x ||
		rel_pos.y < 0 || rel_pos.y >= (int)structureData.Size.y ||
		rel_pos.z < 0 || rel_pos.z >= (int)structureData.Size.z)
	{
		return structureData.Default;
	}

	//std::cout << "rel: " << rel_pos << "\n";
	unsigned int idx = 0;
	idx = rel_pos.z + idx * structureData.Size.z;
	idx = rel_pos.y + idx * structureData.Size.y;
	idx = rel_pos.x + idx * structureData.Size.x;
	//std::cout << "idx: " << idx << "\n";

	return structureData.Data[idx];
}
