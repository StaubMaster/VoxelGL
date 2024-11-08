
#include "math3D.h"

void	rotate_fore(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos - mns[0] * sin;
	mns[0] = mns[0] * cos + pls[0] * sin;
	pls[0] = temppp;
}
void	rotate_back(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos + mns[0] * sin;
	mns[0] = mns[0] * cos - pls[0] * sin;
	pls[0] = temppp;
}

