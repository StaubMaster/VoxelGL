#include "FormControl.hpp"


Point2D::Point2D() : X(0), Y(0) { }
Point2D::Point2D(float x, float y) : X(x), Y(y) { }

Color::Color(float r, float g, float b) : R(r), G(g), B(b) { }





FormControl::FormControl(float min_x, float min_y, float max_x, float max_y) :
	Min(min_x, min_y), Max(max_x, max_y),
	render(NULL)
{

}
FormControl::~FormControl()
{

}
FormControl::FormControl(const FormControl & other) :
	Min(other.Min), Max(other.Max), render(other.render)
{

}
const FormControl & FormControl::operator =(const FormControl & other)
{
	Min = other.Min;
	Max = other.Max;
	render = other.render;
	return *this;
}

bool	FormControl::isHover(Point2D Mouse) const
{
	return (Min.X < Mouse.X && Mouse.X < Max.X && 
			Min.Y < Mouse.Y && Mouse.Y < Max.Y
	);
}
void	FormControl::Update(Point2D Mouse)
{
	(void)Mouse;
}

void	FormControl::UpdateRender()
{
	if (render == NULL)
		return;
}
FormControlRenderData	FormControl::getRenderData() const
{
	return (FormControlRenderData) {
		Min, Max,
		Color(0.5f, 0.5f, 0.5f),
		0.99f
	};
}
void	FormControl::setRenderData(FormControlRenderData * ptr)
{
	render = ptr;
}





FormButton::FormButton(float min_x, float min_y, float max_x, float max_y) :
	FormControl(min_x, min_y, max_x, max_y)
{
	
}
FormButton::~FormButton()
{

}

void	FormButton::Update(Point2D Mouse)
{
	if (isHover(Mouse))
	{
		render -> Col.R = 0.25;
		render -> Col.G = 0.75;
		render -> Col.B = 0.25;
	}
	else
	{
		render -> Col.R = 0.25;
		render -> Col.G = 0.25;
		render -> Col.B = 0.25;
	}
}

void	FormButton::UpdateRender()
{
	if (render == NULL)
		return;
	render -> Col.R = 0.25;
	render -> Col.G = 0.25;
	render -> Col.B = 0.25;
	render -> Depth = 0.5f;
}





FormSlot::FormSlot(float min_x, float min_y, float max_x, float max_y) :
	FormControl(min_x, min_y, max_x, max_y)
{
	
}
FormSlot::~FormSlot()
{

}
Point2D	FormSlot::getCenter() const
{
	return Point2D(
		(Min.X + Max.X) / 2,
		(Min.Y + Max.Y) / 2
	);
}
void	FormSlot::Update(Point2D Mouse)
{
	if (isHover(Mouse))
	{
		render -> Col.R = 0.85;
		render -> Col.G = 0.85;
		render -> Col.B = 0.85;
	}
	else
	{
		render -> Col.R = 0.75;
		render -> Col.G = 0.75;
		render -> Col.B = 0.75;
	}
}

void	FormSlot::UpdateRender()
{
	if (render == NULL)
		return;
	render -> Col.R = 0.75;
	render -> Col.G = 0.75;
	render -> Col.B = 0.75;
	render -> Depth = 0.5f;
}




FormControlList::FormControlList()
{
	shader = new Shader(
		"shaders/GUI.vert",
		"shaders/GUI.geom",
		"shaders/GUI.frag"
	);

	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Data);
	Data_Count = 0;
}
FormControlList::~FormControlList()
{
	delete shader;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Data);
	glDeleteVertexArrays(1, &Buffer_Array);
}

void	FormControlList::Update(Window * win)
{
	double	mouse_x_dbl;
	double	mouse_y_dbl;
	Point2D	mouse;

	glfwGetCursorPos(win -> win, &mouse_x_dbl, &mouse_y_dbl);
	mouse.X = (mouse_x_dbl / 500) - 1;
	mouse.Y = 1 - (mouse_y_dbl / 500);

	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i] -> Update(mouse);
	}
	UpdateBuffer();
}

void	FormControlList::Insert(FormControl & control)
{
	controls.push_back(&control);
	renders.push_back(control.getRenderData());

	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i] -> setRenderData(&renders[i]);
		controls[i] -> UpdateRender();
	}
}

void	FormControlList::UpdateBuffer()
{
	Data_Count = renders.size();

	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Data);
	glBufferData(GL_ARRAY_BUFFER, Data_Count * sizeof(FormControlRenderData), renders.data(), GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(FormControlRenderData), (void *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(FormControlRenderData), (void *)(sizeof(float) * 2));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(FormControlRenderData), (void *)(sizeof(float) * 4));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(FormControlRenderData), (void *)(sizeof(float) * 7));
}
void	FormControlList::Draw() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(Buffer_Array);
	shader -> Use();
	glDrawArrays(GL_POINTS, 0, Data_Count);
}
