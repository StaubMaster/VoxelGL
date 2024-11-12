
#ifndef VOXEL_HPP
# define VOXEL_HPP

class Voxel
{
	private:
		char	ID;
	
	public:
		Voxel();
		Voxel(char id);

		bool	isSolid() const;
};

#endif
