
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


Voxel::RenderData Voxel::RenderData::compress(Undex3D vox_idx, int tex_idx, char tex_info)
{
	RenderData data;

	data.compressed_pos = (vox_idx.x | (vox_idx.y << 8) | (vox_idx.z << 16));
	data.tex_idx = tex_idx;

	float	tex_x_min = 0.0f, tex_x_max = 1.0f;
	float	tex_y_min = 0.0f, tex_y_max = 1.0f;

	char side = (tex_info >> 2) & 0b111;
	if (side == 0b000)
	{
		tex_x_min = 0.75f; tex_x_max = 1.00f; tex_y_min = 0.5f; tex_y_max = 1.0f;
	}
	else if (side == 0b001)
	{
		tex_x_min = 0.50f; tex_x_max = 0.25f; tex_y_min = 0.5f; tex_y_max = 1.0f;
	}
	else if (side == 0b010)
	{
		tex_x_min = 0.25f; tex_x_max = 0.50f; tex_y_min = 0.0f; tex_y_max = 0.5f;
	}
	else if (side == 0b011)
	{
		tex_x_min = 0.50f; tex_x_max = 0.75f; tex_y_min = 0.5f; tex_y_max = 0.0f;
	}
	else if (side == 0b100)
	{
		tex_x_min = 0.75f; tex_x_max = 0.50f; tex_y_min = 0.5f; tex_y_max = 1.0f;
	}
	else if (side == 0b101)
	{
		tex_x_min = 0.00f; tex_x_max = 0.25f; tex_y_min = 0.5f; tex_y_max = 1.0f;
	}

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
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b00000);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b00010);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b00001);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b00001);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b00010);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(0, 1, 1), tex_idx, 0b00011);
	idx += 6;
}
void Voxel::FaceXp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx)
{
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b00100);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b00101);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b00110);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b00110);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b00101);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(0, 1, 1), tex_idx, 0b00111);
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
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b01100);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01101);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b01110);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(0, 0, 1), tex_idx, 0b01110);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b01101);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 0, 1), tex_idx, 0b01111);
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
	data[idx + 0] = RenderData::compress(vox_idx + Undex3D(0, 0, 0), tex_idx, 0b10100);
	data[idx + 1] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b10110);
	data[idx + 2] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10101);
	data[idx + 3] = RenderData::compress(vox_idx + Undex3D(1, 0, 0), tex_idx, 0b10101);
	data[idx + 4] = RenderData::compress(vox_idx + Undex3D(0, 1, 0), tex_idx, 0b10110);
	data[idx + 5] = RenderData::compress(vox_idx + Undex3D(1, 1, 0), tex_idx, 0b10111);
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
