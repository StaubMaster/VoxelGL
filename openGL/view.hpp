
#ifndef VIEW_H
# define VIEW_H
# include "openGL.h"
# include "Abstract/math3D.hpp"

class View
{
	private:
		struct depth_s
		{
			float	depthN;
			float	depthF;

			float	diff;
			float	sum;

			float	d0;
			float	d1;
			float	d2;
		};
		static depth_s calc_depth(float near, float far);

	public:
		Point	pos;
		Angle	ang;

		depth_s	depth;

	public:
		View();
		~View();

	public:
		void	move(Point rel);
		void	turn(Angle rel);

		void	uniform(int uni) const;
		void	uniform_depth(int uni) const;
};

typedef struct s_view
{
	float	pos_x, pos_y, pos_z;
	float	sin_x, sin_y, sin_z;
	float	cos_x, cos_y, cos_z;
	float	ang_x, ang_y, ang_z;
	float	*data;
	float	move_speed;
	float	turn_speed;
}	t_view;

void	view_init(t_view *view, float move, float turn);
void	view_move_turn(t_view *view, GLFWwindow *win);
void	view_uniform(t_view *view, int uni);

#endif
