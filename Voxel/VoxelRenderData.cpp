
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



VoxelRenderData::TextureCoordFace	VoxelRenderData::TextureCoordCube::getFace(char idx, bool & texSwap) const
{
	texSwap = TexSwap;
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
		TexSwap,
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
		TexSwap,
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
		TexSwap,
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
		!TexSwap,
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
		!TexSwap,
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
		!TexSwap,
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
		!TexSwap,
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
		!TexSwap,
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
		!TexSwap,
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
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_ZM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_XM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_YM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_ZP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_XP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	false,
};
static VoxelRenderData::TextureCoordCube Default_Texture_Cube_YP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	false,
};


VoxelRenderData::VoxelRenderData()
{

}
VoxelRenderData::VoxelRenderData(Undex3D vox_pos_idx, char tex_info, const Voxel & vox)
{
	char	tex_idx = vox.getID();
	char	vox_axis = vox.getAxis();
	char	vox_spin = vox.getSpin();

	compressed_pos = (vox_pos_idx.x | (vox_pos_idx.y << 8) | (vox_pos_idx.z << 16));
	this -> tex_idx = tex_idx;

	TextureCoordCube coords;

	if (vox_axis == 0)          { coords = Default_Texture_Same; }
	else if (vox_axis == 0b001) { coords = Default_Texture_Cube_XM; }
	else if (vox_axis == 0b010) { coords = Default_Texture_Cube_ZM; }
	else if (vox_axis == 0b100) { coords = Default_Texture_Cube_YM; }
	else if (vox_axis == 0b110) { coords = Default_Texture_Cube_XP; }
	else if (vox_axis == 0b101) { coords = Default_Texture_Cube_ZP; }
	else if (vox_axis == 0b011) { coords = Default_Texture_Cube_YP; }
	else                        { coords = Default_Texture_Same; }

	if (vox_axis == 0b001 || vox_axis == 0b110)
	{
		     if (vox_spin == 0) { ; }
		else if (vox_spin == 1) { coords = coords.RotateXM(); }
		else if (vox_spin == 2) { coords = coords.SpinAroundX(); }
		else if (vox_spin == 3) { coords = coords.RotateXP(); }
	}
	else if (vox_axis == 0b010 || vox_axis == 0b101)
	{
		     if (vox_spin == 0) { ; }
		else if (vox_spin == 1) { coords = coords.RotateYM(); }
		else if (vox_spin == 2) { coords = coords.SpinAroundY(); }
		else if (vox_spin == 3) { coords = coords.RotateYP(); }
	}
	else if (vox_axis == 0b100 || vox_axis == 0b011)
	{
		     if (vox_spin == 0) { ; }
		else if (vox_spin == 1) { coords = coords.RotateZM(); }
		else if (vox_spin == 2) { coords = coords.SpinAroundZ(); }
		else if (vox_spin == 3) { coords = coords.RotateZP(); }
	}
	else { coords = Default_Texture_Same; }

	bool TexSwap;
	char side_idx = (tex_info >> 2) & 0b111;
	TextureCoordFace face = coords.getFace(side_idx, TexSwap);
	face.getCorner(tex_x, tex_y, (tex_info & 0b01) == 0, (tex_info & 0b10) == 0, TexSwap);
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

void VoxelRenderData::DataStream::FaceXn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_XM | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_XM | TEXTURE_MIN_MAX, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_XM | TEXTURE_MAX_MIN, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_XM | TEXTURE_MAX_MIN, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_XM | TEXTURE_MIN_MAX, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 1), TEXTURE_XM | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceXp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_XP | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_XP | TEXTURE_MAX_MIN, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_XP | TEXTURE_MIN_MAX, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_XP | TEXTURE_MIN_MAX, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_XP | TEXTURE_MAX_MIN, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 1), TEXTURE_XP | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceYn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_YM | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_YM | TEXTURE_MIN_MAX, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_YM | TEXTURE_MAX_MIN, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_YM | TEXTURE_MAX_MIN, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_YM | TEXTURE_MIN_MAX, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 1), TEXTURE_YM | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceYp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_YP | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_YP | TEXTURE_MAX_MIN, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_YP | TEXTURE_MIN_MAX, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 1), TEXTURE_YP | TEXTURE_MIN_MAX, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_YP | TEXTURE_MAX_MIN, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 1), TEXTURE_YP | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceZn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_ZM | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_ZM | TEXTURE_MIN_MAX, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_ZM | TEXTURE_MAX_MIN, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_ZM | TEXTURE_MAX_MIN, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_ZM | TEXTURE_MIN_MAX, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(1, 1, 0), TEXTURE_ZM | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceZp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + Undex3D(0, 0, 0), TEXTURE_ZP | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_ZP | TEXTURE_MAX_MIN, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_ZP | TEXTURE_MIN_MAX, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + Undex3D(1, 0, 0), TEXTURE_ZP | TEXTURE_MIN_MAX, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + Undex3D(0, 1, 0), TEXTURE_ZP | TEXTURE_MAX_MIN, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + Undex3D(1, 1, 0), TEXTURE_ZP | TEXTURE_MAX_MAX, vox);
	Index += 6;
}



void VoxelRenderData::DataStream::FaceX(Undex3D vox_pos_idx, const Voxel * v_n, const Voxel * v_p)
{
	char	isDraw = ((v_n -> isDraw()) << 0) | ((v_p -> isDraw()) << 1);
	if (isDraw == 0b11)
	{
		char	isTrans = ((v_n -> isTransparent()) << 0) | ((v_p -> isTransparent()) << 1);
		if (isTrans == 0b00) { }
		else if (isTrans == 0b10) { FaceXn(vox_pos_idx, *v_n); }
		else if (isTrans == 0b01) { FaceXp(vox_pos_idx, *v_p); }
	}
	else if (isDraw == 0b01) { FaceXn(vox_pos_idx, *v_n); }
	else if (isDraw == 0b10) { FaceXp(vox_pos_idx, *v_p); }
}
void VoxelRenderData::DataStream::FaceY(Undex3D vox_pos_idx, const Voxel * v_n, const Voxel * v_p)
{
	char	isDraw = ((v_n -> isDraw()) << 0) | ((v_p -> isDraw()) << 1);
	if (isDraw == 0b11)
	{
		char	isTrans = ((v_n -> isTransparent()) << 0) | ((v_p -> isTransparent()) << 1);
		if (isTrans == 0b00) { }
		else if (isTrans == 0b10) { FaceYn(vox_pos_idx, *v_n); }
		else if (isTrans == 0b01) { FaceYp(vox_pos_idx, *v_p); }
	}
	else if (isDraw == 0b01) { FaceYn(vox_pos_idx, *v_n); }
	else if (isDraw == 0b10) { FaceYp(vox_pos_idx, *v_p); }
}
void VoxelRenderData::DataStream::FaceZ(Undex3D vox_pos_idx, const Voxel * v_n, const Voxel * v_p)
{
	char	isDraw = ((v_n -> isDraw()) << 0) | ((v_p -> isDraw()) << 1);
	if (isDraw == 0b11)
	{
		char	isTrans = ((v_n -> isTransparent()) << 0) | ((v_p -> isTransparent()) << 1);
		if (isTrans == 0b00) { }
		else if (isTrans == 0b10) { FaceZn(vox_pos_idx, *v_n); }
		else if (isTrans == 0b01) { FaceZp(vox_pos_idx, *v_p); }
	}
	else if (isDraw == 0b01) { FaceZn(vox_pos_idx, *v_n); }
	else if (isDraw == 0b10) { FaceZp(vox_pos_idx, *v_p); }
}



void VoxelRenderData::DataStream::FaceX(Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_pos_idx.y == Voxel_per_Side || vox_pos_idx.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_pos_idx.x == 0)
	{
		if (ch_n == NULL) { return; }
		vn = &ch_n -> get(vox_pos_idx.set_get_X(Voxel_per_Side - 1));
		vp = &here -> get(vox_pos_idx.set_get_X(0));
		if (!vp -> isDraw()) { return; }
	}
	else if (vox_pos_idx.x == Voxel_per_Side)
	{
		if (ch_p == NULL) { return; }
		vn = &here -> get(vox_pos_idx.set_get_X(Voxel_per_Side - 1));
		vp = &ch_p -> get(vox_pos_idx.set_get_X(0));
		if (!vn -> isDraw()) { return; }
	}
	else
	{
		vn = &here -> get(vox_pos_idx.set_get_X(vox_pos_idx.x - 1));
		vp = &here -> get(vox_pos_idx.set_get_X(vox_pos_idx.x - 0));
	}
	FaceX(vox_pos_idx, vn, vp);
}
void VoxelRenderData::DataStream::FaceY(Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_pos_idx.x == Voxel_per_Side || vox_pos_idx.z == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_pos_idx.y == 0)
	{
		if (ch_n == NULL) { return; }
		vn = &ch_n -> get(vox_pos_idx.set_get_Y(Voxel_per_Side - 1));
		vp = &here -> get(vox_pos_idx.set_get_Y(0));
		if (!vp -> isDraw()) { return; }
	}
	else if (vox_pos_idx.y == Voxel_per_Side)
	{
		if (ch_p == NULL) { return; }
		vn = &here -> get(vox_pos_idx.set_get_Y(Voxel_per_Side - 1));
		vp = &ch_p -> get(vox_pos_idx.set_get_Y(0));
		if (!vn -> isDraw()) { return; }
	}
	else
	{
		vn = &here -> get(vox_pos_idx.set_get_Y(vox_pos_idx.y - 1));
		vp = &here -> get(vox_pos_idx.set_get_Y(vox_pos_idx.y - 0));
	}
	FaceY(vox_pos_idx, vn, vp);
}
void VoxelRenderData::DataStream::FaceZ(Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
{
	if (vox_pos_idx.x == Voxel_per_Side || vox_pos_idx.y == Voxel_per_Side)
		return;

	const Voxel * vn = NULL;
	const Voxel * vp = NULL;
	if (vox_pos_idx.z == 0)
	{
		if (ch_n == NULL) { return; }
		vn = &ch_n -> get(vox_pos_idx.set_get_Z(Voxel_per_Side - 1));
		vp = &here -> get(vox_pos_idx.set_get_Z(0));
		if (!vp -> isDraw()) { return; }
	}
	else if (vox_pos_idx.z == Voxel_per_Side)
	{
		if (ch_p == NULL) { return; }
		vn = &here -> get(vox_pos_idx.set_get_Z(Voxel_per_Side - 1));
		vp = &ch_p -> get(vox_pos_idx.set_get_Z(0));
		if (!vn -> isDraw()) { return; }
	}
	else
	{
		vn = &here -> get(vox_pos_idx.set_get_Z(vox_pos_idx.z - 1));
		vp = &here -> get(vox_pos_idx.set_get_Z(vox_pos_idx.z - 0));
	}
	FaceZ(vox_pos_idx, vn, vp);
}

