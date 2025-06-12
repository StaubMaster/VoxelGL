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
			BufferStream -> FaceX(voxel_idx, here, Xn, Xp);
			BufferStream -> FaceY(voxel_idx, here, Yn, Yp);
			BufferStream -> FaceZ(voxel_idx, here, Zn, Zp);
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
