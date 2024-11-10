
#include "VoxelSpace.hpp"

VoxelSpace::VoxelSpace()
{
	std::cout << "++++ VoxelSpace\n";

	Chunks.clear();
	for (int z = -0; z <= +1; z++)
	{
		for (int y = -0; y <= +1; y++)
		{
			for (int x = -0; x <= +1; x++)
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
