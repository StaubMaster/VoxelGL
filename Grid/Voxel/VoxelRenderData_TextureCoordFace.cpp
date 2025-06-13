#include "VoxelRenderData.hpp"
#include "../Chunk/VoxelChunk.hpp"



void	VoxelRenderData::TextureCoordFace::getCorner(float & x, float & y, bool Xbool, bool Ybool, bool swap) const
{
	if (!swap)
	{
		if (!Xbool) { x = min_x; } else { x = max_x; }
		if (!Ybool) { y = min_y; } else { y = max_y; }
	}
	else
	{
		if (!Ybool) { x = min_x; } else { x = max_x; }
		if (!Xbool) { y = max_y; } else { y = min_y; }
	}
}

VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::FlipX() const
{
	return ((TextureCoordFace) {
		max_x,
		min_x,
		min_y,
		max_y,
	});
}
VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::FlipY() const
{
	return ((TextureCoordFace) {
		min_x,
		max_x,
		max_y,
		min_y,
	});
}
VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::Spin() const
{
	return ((TextureCoordFace) {
		max_x,
		min_x,
		max_y,
		min_y,
	});
}
