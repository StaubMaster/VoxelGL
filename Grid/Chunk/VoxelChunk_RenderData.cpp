#include "VoxelChunk.hpp"



#pragma region RenderData
VoxelChunk::RenderData::RenderData()
{
	//std::cout << "++++ VoxelChunk::RenderData\n";
	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Corner);
	glGenBuffers(1, &Buffer_Index);
	Vertex_Count = 0;

	NeedsUpdate = false;
	NeedsBind = false;
	BufferStream = NULL;
}
VoxelChunk::RenderData::~RenderData()
{
	//std::cout << "---- VoxelChunk::RenderData\n";
	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Corner);
	glDeleteBuffers(1, &Buffer_Index);
	glDeleteVertexArrays(1, &Buffer_Array);
}
void	VoxelChunk::RenderData::RequestUpdate()
{
	NeedsUpdate = true;
}

void VoxelChunk::RenderData::UpdateFaceX(VoxelRenderData::DataStream * BitStream, Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
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
	BitStream -> FaceX(vox_pos_idx, vn, vp);
}
void VoxelChunk::RenderData::UpdateFaceY(VoxelRenderData::DataStream * BitStream, Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
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
	BitStream -> FaceY(vox_pos_idx, vn, vp);
}
void VoxelChunk::RenderData::UpdateFaceZ(VoxelRenderData::DataStream * BitStream, Undex3D vox_pos_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p)
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
	BitStream -> FaceZ(vox_pos_idx, vn, vp);
}
void	VoxelChunk::RenderData::Update(const VoxelChunk * here,
	const VoxelChunk * Xn, const VoxelChunk * Xp,
	const VoxelChunk * Yn, const VoxelChunk * Yp,
	const VoxelChunk * Zn, const VoxelChunk * Zp)
{
	if (NeedsUpdate && BufferStream == NULL)
	{
		//std::cout << "BufferUpdate() " << Index << " ...\n";
		NeedsUpdate = false;
		BufferStream = new VoxelRenderData::DataStream(Vertex_per_Chunk * 6 * 6);

		Undex3D voxel_idx;
		do
		{
			UpdateFaceX(BufferStream, voxel_idx, here, Xn, Xp);
			UpdateFaceY(BufferStream, voxel_idx, here, Yn, Yp);
			UpdateFaceZ(BufferStream, voxel_idx, here, Zn, Zp);
		}
		while (Undex3D::loop_exclusive(voxel_idx, 0, Voxel_per_Side + 1));

		NeedsBind = true;
		//std::cout << "BufferUpdate() " << Index << " done\n";
	}
}
void	VoxelChunk::RenderData::Bind()
{
	if (NeedsBind && BufferStream != NULL)
	{
		//std::cout << "BufferBind() " << Index << " ...\n";
		NeedsBind = false;

		glBindVertexArray(Buffer_Array);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corner);
		BufferStream -> ToBuffer(Vertex_Count);

		delete BufferStream;
		BufferStream = NULL;
		//std::cout << "BufferBind() " << Index << " done\n";
	}
}
void	VoxelChunk::RenderData::Draw() const
{
	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_TRIANGLES, 0, Vertex_Count);
}
#pragma endregion
