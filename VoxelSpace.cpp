
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
		Point chunk_off = Chunks[0].getChunkOffset();
		Point chunk_norm_pos = pos / (VoxelChunk::Voxel_per_Side + 1);

		Point rel_pos = pos - chunk_off;

		//RayCast3D_Hit hit = RayCast3D(rel_pos, dir, 128, &Chunks[0], VoxelChunk::CheckVoxel);
		//RayCast3D_Data data = RayCast3D_init(rel_pos, dir);
		RayCast3D_Data data = RayCast3D_init(chunk_norm_pos, dir);
		RayCast3D_Hit hit_voxel;
		hit_voxel.t = 0;
		hit_voxel.cardinal = 0;
		hit_voxel.isHit = false;
		while (hit_voxel.t < 128)
		{
			//int check = VoxelChunk::CheckVoxel(&Chunks[0], data.grid_idx);
			int check = CheckChunk(this, data.grid_idx);
			if (check < 0)
			{
				hit_voxel.isHit = false;
				break;
			}
			else if (check > 0)
			{
				hit_voxel = RayCast3D_hit(hit_voxel, data);
				break;
			}

			hit_voxel = RayCast3D_continue(data);
		}

		if (hit_voxel.isHit)
		{
			std::cout << "chunk " << hit_voxel.idx.x << ":" << hit_voxel.idx.y << ":" << hit_voxel.idx.z << "\n";
			//Box box(
			//	Point((hit_voxel.x + 0) - 0.1f, (hit_voxel.y + 0) - 0.1f, (hit_voxel.z + 0) - 0.1f) + chunk_off,
			//	Point((hit_voxel.x + 1) + 0.1f, (hit_voxel.y + 1) + 0.1f, (hit_voxel.z + 1) + 0.1f) + chunk_off
			//);
			Box box(
				Point(
					((hit_voxel.idx.x + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
					((hit_voxel.idx.y + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
					((hit_voxel.idx.z + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f),
				Point(
					((hit_voxel.idx.x + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
					((hit_voxel.idx.y + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
					((hit_voxel.idx.z + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f)
			);
			box.CreateBuffer();
			box.UpdateBuffer();
			box.Draw();
		}
	}
}

int	VoxelSpace::CheckChunk(const void * obj, Index3D idx)
{
	VoxelSpace * sp = (VoxelSpace *)obj;

	VoxelChunk * ch = sp -> FindChunkPtr(idx.x, idx.y, idx.z);
	if (ch == NULL)
	{
		return (-1);
	}
	else
	{
		return (+1);
	}

	return (0);
}
