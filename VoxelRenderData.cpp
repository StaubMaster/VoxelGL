
#include "VoxelRenderData.hpp"

void	VoxelRenderData::TextureCoordFace::getCorner(float & x, float & y, bool Xbool, bool Ybool, bool swap) const
{
	if (!swap)
	{
		if (!Xbool) { x = min_x; } else { x = max_x; }
		if (!Ybool) { y = min_y; } else { y = max_y; }
	}
	else
	{
		if (!Ybool) { x = min_x; } else { x = max_x; }
		if (!Xbool) { y = max_y; } else { y = min_y; }
	}
}

VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::FlipX() const
{
	return ((TextureCoordFace) {
		max_x,
		min_x,
		min_y,
		max_y,
	});
}
VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::FlipY() const
{
	return ((TextureCoordFace) {
		min_x,
		max_x,
		max_y,
		min_y,
	});
}
VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordFace::Spin() const
{
	return ((TextureCoordFace) {
		max_x,
		min_x,
		max_y,
		min_y,
	});
}



VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordCube::getFace(char idx) const
{
	return (((TextureCoordFace *)this)[idx - 1]);
}

VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::SpinAroundX() const
{
	return ((TextureCoordCube) {
		XM.Spin(),
		YP.FlipX(),
		ZM.FlipY(),
		ZP.FlipY(),
		YM.FlipX(),
		XP.Spin(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::SpinAroundY() const
{
	return ((TextureCoordCube) {
		XP.FlipY(),
		YM.Spin(),
		ZM.FlipX(),
		ZP.FlipX(),
		YP.Spin(),
		XM.FlipY(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::SpinAroundZ() const
{
	return ((TextureCoordCube) {
		XP.FlipX(),
		YP.FlipY(),
		ZP.Spin(),
		ZM.Spin(),
		YM.FlipY(),
		XM.FlipX(),
	});
}

VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateXM() const
{
	return ((TextureCoordCube) {
		XM.Spin(),
		ZM,
		YM.FlipY(),
		YP.FlipY(),
		ZP,
		XP.Spin(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateXP() const
{
	return ((TextureCoordCube) {
		XM,
		ZP.FlipY(),
		YP.Spin(),
		YM.Spin(),
		ZM.FlipY(),
		XP,
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateYM() const
{
	return ((TextureCoordCube) {
		ZM.Spin(),
		YM,
		XM.FlipY(),
		XP.FlipY(),
		YP,
		ZP.Spin(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateYP() const
{
	return ((TextureCoordCube) {
		ZP.FlipY(),
		YM.Spin(),
		XP,
		XM,
		YP.Spin(),
		ZM.FlipY(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateZM() const
{
	return ((TextureCoordCube) {
		YP.FlipY(),
		XM.Spin(),
		ZP,
		ZM,
		XP.Spin(),
		YM.FlipY(),
	});
}
VoxelRenderData::TextureCoordCube	VoxelRenderData::TextureCoordCube::RotateZP() const
{
	return ((TextureCoordCube) {
		YM,
		XP.FlipY(),
		ZP.Spin(),
		ZM.Spin(),
		XM.FlipY(),
		YP,
	});
}



static VoxelRenderData::TextureCoordCube Default_Texture_Same = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	X+
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
};





VoxelRenderData::VoxelRenderData()
{

}
VoxelRenderData::VoxelRenderData(Undex3D vox_idx, int tex_idx, char tex_info, char tex_rot)
{
	compressed_pos = (vox_idx.x | (vox_idx.y << 8) | (vox_idx.z << 16));
	tex_idx = tex_idx;

	TextureCoordCube coords;

	if (tex_rot == 0)
		coords = Default_Texture_Cube;
	else if (tex_rot == 1)
		coords = Default_Texture_Cube.RotateXM();
	else if (tex_rot == 2)
		coords = Default_Texture_Cube.SpinAroundX();
	else if (tex_rot == 3)
		coords = Default_Texture_Cube.RotateXP();
	else if (tex_rot == 4)
		coords = Default_Texture_Cube;
	else if (tex_rot == 5)
		coords = Default_Texture_Cube.RotateYM();
	else if (tex_rot == 6)
		coords = Default_Texture_Cube.SpinAroundY();
	else if (tex_rot == 7)
		coords = Default_Texture_Cube.RotateYP();
	else if (tex_rot == 8)
		coords = Default_Texture_Cube;
	else if (tex_rot == 9)
		coords = Default_Texture_Cube.RotateZM();
	else if (tex_rot == 10)
		coords = Default_Texture_Cube.SpinAroundZ();
	else if (tex_rot == 11)
		coords = Default_Texture_Cube.RotateZP();
	else
		coords = Default_Texture_Same;

	char side_idx = (tex_info >> 2) & 0b111;
	TextureCoordFace face = coords.getFace(side_idx);
	face.getCorner(tex_x, tex_y, (tex_info & 0b01) == 0, (tex_info & 0b10) == 0, (tex_rot % 2) != 0);
}





VoxelRenderData::DataStream::DataStream(unsigned int len)
{
	Length = len;
	Data = new VoxelRenderData[Length];
	Index = 0;
}
VoxelRenderData::DataStream::~DataStream()
{
	delete [] Data;
}

void	VoxelRenderData::DataStream::Insert(VoxelRenderData vox)
{
	Data[Index] = vox;
	Index++;
}
void	VoxelRenderData::DataStream::ToBuffer(unsigned int & count) const
{
	glBufferData(GL_ARRAY_BUFFER, Index * sizeof(VoxelRenderData), Data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(VoxelRenderData), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(VoxelRenderData), (void *)sizeof(unsigned int));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VoxelRenderData), (void *)(sizeof(unsigned int) + sizeof(unsigned int)));

	count = Index;
}

void VoxelRenderData::DataStream::FaceXn(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_XM | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(0, 1, 1), tex_idx, TEXTURE_XM | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceXp(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_XP | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_XP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_XP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(0, 1, 1), tex_idx, TEXTURE_XP | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceYn(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_YM | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_YM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_YM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_YM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_YM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(1, 0, 1), tex_idx, TEXTURE_YM | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceYp(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_YP | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_YP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_YP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(0, 0, 1), tex_idx, TEXTURE_YP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_YP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(1, 0, 1), tex_idx, TEXTURE_YP | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceZn(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_ZM | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_ZM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_ZM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_ZM | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_ZM | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(1, 1, 0), tex_idx, TEXTURE_ZM | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceZp(Undex3D vox_idx, int tex_idx, char tex_rot)
{
	Data[Index + 0] = VoxelRenderData(vox_idx + Undex3D(0, 0, 0), tex_idx, TEXTURE_ZP | TEXTURE_MIN_MIN, tex_rot);
	Data[Index + 1] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_ZP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 2] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_ZP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 3] = VoxelRenderData(vox_idx + Undex3D(1, 0, 0), tex_idx, TEXTURE_ZP | TEXTURE_MIN_MAX, tex_rot);
	Data[Index + 4] = VoxelRenderData(vox_idx + Undex3D(0, 1, 0), tex_idx, TEXTURE_ZP | TEXTURE_MAX_MIN, tex_rot);
	Data[Index + 5] = VoxelRenderData(vox_idx + Undex3D(1, 1, 0), tex_idx, TEXTURE_ZP | TEXTURE_MAX_MAX, tex_rot);
	Index += 6;
}



void VoxelRenderData::DataStream::FaceX(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceXn(vox_idx, 0, v_n -> Rotation);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceXp(vox_idx, 0, v_p -> Rotation);
		}
	}
}
void VoxelRenderData::DataStream::FaceY(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceYn(vox_idx, 0, v_n -> Rotation);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceYp(vox_idx, 0, v_p -> Rotation);
		}
	}
}
void VoxelRenderData::DataStream::FaceZ(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p)
{
	if (v_n != NULL && v_p != NULL)
	{
		if (v_n -> isSolid() && !v_p -> isSolid())
		{
			FaceZn(vox_idx, 0, v_n -> Rotation);
		}
		if (!v_n -> isSolid() && v_p -> isSolid())
		{
			FaceZp(vox_idx, 0, v_p -> Rotation);
		}
	}
}



void VoxelRenderData::DataStream::FaceX(Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_idx.y == Voxel_per_Side || vox_idx.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_idx.x == 0)
	{
		if (ch_n != NULL)
		{
			vn = &ch_n -> get(vox_idx.set_get_X(Voxel_per_Side - 1));
			vp = &here -> get(vox_idx.set_get_X(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox_idx.x == Voxel_per_Side)
	{
		if (ch_p != NULL)
		{
			vn = &here -> get(vox_idx.set_get_X(Voxel_per_Side - 1));
			vp = &ch_p -> get(vox_idx.set_get_X(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &here -> get(vox_idx.set_get_X(vox_idx.x - 1));
		vp = &here -> get(vox_idx.set_get_X(vox_idx.x - 0));
	}
	FaceX(vox_idx, vn, vp);
}
void VoxelRenderData::DataStream::FaceY(Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_idx.x == Voxel_per_Side || vox_idx.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_idx.y == 0)
	{
		if (ch_n != NULL)
		{
			vn = &ch_n -> get(vox_idx.set_get_Y(Voxel_per_Side - 1));
			vp = &here -> get(vox_idx.set_get_Y(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox_idx.y == Voxel_per_Side)
	{
		if (ch_p != NULL)
		{
			vn = &here -> get(vox_idx.set_get_Y(Voxel_per_Side - 1));
			vp = &ch_p -> get(vox_idx.set_get_Y(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &here -> get(vox_idx.set_get_Y(vox_idx.y - 1));
		vp = &here -> get(vox_idx.set_get_Y(vox_idx.y - 0));
	}
	FaceY(vox_idx, vn, vp);
}
void VoxelRenderData::DataStream::FaceZ(Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_idx.x == Voxel_per_Side || vox_idx.y == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_idx.z == 0)
	{
		if (ch_n != NULL)
		{
			vn = &ch_n -> get(vox_idx.set_get_Z(Voxel_per_Side - 1));
			vp = &here -> get(vox_idx.set_get_Z(0));

			if (!vp -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else if (vox_idx.z == Voxel_per_Side)
	{
		if (ch_p != NULL)
		{
			vn = &here -> get(vox_idx.set_get_Z(Voxel_per_Side - 1));
			vp = &ch_p -> get(vox_idx.set_get_Z(0));

			if (!vn -> isSolid())
			{
				vn = NULL;
				vp = NULL;
			}
		}
	}
	else
	{
		vn = &here -> get(vox_idx.set_get_Z(vox_idx.z - 1));
		vp = &here -> get(vox_idx.set_get_Z(vox_idx.z - 0));
	}
	FaceZ(vox_idx, vn, vp);
}

