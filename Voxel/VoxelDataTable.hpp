
#ifndef VOXELDATATABLE_HPP
# define VOXELDATATABLE_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

# include "Voxel.hpp"

struct VoxelData
{
	const char *	fileName;
	bool			isNoDraw;
	bool			isNotSolid;
	bool			isTransparent;
	bool			isFixedAxis;
	bool			isFixedSpin;

	VoxelData(const char * fileName,
		bool isNoDraw,
		bool isNotSolid,
		bool isTransparent,
		bool isFixedAxis,
		bool isFixedSpin
	);

	Voxel	ToVoxel(char idx, char ori) const;
	Voxel	ToVoxelForce(char idx, char ori) const;
};

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

		class Exception_IndexOutOfRange : public std::exception { public: const char * what() const throw(); };
};

#endif
