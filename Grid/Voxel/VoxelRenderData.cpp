
#include "VoxelRenderData.hpp"
#include "../Chunk/VoxelChunk.hpp"



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

	if (vox_axis == 0)                 { coords = Default::Same; }
	else if (vox_axis == AXIS_BITS_XN) { coords = Default::XM; }
	else if (vox_axis == AXIS_BITS_YN) { coords = Default::ZM; }
	else if (vox_axis == AXIS_BITS_ZN) { coords = Default::YM; }
	else if (vox_axis == AXIS_BITS_XP) { coords = Default::XP; }
	else if (vox_axis == AXIS_BITS_YP) { coords = Default::ZP; }
	else if (vox_axis == AXIS_BITS_ZP) { coords = Default::YP; }
	else                               { coords = Default::Same; }

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
	else { coords = Default::Same; }

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



void VoxelRenderData::DataStream::FaceN(Undex3D vox_pos_idx, const Voxel & vox, char tex_axis, Undex3D udx[6])
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + udx[0], tex_axis | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + udx[1], tex_axis | TEXTURE_MIN_MAX, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + udx[2], tex_axis | TEXTURE_MAX_MIN, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + udx[3], tex_axis | TEXTURE_MAX_MIN, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + udx[4], tex_axis | TEXTURE_MIN_MAX, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + udx[5], tex_axis | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceP(Undex3D vox_pos_idx, const Voxel & vox, char tex_axis, Undex3D udx[6])
{
	Data[Index + 0] = VoxelRenderData(vox_pos_idx + udx[0], tex_axis | TEXTURE_MIN_MIN, vox);
	Data[Index + 1] = VoxelRenderData(vox_pos_idx + udx[1], tex_axis | TEXTURE_MAX_MIN, vox);
	Data[Index + 2] = VoxelRenderData(vox_pos_idx + udx[2], tex_axis | TEXTURE_MIN_MAX, vox);
	Data[Index + 3] = VoxelRenderData(vox_pos_idx + udx[3], tex_axis | TEXTURE_MIN_MAX, vox);
	Data[Index + 4] = VoxelRenderData(vox_pos_idx + udx[4], tex_axis | TEXTURE_MAX_MIN, vox);
	Data[Index + 5] = VoxelRenderData(vox_pos_idx + udx[5], tex_axis | TEXTURE_MAX_MAX, vox);
	Index += 6;
}
void VoxelRenderData::DataStream::FaceXn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(0, 1, 0),
		Undex3D(0, 0, 1),
		Undex3D(0, 0, 1),
		Undex3D(0, 1, 0),
		Undex3D(0, 1, 1),
	};
	FaceN(vox_pos_idx, vox, TEXTURE_XM, udx);
}
void VoxelRenderData::DataStream::FaceXp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(0, 0, 1),
		Undex3D(0, 1, 0),
		Undex3D(0, 1, 0),
		Undex3D(0, 0, 1),
		Undex3D(0, 1, 1),
	};
	FaceP(vox_pos_idx, vox, TEXTURE_XP, udx);
}
void VoxelRenderData::DataStream::FaceYn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(0, 0, 1),
		Undex3D(1, 0, 0),
		Undex3D(1, 0, 0),
		Undex3D(0, 0, 1),
		Undex3D(1, 0, 1),
	};
	FaceN(vox_pos_idx, vox, TEXTURE_YM, udx);
}
void VoxelRenderData::DataStream::FaceYp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(1, 0, 0),
		Undex3D(0, 0, 1),
		Undex3D(0, 0, 1),
		Undex3D(1, 0, 0),
		Undex3D(1, 0, 1),
	};
	FaceP(vox_pos_idx, vox, TEXTURE_YP, udx);
}
void VoxelRenderData::DataStream::FaceZn(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(1, 0, 0),
		Undex3D(0, 1, 0),
		Undex3D(0, 1, 0),
		Undex3D(1, 0, 0),
		Undex3D(1, 1, 0),
	};
	FaceP(vox_pos_idx, vox, TEXTURE_ZM, udx);
}
void VoxelRenderData::DataStream::FaceZp(Undex3D vox_pos_idx, const Voxel & vox)
{
	Undex3D udx[6] = {
		Undex3D(0, 0, 0),
		Undex3D(0, 1, 0),
		Undex3D(1, 0, 0),
		Undex3D(1, 0, 0),
		Undex3D(0, 1, 0),
		Undex3D(1, 1, 0),
	};
	FaceP(vox_pos_idx, vox, TEXTURE_ZP, udx);
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

