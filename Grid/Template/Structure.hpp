
#pragma once

# include "../../openGL/Abstract/math3D.hpp"

# include "../Voxel/Voxel.hpp"

struct StructureData
{
	Undex3D		Size;
	Voxel	*	Data;
	Voxel		Default;
};

struct Structure
{
	private:
		StructureData	& structureData;
		Index3D			globalPos;

	public:
		Structure(StructureData & data, Index3D global);

	private:
		Structure(const Structure & other) = delete;
		const Structure & operator =(const Structure & other) = delete;

	public:
		bool	relativeBool(Index3D global);
		Voxel	relative(Index3D global);
};
