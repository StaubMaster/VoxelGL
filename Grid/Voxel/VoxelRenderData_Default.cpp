#include "VoxelRenderData.hpp"



VoxelRenderData::TextureCoordCube VoxelRenderData::Default::Same = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.75f, 0.0f, 1.0f },	//	X+
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::ZM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::XM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::YM = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.0f, 0.5f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.0f, 0.5f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.5f, 1.0f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.50f, 0.0f, 0.5f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.00f, 0.25f, 0.5f, 1.0f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.75f, 0.5f, 1.0f },	//	Z+
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::ZP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::XP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	false,
};
VoxelRenderData::TextureCoordCube VoxelRenderData::Default::YP = (VoxelRenderData::TextureCoordCube)
{
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 1.0f, 0.5f },	//	Z+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 1.0f, 0.5f },	//	X+
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 0.5f, 0.0f },	//	Y-
	(VoxelRenderData::TextureCoordFace){ 0.50f, 0.25f, 1.0f, 0.5f },	//	Y+
	(VoxelRenderData::TextureCoordFace){ 0.25f, 0.00f, 0.5f, 0.0f },	//	X-
	(VoxelRenderData::TextureCoordFace){ 0.75f, 0.50f, 0.5f, 0.0f },	//	Z-
	false,
};
