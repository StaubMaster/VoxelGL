
#include "VoxelSpace.hpp"

VoxelSpace::VoxelSpace()
{
	std::cout << "++++ VoxelSpace\n";

	Chunks.clear();
	for (int z = -2; z < +2; z++)
	{
		for (int y = -2; y < +2; y++)
		{
			for (int x = -2; x < +2; x++)
			{
				Chunks.push_back(VoxelChunk(x, y, z));
			}
		}
	}

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i].FillRandom();
		Chunks[i].UpdateBufferVertex();
	}

	int x, y, z;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i].getChunkIndex(x, y, z);
		Chunks[i].UpdateBufferIndex(
			FindChunkPtr(x - 1, y, z), FindChunkPtr(x + 1, y, z),
			FindChunkPtr(x, y - 1, z), FindChunkPtr(x, y + 1, z),
			FindChunkPtr(x, y, z - 1), FindChunkPtr(x, y, z + 1)
		);
	}
}
VoxelSpace::~VoxelSpace()
{
	std::cout << "---- VoxelSpace\n";

	Chunks.clear();
}

VoxelChunk *	VoxelSpace::FindChunkPtr(int x, int y, int z)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk & ch = Chunks[i];
		if (ch.isChunkIndex(x, y, z))
			return (&ch);
	}
	return (NULL);
}

void	VoxelSpace::Draw(int Uni_Chunk_Pos) const
{
	for (size_t i = 0; i < Chunks.size(); i++)
		Chunks[i].Draw(Uni_Chunk_Pos);
}
void	VoxelSpace::DrawBound() const
{
	int x, y, z;
	Point min, max;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i].getChunkIndex(x, y, z);
		min.x = x * 4 * (int)(VoxelChunk::Voxel_per_Side);
		min.y = y * 4 * (int)(VoxelChunk::Voxel_per_Side);
		min.z = z * 4 * (int)(VoxelChunk::Voxel_per_Side);
		max.x = min.x + 4 * (int)(VoxelChunk::Voxel_per_Side);
		max.y = min.y + 4 * (int)(VoxelChunk::Voxel_per_Side);
		max.z = min.z + 4 * (int)(VoxelChunk::Voxel_per_Side);

		Box box(min, max);
		box.CreateBuffer();
		box.UpdateBuffer();
		box.Draw();
	}
}


