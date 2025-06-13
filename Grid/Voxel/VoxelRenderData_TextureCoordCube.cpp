#include "VoxelRenderData.hpp"
#include "../Chunk/VoxelChunk.hpp"



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