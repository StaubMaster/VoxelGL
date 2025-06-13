#include "VoxelDataTable.hpp"



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
