
#include "VoxelSpace.hpp"

VoxelSpace::VoxelSpace(VoxelDataTable & table) :
	Table(table)
{
	std::cout << "++++ VoxelSpace\n";

	Chunks.clear();
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

	//ch -> GeneratePlane(Table);
	//ch -> GenerateVoxelRotationTest(Table);
	//ch -> GenerateFuzzyCenterCube(Table, 16);
	//ch -> GenerateChunkLimit(Table, 1);

	//UpdateBufferNeighbours(idx);
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

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Index3D ch_idx = Chunks[i] -> getChunkIndex3D();

		if (Index3D::Box_inclusive(ch_idx, min ,max))
		{
			Index3D diff = ch_idx - min;
			exists[diff.ToIndex(range_per_side)] = true;
		}
	}

	Index3D i;
	do
	{
		if (!exists[i.ToIndex(range_per_side)])
		{
			AddChunk(i + min);
		}
	}
	while (Index3D::loop_exclusive(i, 0, range_per_side));

	delete [] exists;
}
void	VoxelSpace::SubChunksRange(Index3D idx, int range)
{
	Index3D min = idx - Index3D(range);
	Index3D max = idx + Index3D(range);

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		Index3D ch_idx = Chunks[i] -> getChunkIndex3D();

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
		ch -> RequestBufferUpdate();
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
void	VoxelSpace::UpdateChunks()
{
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		if (Chunks[i] -> NeedsGeneration1)
		{
			Chunks[i] -> GeneratePlane(Table);

			Chunks[i] -> NeedsGeneration1 = false;
			Chunks[i] -> NeedsGeneration2 = true;
			break;
		}
	}

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		if (Chunks[i] -> NeedsGeneration2)
		{
			Index3D idx = Chunks[i] -> getChunkIndex3D();
			VoxelChunk * chunks[4] = {
				Chunks[i],
				FindChunkPtr(idx.Xp()),
				FindChunkPtr(idx.Zp()),
				FindChunkPtr(idx.Xp().Zp())
			};

			bool allAvailable = true;
			for (int c = 0; c < 4; c++)
			{
				if (chunks[c] == NULL)
				{
					allAvailable = false;
					break;
				}
				if (chunks[c] -> NeedsGeneration1)
				{
					allAvailable = false;
					break;
				}
			}

			if (allAvailable)
			{
				VoxelChunk::GenerateFeature(Table, chunks);
				Chunks[i] -> NeedsGeneration2 = false;
				Chunks[i] -> RequestBufferUpdate();
				break;
			}
		}
	}

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		if (Chunks[i] -> Render.NeedsUpdate)
		{
			Index3D idx = Chunks[i] -> getChunkIndex3D();
			Chunks[i] -> Render.Update(FindChunkPtr(idx),
				FindChunkPtr(idx.Xn()), FindChunkPtr(idx.Xp()),
				FindChunkPtr(idx.Yn()), FindChunkPtr(idx.Yp()),
				FindChunkPtr(idx.Zn()), FindChunkPtr(idx.Zp())
			);
			break;
		}
	}

	for (size_t i = 0; i < Chunks.size(); i++)
	{
		if (Chunks[i] -> Render.NeedsBind)
		{
			Chunks[i] -> Render.Bind();
			break;
		}
	}
}



char	VoxelSpace::tryAdd(VoxelHover hover, char id)
{
	VoxelChunk::Voxel_Neighbour(hover.hit.from_axis, hover.voxel_idx, hover.chunk_idx);

	VoxelChunk * chunk = FindChunkPtr(hover.chunk_idx);
	if (chunk == NULL)
		return (0);

	chunk -> tryAdd(Table, hover, id);

	UpdateBufferNeighbours(chunk -> getChunkIndex3D());

	return 0;
}
char	VoxelSpace::trySub(VoxelHover hover, char id)
{
	VoxelChunk * chunk = Chunks[hover.chunk_vector_idx];
	if (!chunk -> isChunkIndex(hover.chunk_idx))
		chunk = FindChunkPtr(hover.chunk_idx);

	char t = chunk -> trySub(hover);

	UpdateBufferNeighbours(chunk -> getChunkIndex3D());

	return t;
	(void)id;
}



bool	VoxelSpace::IntersektBool(AxisBox & box)
{
	Index3D chunk_min(
		floorf(box.Min.x / Voxel_per_Side),
		floorf(box.Min.y / Voxel_per_Side),
		floorf(box.Min.z / Voxel_per_Side)
	);
	Index3D chunk_max(
		ceilf(box.Max.x / Voxel_per_Side),
		ceilf(box.Max.y / Voxel_per_Side),
		ceilf(box.Max.z / Voxel_per_Side)
	);

	Index3D i = chunk_min;
	do
	{
		VoxelChunk * chunk = FindChunkPtr(i);
		if (chunk != NULL)
		{
			if (chunk -> IntersektBool(box))
				return (true);
		}
	}
	while (Index3D::loop_exclusive(i, chunk_min, chunk_max));

	return (false);
}
char	VoxelSpace::TouchVoxel(AxisBox & box, float size)
{
	Index3D chunk_min(
		floorf(box.Min.x / Voxel_per_Side),
		floorf(box.Min.y / Voxel_per_Side),
		floorf(box.Min.z / Voxel_per_Side)
	);
	Index3D chunk_max(
		ceilf(box.Max.x / Voxel_per_Side),
		ceilf(box.Max.y / Voxel_per_Side),
		ceilf(box.Max.z / Voxel_per_Side)
	);

	char	bits = 0;

	Index3D i = chunk_min;
	do
	{
		VoxelChunk * chunk = FindChunkPtr(i);
		if (chunk != NULL)
		{
			bits |= chunk -> TouchVoxel(box, size);
		}
	}
	while (Index3D::loop_exclusive(i, chunk_min, chunk_max));

	return (bits);
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

		AxisBox box(min, max);
		box.CreateBuffer();
		box.UpdateBuffer();
		box.Draw();
	}
}


VoxelHover	VoxelSpace::Cross(Point pos, Point dir)
{
	RayCast3D_Hit hit_chunk;
	RayCast3D_Hit hit_voxel;

	hit_chunk.t = 0;
	hit_chunk.from_axis = 0;
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
			hit_voxel.from_axis = 0;
			hit_voxel.isHit = false;
			hit_voxel.from_axis = hit_chunk.from_axis;
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

	VoxelHover hover;
	hover.isValid = false;
	if (hit_chunk.isHit && hit_voxel.isHit)
	{
		hover.isValid = true;
		hover.chunk_vector_idx = FindChunkIdx(hit_chunk.idx);

		hover.chunk_idx = hit_chunk.idx;
		hover.voxel_idx.x = hit_voxel.idx.x;
		hover.voxel_idx.y = hit_voxel.idx.y;
		hover.voxel_idx.z = hit_voxel.idx.z;

		hover.hit = hit_voxel;
	}
	return hover;
}
void	VoxelSpace::DrawHover(VoxelHover hover) const
{
	if (hover.isValid)
	{
		Point chunk_off = Chunks[hover.chunk_vector_idx] -> getChunkOffset();

		Point voxel_pos(hover.voxel_idx.x, hover.voxel_idx.y, hover.voxel_idx.z);
		voxel_pos = voxel_pos + chunk_off;
		voxel_pos = voxel_pos - hover.hit.dir / 128;
		AxisBox box_voxel(
			voxel_pos + Point(0, 0, 0),
			voxel_pos + Point(1, 1, 1)
		);
		box_voxel.CreateBuffer();
		box_voxel.UpdateBuffer();
		box_voxel.Draw();
	}
}



unsigned int	VoxelSpace::GeneralInfoChunksCount()
{
	return (Chunks.size());
}
unsigned int	VoxelSpace::GeneralInfoMemSumChunksData()
{
	unsigned int sum = 0;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		sum += Chunks[i] -> GeneralInfoMemData();
	}
	return (sum);
}
unsigned int	VoxelSpace::GeneralInfoMemSumChunksBuff()
{
	unsigned int sum = 0;
	for (size_t i = 0; i < Chunks.size(); i++)
	{
		sum += Chunks[i] -> GeneralInfoMemBuff();
	}
	return (sum);
}
