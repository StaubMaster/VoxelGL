
#include "VoxelDataTable.hpp"


VoxelData::VoxelData(const char * fileName,
	bool isNoDraw,
	bool isNotSolid,
	bool isTransparent,
	bool isFixedAxis,
	bool isFixedSpin
) :
	fileName(fileName),
	isNoDraw(isNoDraw),
	isNotSolid(isNotSolid),
	isTransparent(isTransparent),
	isFixedAxis(isFixedAxis),
	isFixedSpin(isFixedSpin)
{

}

Voxel	VoxelData::ToVoxel(char idx, char ori) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	if (isFixedAxis) { axis = ori & VOXEL_AXIS_BITS; } else { axis = (std::rand() % 6) + 1; }
	char spin;
	if (isFixedSpin) { spin = ori & VOXEL_SPIN_BITS; } else { spin = (std::rand() % 4) << 3; }

	return Voxel(idx, category, axis | spin);
}
Voxel	VoxelData::ToVoxelForce(char idx, char ori) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	axis = ori & VOXEL_AXIS_BITS;
	char spin;
	spin = ori & VOXEL_SPIN_BITS;

	return Voxel(idx, category, axis | spin);
}
Voxel	VoxelData::ToVoxel(char idx, VoxelHover hover) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	if (isFixedAxis) { axis = hover.hit.from_axis; } else { axis = (std::rand() % 6) + 1; }
	char spin;
	//if (isFixedSpin) { spin = (hover.hit.dir2 << 3) & VOXEL_SPIN_BITS; } else { spin = (std::rand() % 4) << 3; }
	spin = 0;

	return Voxel(idx, category, axis | spin);
}




VoxelDataTable::VoxelDataTable()
{
	Table.clear();
}
VoxelDataTable::~VoxelDataTable()
{
	Table.clear();
}

void	VoxelDataTable::Set(VoxelData vox)
{
	Table.push_back(vox);
}
unsigned int	VoxelDataTable::Length() const
{
	return Table.size();
}
const VoxelData &	VoxelDataTable::Get(unsigned int idx) const
{
	if (idx >= Table.size())
		throw Exception_IndexOutOfRange();
	return Table[idx];
}



unsigned int	VoxelDataTable::InitTextures() const
{
	unsigned int texture_arr;

		glGenTextures(1, &texture_arr);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);

		int	tex_w = 128;
		int	tex_h = 64;
		int	img_count = Table.size();

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, tex_w, tex_h, img_count, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);

		for (int i = 0; i < img_count; i++)
		{
			PNG_Image * temp = PNG_Image::Load(Table[i].fileName);
			PNG_Image * img = temp -> Scale(tex_w, tex_h);
			delete temp;

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tex_w, tex_h, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, img -> data);
			delete img;
		}

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	return texture_arr;
}


const char * VoxelDataTable::Exception_IndexOutOfRange::what() const throw() { return "Index out of Range"; }
