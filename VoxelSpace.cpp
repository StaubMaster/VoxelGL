
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
				Chunks.push_back(new VoxelChunk(x, y, z));
			}
		}
	}
	//Chunks.push_back(VoxelChunk(0, 0, 0));
}
VoxelSpace::~VoxelSpace()
{
	std::cout << "---- VoxelSpace\n";

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		delete Chunks[i];
	}

	Chunks.clear();
}



VoxelChunk *	VoxelSpace::FindChunkPtr(int x, int y, int z)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(x, y, z))
			return (ch);
	}
	return (NULL);
}
VoxelChunk *	VoxelSpace::FindChunkPtr(Index3D idx)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(idx.x, idx.y, idx.z))
			return (ch);
	}
	return (NULL);
}
unsigned int	VoxelSpace::FindChunkIdx(int x, int y, int z)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(x, y, z))
			return (i);
	}
	return (0xFFFFFFFF);
}
unsigned int	VoxelSpace::FindChunkIdx(Index3D idx)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(idx.x, idx.y, idx.z))
			return (i);
	}
	return (0xFFFFFFFF);
}

int	VoxelSpace::CheckChunk(Index3D idx)
{
	VoxelChunk * ch = FindChunkPtr(idx);
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



void	VoxelSpace::FillRandom()
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i] -> FillRandom();
	}

	int x, y, z;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i] -> getChunkIndex(x, y, z);
		UpdateBuffer(x, y, z);
	}
}
void	VoxelSpace::AddChunk(int x, int y, int z)
{
	if (FindChunkIdx(x, y, z) != 0xFFFFFFFF)
		return;
	std::cout << "chunk not already present\n";
	Chunks.push_back(new VoxelChunk(x, y, z));
	std::cout << "chunk ++++\n";
	unsigned int i = FindChunkIdx(x, y, z);
	if (i == 0xFFFFFFFF)
	{
		std::cout << "chunk not found\n";
		return;
	}
	Chunks[i] -> FillRandom();
	std::cout << "chunk filled\n";
	UpdateBufferNeighbours(x, y, z);
	std::cout << "chunk buffer\n";
}
void	VoxelSpace::UpdateBuffer(int x, int y, int z)
{
	VoxelChunk * ch = FindChunkPtr(x, y, z);

	if (ch != NULL)
	{
		ch -> UpdateBufferVertex();
		ch -> UpdateBufferIndex(
			FindChunkPtr(x - 1, y, z), FindChunkPtr(x + 1, y, z),
			FindChunkPtr(x, y - 1, z), FindChunkPtr(x, y + 1, z),
			FindChunkPtr(x, y, z - 1), FindChunkPtr(x, y, z + 1)
		);
	}
}
void	VoxelSpace::UpdateBufferNeighbours(int x, int y, int z)
{
	UpdateBuffer(x, y, z);
	UpdateBuffer(x - 1, y, z);
	UpdateBuffer(x + 1, y, z);
	UpdateBuffer(x, y - 1, z);
	UpdateBuffer(x, y + 1, z);
	UpdateBuffer(x, y, z - 1);
	UpdateBuffer(x, y, z + 1);
}



char	VoxelSpace::tryAdd(Voxel_Hover hover)
{
	VoxelChunk::Voxel_Neighbour(hover.cardinal, hover.voxel_idx, hover.chunk_idx);


	VoxelChunk * chunk = FindChunkPtr(hover.chunk_idx);
	if (chunk == NULL)
		return (0);


	char t = chunk -> tryReplace(hover.voxel_idx, 1);

	int x, y, z;
	chunk -> getChunkIndex(x, y, z);
	UpdateBufferNeighbours(x, y, z);

	return t;
}
char	VoxelSpace::trySub(Voxel_Hover hover)
{
	VoxelChunk * chunk = Chunks[hover.chunk_vec_idx];
	if (!chunk -> isChunkIndex(hover.chunk_idx))
		chunk = FindChunkPtr(hover.chunk_idx);


	char t = chunk -> tryReplace(hover.voxel_idx, 0);

	int x, y, z;
	chunk -> getChunkIndex(x, y, z);
	UpdateBufferNeighbours(x, y, z);

	return t;
}

void	VoxelSpace::Draw(int Uni_Chunk_Pos) const
{
	for (size_t i = 0; i < Chunks.size(); i++)
		Chunks[i] -> Draw(Uni_Chunk_Pos);
}
void	VoxelSpace::DrawBound() const
{
	int x, y, z;
	Point min, max;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Chunks[i] -> getChunkIndex(x, y, z);
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


VoxelSpace::Voxel_Hover	VoxelSpace::Cross(Point pos, Point dir)
{
	RayCast3D_Hit hit_chunk;
	RayCast3D_Hit hit_voxel;

	hit_chunk.t = 0;
	hit_chunk.cardinal = 0;
	hit_chunk.isHit = false;
	RayCast3D_Data data_chunk = RayCast3D_init(pos, dir, VoxelChunk::Voxel_per_Side);

	while (hit_chunk.t < 128)
	{
		int check = CheckChunk(data_chunk.grid_idx);
		if (check < 0)
		{
			hit_chunk.isHit = false;
			break;
		}
		else if (check > 0)
		{
			hit_chunk = RayCast3D_hit(hit_chunk, data_chunk);
			VoxelChunk * chunk = FindChunkPtr(hit_chunk.idx);

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
			hit_voxel.cardinal = hit_chunk.cardinal;
			RayCast3D_Data data_voxel = RayCast3D_init(hit_chunk.pos - (chunk -> getChunkOffset()), dir, 1);
			//std::cout << "rel chunk " << data_voxel.ray_pos.x << ":" << data_voxel.ray_pos.y << ":" << data_voxel.ray_pos.z << "\n";

			while (hit_voxel.t < 128)
			{
				int check = chunk -> CheckVoxel(data_voxel.grid_idx);
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

		/*if (hit_voxel.isHit)
		{
			VoxelChunk * chunk = FindChunkPtr(hit_chunk.idx);
			if (chunk != NULL)
			{
				//Point chunk_off = chunk -> getChunkOffset();

				//Point shift = Point(-dir.x, -dir.y, dir.z) * -0.01f;
				//Box box_voxel(
				//	Point(hit_voxel.idx.x, hit_voxel.idx.y, hit_voxel.idx.z) + shift + Point(0, 0, 0) + chunk_off,
				//	Point(hit_voxel.idx.x, hit_voxel.idx.y, hit_voxel.idx.z) + shift + Point(1, 1, 1) + chunk_off
				//);
				//box_voxel.CreateBuffer();
				//box_voxel.UpdateBuffer();
				//box_voxel.Draw();

				//Box box_voxel_hit(
				//	hit_voxel.pos + Point(0.01f, 0.01f, 0.01f) + chunk_off,
				//	hit_voxel.pos - Point(0.01f, 0.01f, 0.01f) + chunk_off
				//);
				//box_voxel_hit.CreateBuffer();
				//box_voxel_hit.UpdateBuffer();
				//box_voxel_hit.Draw();
			}
		}*/
	}

	Voxel_Hover hover;
	hover.isValid = false;
	if (hit_chunk.isHit && hit_voxel.isHit)
	{
		hover.isValid = true;
		hover.chunk_vec_idx = FindChunkIdx(hit_chunk.idx);
		hover.chunk_idx = hit_chunk.idx;
		hover.voxel_idx.x = hit_voxel.idx.x;
		hover.voxel_idx.y = hit_voxel.idx.y;
		hover.voxel_idx.z = hit_voxel.idx.z;
		hover.cardinal = hit_voxel.cardinal;
		hover.dir = dir;
	}
	return hover;
}
void	VoxelSpace::DrawHover(Voxel_Hover hover) const
{
	if (hover.isValid)
	{
		Point chunk_off = Chunks[hover.chunk_vec_idx] -> getChunkOffset();

		Point voxel_pos(hover.voxel_idx.x, hover.voxel_idx.y, hover.voxel_idx.z);
		voxel_pos = voxel_pos + chunk_off;
		voxel_pos = voxel_pos - hover.dir * 0.0625f;
		Box box_voxel(
			voxel_pos + Point(0, 0, 0) + Point(0.01f, 0.01f, 0.01f),
			voxel_pos + Point(1, 1, 1) - Point(0.01f, 0.01f, 0.01f)
		);
		box_voxel.CreateBuffer();
		box_voxel.UpdateBuffer();
		box_voxel.Draw();
	}
}
