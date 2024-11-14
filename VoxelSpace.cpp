
#include "VoxelSpace.hpp"

VoxelSpace::VoxelSpace()
{
	std::cout << "++++ VoxelSpace\n";

	Chunks.clear();
	/*for (int z = -2; z < +2; z++)
	{
		for (int y = -2; y < +2; y++)
		{
			for (int x = -2; x < +2; x++)
			{
				Chunks.push_back(new VoxelChunk(Index3D(x, y, z)));
			}
		}
	}*/
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



VoxelChunk *	VoxelSpace::FindChunkPtr(Index3D idx)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(idx))
			return (ch);
	}
	return (NULL);
}
unsigned int	VoxelSpace::FindChunkIdx(Index3D idx)
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		VoxelChunk * ch = Chunks[i];
		if (ch -> isChunkIndex(idx))
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



void	VoxelSpace::AddChunk(Index3D idx)
{
	VoxelChunk * ch = new VoxelChunk(idx);
	Chunks.push_back(ch);

	ch -> GenerateFuzzyCenterCube(16);
	UpdateBufferNeighbours(idx);
}
void	VoxelSpace::SubChunk(Index3D idx)
{
	unsigned int i = FindChunkIdx(idx);

	delete Chunks[i];
	Chunks.erase(Chunks.begin() + i);
}
void	VoxelSpace::AddChunksRange(Index3D idx, int range)
{
	Index3D min = idx - Index3D(range);
	Index3D max = idx + Index3D(range);

	int range_per_side = range * 2 + 1;
	bool * exists = new bool[range_per_side * range_per_side * range_per_side];

	for (int i = 0; i < range_per_side * range_per_side * range_per_side; i++)
	{
		exists[i] = false;
	}

	//std::cout << "\n";
	//std::cout << "min " << min << "\n";
	//std::cout << "max " << max << "\n";
	//std::cout << "\n";
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Index3D ch_idx = Chunks[i] -> getChunkIndex3D();

		if (Index3D::Box_inclusive(ch_idx, min ,max))
		{
			Index3D diff = ch_idx - min;
			//std::cout << "found " << diff << "\n";
			exists[diff.ToIndex(range_per_side)] = true;
		}
	}

	Index3D i;
	//std::cout << "\n";
	do
	{
		if (!exists[i.ToIndex(range_per_side)])
		{
			//std::cout << "not found " << i << "\n";
			AddChunk(i + min);
		}
	}
	while (Index3D::loop_exclusive(i, 0, range_per_side));
	//std::cout << "\n";

	delete [] exists;

	/*i = min;
	do
	{
		if (FindChunkIdx(i) == 0xFFFFFFFF)
		{
			AddChunk(i);
		}
	}
	while (Index3D::loop_inclusive(i, min, max));*/
}
void	VoxelSpace::SubChunksRange(Index3D idx, int range)
{
	Index3D min = idx - Index3D(range);
	Index3D max = idx + Index3D(range);

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Index3D ch_idx = Chunks[i] -> getChunkIndex3D();

		//if (abs(diff.x) > range || abs(diff.y) > range || abs(diff.z) > range)
		if (!Index3D::Box_inclusive(ch_idx, min ,max))
		{
			SubChunk(ch_idx);
			i--;
		}
	}
}



void	VoxelSpace::UpdateBuffer(Index3D idx)
{
	VoxelChunk * ch = FindChunkPtr(idx);

	if (ch != NULL)
	{
		ch -> UpdateBufferVertex();
		ch -> UpdateBufferIndex(
			FindChunkPtr(idx.Xn()), FindChunkPtr(idx.Xp()),
			FindChunkPtr(idx.Yn()), FindChunkPtr(idx.Yp()),
			FindChunkPtr(idx.Zn()), FindChunkPtr(idx.Zp())
		);
	}
}
void	VoxelSpace::UpdateBufferNeighbours(Index3D idx)
{
	UpdateBuffer(idx);
	UpdateBuffer(idx.Xn());
	UpdateBuffer(idx.Xp());
	UpdateBuffer(idx.Yn());
	UpdateBuffer(idx.Yp());
	UpdateBuffer(idx.Zn());
	UpdateBuffer(idx.Zp());
}



char	VoxelSpace::tryAdd(Voxel_Hover hover)
{
	VoxelChunk::Voxel_Neighbour(hover.cardinal, hover.voxel_idx, hover.chunk_idx);


	VoxelChunk * chunk = FindChunkPtr(hover.chunk_idx);
	if (chunk == NULL)
		return (0);


	char t = chunk -> tryReplace(hover.voxel_idx, 1);

	UpdateBufferNeighbours(chunk -> getChunkIndex3D());

	return t;
}
char	VoxelSpace::trySub(Voxel_Hover hover)
{
	VoxelChunk * chunk = Chunks[hover.chunk_vec_idx];
	if (!chunk -> isChunkIndex(hover.chunk_idx))
		chunk = FindChunkPtr(hover.chunk_idx);


	char t = chunk -> tryReplace(hover.voxel_idx, 0);

	UpdateBufferNeighbours(chunk -> getChunkIndex3D());

	return t;
}

void	VoxelSpace::Draw(int Uni_Chunk_Pos) const
{
	for (size_t i = 0; i < Chunks.size(); i++)
		Chunks[i] -> Draw(Uni_Chunk_Pos);
}
void	VoxelSpace::DrawBound() const
{
	Index3D idx;
	Point min, max;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		idx = Chunks[i] -> getChunkIndex3D();
		min.x = idx.x * (int)(Voxel_per_Side);
		min.y = idx.y * (int)(Voxel_per_Side);
		min.z = idx.z * (int)(Voxel_per_Side);
		max.x = min.x + (int)(Voxel_per_Side);
		max.y = min.y + (int)(Voxel_per_Side);
		max.z = min.z + (int)(Voxel_per_Side);

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
	RayCast3D_Data data_chunk = RayCast3D_init(pos, dir, Voxel_per_Side);

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

			hit_voxel.t = 0;
			hit_voxel.cardinal = 0;
			hit_voxel.isHit = false;
			hit_voxel.cardinal = hit_chunk.cardinal;
			RayCast3D_Data data_voxel = RayCast3D_init(hit_chunk.pos - (chunk -> getChunkOffset()), dir, 1);

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
		voxel_pos = voxel_pos - hover.dir / 128;
		Box box_voxel(
			voxel_pos + Point(0, 0, 0),
			voxel_pos + Point(1, 1, 1)
		);
		box_voxel.CreateBuffer();
		box_voxel.UpdateBuffer();
		box_voxel.Draw();
	}
}
