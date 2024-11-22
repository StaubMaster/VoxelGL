
#ifndef VOXELDATATABLE_HPP
# define VOXELDATATABLE_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

struct VoxelData
{
	const char *	fileName;
	bool			isNoDraw;
	bool			isTransparent;
	bool			isSolid;

	VoxelData(const char * fileName, bool isNoDraw, bool isTransparent, bool isSolid);
};

class VoxelDataTabel
{
	private:
		std::vector<VoxelData>	Tabel;

	public:
		VoxelDataTabel();
		~VoxelDataTabel();

		void	Cat(VoxelData vox);
};

#endif
