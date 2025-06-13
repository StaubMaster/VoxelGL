
#pragma once

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

# include "VoxelData.hpp"

# include "../Voxel/Voxel.hpp"
# include "../Space/VoxelHover.hpp"

# include "../../openGL/openGL.h"
# include "../../FileParse/PNG/PNG_Image.hpp"

class VoxelDataTable
{
	private:
		std::vector<VoxelData>	Table;

	public:
		VoxelDataTable();
		~VoxelDataTable();

		void				Set(VoxelData vox);
		unsigned int		Length() const;
		const VoxelData &	Get(unsigned int idx) const;

		unsigned int	InitTextures() const;

		class Exception_IndexOutOfRange : public std::exception { public: const char * what() const throw(); };
};
