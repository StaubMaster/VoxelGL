
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
		min.x = x * (int)(VoxelChunk::Voxel_per_Side);
		min.y = y * (int)(VoxelChunk::Voxel_per_Side);
		min.z = z * (int)(VoxelChunk::Voxel_per_Side);
		max.x = min.x + (int)(VoxelChunk::Voxel_per_Side);
		max.y = min.y + (int)(VoxelChunk::Voxel_per_Side);
		max.z = min.z + (int)(VoxelChunk::Voxel_per_Side);

		Box box(min, max);
		box.CreateBuffer();
		box.UpdateBuffer();
		box.Draw();
	}
}


void	VoxelSpace::Cross(Point pos, Point dir)
{
	RayCast3D_Hit hit_chunk;
	RayCast3D_Hit hit_voxel;

	hit_chunk.t = 0;
	hit_chunk.cardinal = 0;
	hit_chunk.isHit = false;
	RayCast3D_Data data_chunk = RayCast3D_init(pos, dir, VoxelChunk::Voxel_per_Side);

	while (hit_chunk.t < 128)
	{
		int check = CheckChunk(this, data_chunk.grid_idx);
		if (check < 0)
		{
			hit_chunk.isHit = false;
			break;
		}
		else if (check > 0)
		{
			hit_chunk = RayCast3D_hit(hit_chunk, data_chunk);
			VoxelChunk * chunk = FindChunkPtr(hit_chunk.idx.x, hit_chunk.idx.y, hit_chunk.idx.z);

			//std::cout << "check " << hit_chunk.idx.x << ":" << hit_chunk.idx.y << ":" << hit_chunk.idx.z << "\n";

			//Box box_chunk_hit(
			//	hit_chunk.pos - Point(0.1f, 0.1f, 0.1f),
			//	hit_chunk.pos + Point(0.1f, 0.1f, 0.1f)
			//);
			//box_chunk_hit.CreateBuffer();
			//box_chunk_hit.UpdateBuffer();
			//box_chunk_hit.Draw();

			//Box box_chunk(
			//	Point(
			//		((hit_chunk.idx.x + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
			//		((hit_chunk.idx.y + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
			//		((hit_chunk.idx.z + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f),
			//	Point(
			//		((hit_chunk.idx.x + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
			//		((hit_chunk.idx.y + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
			//		((hit_chunk.idx.z + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f)
			//);
			//box_chunk.CreateBuffer();
			//box_chunk.UpdateBuffer();
			//box_chunk.Draw();

			hit_voxel.t = 0;
			hit_voxel.cardinal = 0;
			hit_voxel.isHit = false;
			RayCast3D_Data data_voxel = RayCast3D_init(hit_chunk.pos - (chunk -> getChunkOffset()), dir, 1);
			//std::cout << "rel chunk " << data_voxel.ray_pos.x << ":" << data_voxel.ray_pos.y << ":" << data_voxel.ray_pos.z << "\n";

			while (hit_voxel.t < 128)
			{
				int check = VoxelChunk::CheckVoxel(chunk, data_voxel.grid_idx);
				if (check < 0)
				{
					hit_voxel.isHit = false;
					break;
				}
				else if (check > 0)
				{
					hit_voxel = RayCast3D_hit(hit_voxel, data_voxel);
					hit_voxel.pos = data_voxel.norm_pos + (data_voxel.norm_dir * hit_voxel.t);
					break;
				}

				hit_voxel = RayCast3D_continue(data_voxel);
			}

			if (hit_voxel.isHit)
				break;
		}

		hit_chunk = RayCast3D_continue(data_chunk);
	}

	/*std::cout
		<< "chunk (" << hit_chunk.isHit << ")" << hit_chunk.idx.x << ":" << hit_chunk.idx.y << ":" << hit_chunk.idx.z << " [" << hit_chunk.t << "]  "
		<< "voxel (" << hit_voxel.isHit << ")" << hit_voxel.idx.x << ":" << hit_voxel.idx.y << ":" << hit_voxel.idx.z << " [" << hit_voxel.t << "]  "
		<< "\n";*/

	if (hit_chunk.isHit)
	{
		//Box box_chunk(
		//	Point(
		//		((hit_chunk.idx.x + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
		//		((hit_chunk.idx.y + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f,
		//		((hit_chunk.idx.z + 0) * ((int)VoxelChunk::Voxel_per_Side + 1)) - 0.1f),
		//	Point(
		//		((hit_chunk.idx.x + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
		//		((hit_chunk.idx.y + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f,
		//		((hit_chunk.idx.z + 1) * ((int)VoxelChunk::Voxel_per_Side + 1)) + 0.1f)
		//);
		//box_chunk.CreateBuffer();
		//box_chunk.UpdateBuffer();
		//box_chunk.Draw();

		//Box box_chunk_hit(
		//	hit_chunk.pos - Point(0.01f, 0.01f, 0.01f),
		//	hit_chunk.pos + Point(0.01f, 0.01f, 0.01f)
		//);
		//box_chunk_hit.CreateBuffer();
		//box_chunk_hit.UpdateBuffer();
		//box_chunk_hit.Draw();

		if (hit_voxel.isHit)
		{
			VoxelChunk * chunk = FindChunkPtr(hit_chunk.idx.x, hit_chunk.idx.y, hit_chunk.idx.z);
			if (chunk != NULL)
			{
				Point chunk_off = chunk -> getChunkOffset();

				Point shift = Point(-dir.x, -dir.y, dir.z) * -0.01f;
				Box box_voxel(
					Point(hit_voxel.idx.x, hit_voxel.idx.y, hit_voxel.idx.z) + shift + Point(0, 0, 0) + chunk_off,
					Point(hit_voxel.idx.x, hit_voxel.idx.y, hit_voxel.idx.z) + shift + Point(1, 1, 1) + chunk_off
				);
				box_voxel.CreateBuffer();
				box_voxel.UpdateBuffer();
				box_voxel.Draw();

				Box box_voxel_hit(
					hit_voxel.pos + Point(0.01f, 0.01f, 0.01f) + chunk_off,
					hit_voxel.pos - Point(0.01f, 0.01f, 0.01f) + chunk_off
				);
				box_voxel_hit.CreateBuffer();
				box_voxel_hit.UpdateBuffer();
				box_voxel_hit.Draw();
			}
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
