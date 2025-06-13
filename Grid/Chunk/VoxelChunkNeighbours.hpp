
#pragma once

# include "VoxelChunk.hpp"

/*	3x3x3
local chunks
use for generation / updating

*/

struct VoxelChunkNeighbours
{
	VoxelChunk * Hood;

	VoxelChunkNeighbours();
	~VoxelChunkNeighbours();

	bool IsAllBase();
};
