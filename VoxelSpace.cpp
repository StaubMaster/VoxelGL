
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
	//Chunks.push_back(VoxelChunk(0, 0, 0));
}
VoxelSpace::~VoxelSpace()
{
	std::cout << "---- VoxelSpace\n";

	Chunks.clear();
}

void	VoxelSpace::FillRandom()
{
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
		min.x = x * (int)(VoxelChunk::Voxel_per_Side + 1);
		min.y = y * (int)(VoxelChunk::Voxel_per_Side + 1);
		min.z = z * (int)(VoxelChunk::Voxel_per_Side + 1);
		max.x = min.x + (int)(VoxelChunk::Voxel_per_Side + 1);
		max.y = min.y + (int)(VoxelChunk::Voxel_per_Side + 1);
		max.z = min.z + (int)(VoxelChunk::Voxel_per_Side + 1);

		Box box(min, max);
		box.CreateBuffer();
		box.UpdateBuffer();
		box.Draw();
	}
}


void	VoxelSpace::Cross(Point pos, Point dir)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{

	}


	if (Chunks.size() > 0)
	{
		int x, y, z;
		Chunks[0].getChunkIndex(x, y, z);

		Point chunk_off(
			x * ((int)VoxelChunk::Voxel_per_Side + 1),
			y * ((int)VoxelChunk::Voxel_per_Side + 1),
			z * ((int)VoxelChunk::Voxel_per_Side + 1)
		);

		Point rel_pos = pos - chunk_off;

		VoxelHit hit = VoxelCross(rel_pos, dir, &Chunks[0], VoxelChunk::CheckVoxel);

		if (hit.isHit)
		{
			Box box(
				Point((hit.x + 0) - 0.1f, (hit.y + 0) - 0.1f, (hit.z + 0) - 0.1f) + chunk_off,
				Point((hit.x + 1) + 0.1f, (hit.y + 1) + 0.1f, (hit.z + 1) + 0.1f) + chunk_off
			);
			box.CreateBuffer();
			box.UpdateBuffer();
			box.Draw();
		}
	}
}
int	VoxelSpace::CheckChunk(const void * p, int x, int y, int z)
{
	

	return (0);
}
