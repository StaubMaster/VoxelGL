
#include "Voxel.hpp"

Voxel::Voxel()
{
	ID = 0;
}
Voxel::Voxel(char id) :
	ID(id)
{

}

bool	Voxel::isSolid() const
{
	if (ID == 0)
	{
		return (false);
	}
	return (true);
}



static float	Texture_Coords[] = {
	0.00f, 1.00f, 0.0f, 1.0f,
	0.75f, 1.00f, 0.5f, 1.0f,
	0.25f, 0.50f, 0.0f, 0.5f,
	0.00f, 0.25f, 0.5f, 1.0f,
	0.75f, 0.50f, 0.5f, 1.0f,
	0.50f, 0.75f, 0.5f, 0.0f,
	0.50f, 0.25f, 0.5f, 1.0f,
};
Voxel::RenderData Voxel::RenderData::compress(Undex3D vox_idx, int tex_idx, char tex_info)
{
	RenderData data;

	data.compressed_pos = (vox_idx.x | (vox_idx.y << 8) | (vox_idx.z << 16));
	data.tex_idx = tex_idx;

	float	tex_x_min = 0.0f, tex_x_max = 1.0f;
	float	tex_y_min = 0.0f, tex_y_max = 1.0f;

	char side_idx = (tex_info >> 2) & 0b111;
	side_idx *= 4;

	tex_x_min = Texture_Coords[side_idx + 0];
	tex_x_max = Texture_Coords[side_idx + 1];
	tex_y_min = Texture_Coords[side_idx + 2];
	tex_y_max = Texture_Coords[side_idx + 3];

	if ((tex_info & 0b01) == 0)
		data.tex_x = tex_x_min;
	else
		data.tex_x = tex_x_max;

	if ((tex_info & 0b10) == 0)
		data.tex_y = tex_y_min;
	else
		data.tex_y = tex_y_max;

	return data;
}

void Voxel::FaceXn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_XM | TEXTURE_MIN_MIN);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XM | TEXTURE_MAX_MIN);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XM | TEXTURE_MIN_MAX);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XM | TEXTURE_MIN_MAX);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XM | TEXTURE_MAX_MIN);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(0, 1, 1), tex_idx, TEXTURE_XM | TEXTURE_MAX_MAX);
	idx += 6;
}
void Voxel::FaceXp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b11000);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b11001);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b11010);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b11010);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b11001);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(0, 1, 1), tex_idx, 0b11011);
	idx += 6;
}
void Voxel::FaceYn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b01000);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b01010);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01001);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01001);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b01010);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 0, 1), tex_idx, 0b01011);
	idx += 6;
}
void Voxel::FaceYp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b10100);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10101);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b10110);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b10110);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10101);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 0, 1), tex_idx, 0b10111);
	idx += 6;
}
void Voxel::FaceZn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b10000);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10001);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b10010);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b10010);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10001);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 1, 0), tex_idx, 0b10011);
	idx += 6;
}
void Voxel::FaceZp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b01100);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b01110);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01101);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01101);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b01110);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 1, 0), tex_idx, 0b01111);
	idx += 6;
}

void Voxel::FaceX(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceXn(data, idx, vox_idx, 0);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceXp(data, idx, vox_idx, 0);
		}
	}
}
void Voxel::FaceY(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceYn(data, idx, vox_idx, 0);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceYp(data, idx, vox_idx, 0);
		}
	}
}
void Voxel::FaceZ(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceZn(data, idx, vox_idx, 0);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceZp(data, idx, vox_idx, 0);
		}
	}
}
