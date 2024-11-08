
#include "View.hpp"

View::View()
{

}
View::~View()
{

}
void	View::move(Point rel)
{
	rotate_fore(&rel.z, &rel.x, ang.cos_y, ang.sin_y);
	pos.x += rel.x;
	pos.y += rel.y;
	pos.z += rel.z;
}
void	View::turn(Angle rel)
{
	ang.x += rel.x;
	ang.y += rel.y;
	ang.z += rel.z;
	ang.UpdateSinCos();
}





void	view_init(t_view *view, float move, float turn)
{
	view -> data = (float *)view;
	view -> pos_x = 0;
	view -> pos_y = 0;
	view -> pos_z = 0;
	view -> sin_x = 0;
	view -> sin_y = 0;
	view -> sin_z = 0;
	view -> cos_x = 1;
	view -> cos_y = 1;
	view -> cos_z = 1;
	view -> ang_x = 0;
	view -> ang_y = 0;
	view -> ang_z = 0;
	view -> move_speed = move;
	view -> turn_speed = turn;
}

static void view_move(t_view *view, GLFWwindow *win)
{
	float rel[] = { 0.0f, 0.0f, 0.0f };
	if (glfwGetKey(win, GLFW_KEY_D))			{ rel[0] -= view -> move_speed; }
	if (glfwGetKey(win, GLFW_KEY_A))			{ rel[0] += view -> move_speed; }
	if (glfwGetKey(win, GLFW_KEY_SPACE))		{ rel[1] -= view -> move_speed; }
	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))	{ rel[1] += view -> move_speed; }
	if (glfwGetKey(win, GLFW_KEY_S))			{ rel[2] -= view -> move_speed; }
	if (glfwGetKey(win, GLFW_KEY_W))			{ rel[2] += view -> move_speed; }
	rotate_fore(&rel[2], &rel[0], view -> cos_y, view -> sin_y);
	view -> pos_x += rel[0];
	view -> pos_y += rel[1];
	view -> pos_z += rel[2];
}

static void view_turn(t_view *view, GLFWwindow *win)
{
	float rel[] = { 0.0f, 0.0f, 0.0f };
	if (glfwGetKey(win, GLFW_KEY_DOWN))		{ rel[0] += view -> turn_speed; }
	if (glfwGetKey(win, GLFW_KEY_UP))		{ rel[0] -= view -> turn_speed; }
	if (glfwGetKey(win, GLFW_KEY_LEFT))		{ rel[1] += view -> turn_speed; }
	if (glfwGetKey(win, GLFW_KEY_RIGHT))	{ rel[1] -= view -> turn_speed; }
	view -> ang_x += rel[0];
	view -> ang_y += rel[1];
	view -> ang_z += rel[2];
	view -> sin_x = sin(view -> ang_x);
	view -> cos_x = cos(view -> ang_x);
	view -> sin_y = sin(view -> ang_y);
	view -> cos_y = cos(view -> ang_y);
	view -> sin_z = sin(view -> ang_z);
	view -> cos_z = cos(view -> ang_z);
}

static void check_mouse_lock(GLFWwindow *win);
static void view_mouse_turn(t_view *view, GLFWwindow *win);

static int mouse_lock = 0;
void view_move_turn(t_view *view, GLFWwindow *win)
{
	view_move(view, win);
	view_turn(view, win);

	check_mouse_lock(win);
	if ((mouse_lock & 0b10) != 0)
		view_mouse_turn(view, win);
}

static double middle_x;
static double middle_y;
static void view_mouse_turn(t_view *view, GLFWwindow *win)
{
	double x, y;
	glfwGetCursorPos(win, &x, &y);

	double diff_x, diff_y;
	diff_x = middle_x - x;
	diff_y = middle_y - y;

	view -> ang_x -= diff_y * 0.005;
	view -> ang_y += diff_x * 0.005;

	view -> sin_x = sin(view -> ang_x);
	view -> cos_x = cos(view -> ang_x);
	view -> sin_y = sin(view -> ang_y);
	view -> cos_y = cos(view -> ang_y);
	view -> sin_z = sin(view -> ang_z);
	view -> cos_z = cos(view -> ang_z);

	glfwSetCursorPos(win, middle_x, middle_y);
}

static void view_middle(GLFWwindow *win)
{
	int w, h;
	glfwGetWindowSize(win, &w, &h);
	middle_x = w * 0.5;
	middle_y = h * 0.5;
	glfwSetCursorPos(win, middle_x, middle_y);
}

static void check_mouse_lock(GLFWwindow *win)
{
	if (glfwGetKey(win, GLFW_KEY_TAB))
	{
		if ((mouse_lock & 0b01) == 0)
		{
			if ((mouse_lock & 0b10) == 0)
				view_middle(win);
			mouse_lock ^= 0b10;
		}
		mouse_lock |= 0b01;
	}
	else
		mouse_lock &= 0b10;
}
