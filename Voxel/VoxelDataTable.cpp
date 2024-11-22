
#include "VoxelDataTabel.hpp"

VoxelData::VoxelData(const char * fileName, bool isNoDraw, bool isTransparent, bool isSolid) :
	fileName(fileName),
	isNoDraw(isNoDraw),
	isTransparent(isTransparent),
	isSolid(isSolid)
{

}



VoxelDataTabel::VoxelDataTabel()
{
	Tabel.clear();
}
VoxelDataTabel::~VoxelDataTabel()
{
	Tabel.clear();
}

void	VoxelDataTabel::Cat(VoxelData vox)
{
	Tabel.push_back(vox);
}
