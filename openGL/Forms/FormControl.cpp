#include "FormControl.hpp"


Point2D::Point2D() : X(0), Y(0) { }
Point2D::Point2D(float x, float y) : X(x), Y(y) { }

Color::Color(float r, float g, float b) : R(r), G(g), B(b) { }

Box2D::Box2D() : Min(), Max() { }
Box2D::Box2D(float x1, float y1, float x2, float y2)
{
	Min.X = std::min(x1, x2);
	Min.Y = std::min(y1, y2);
	Max.X = std::max(x1, x2);
	Max.Y = std::max(y1, y2);
}
Box2D::Box2D(Point2D p1, Point2D p2)
{
	Min.X = std::min(p1.X, p2.X);
	Min.Y = std::min(p1.Y, p2.Y);
	Max.X = std::max(p1.X, p2.X);
	Max.Y = std::max(p1.Y, p2.Y);
}




Control::Control() :
	Box(),
	render(NULL)
{

}
Control::Control(float min_x, float min_y, float max_x, float max_y) :
	Box(min_x, min_y, max_x, max_y),
	render(NULL)
{

}
Control::Control(Box2D box) :
	Box(box),
	render(NULL)
{

}
Control::~Control()
{

}
Control::Control(const Control & other) :
	Box(other.Box), render(other.render)
{

}
const Control & Control::operator =(const Control & other)
{
	Box = other.Box;
	render = other.render;
	return *this;
}

bool	Control::isHover(Point2D Mouse) const
{
	return (Box.Min.X < Mouse.X && Mouse.X < Box.Max.X && 
			Box.Min.Y < Mouse.Y && Mouse.Y < Box.Max.Y
	);
}
void	Control::Update(Point2D Mouse)
{
	(void)Mouse;
}

void	Control::UpdateRender()
{
	if (render == NULL)
		return;
}
FormControlRenderData	Control::getRenderData() const
{
	return (FormControlRenderData) {
		Box,
		Color(0.5f, 0.5f, 0.5f),
		0.99f
	};
}
void	Control::setRenderData(FormControlRenderData * ptr)
{
	render = ptr;
}





FormButton::FormButton(float min_x, float min_y, float max_x, float max_y) :
	Control(min_x, min_y, max_x, max_y)
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





FormSlot::FormSlot() :
	Control()
{
	itemID = -1;
}
FormSlot::FormSlot(float min_x, float min_y, float max_x, float max_y) :
	Control(min_x, min_y, max_x, max_y)
{
	itemID = -1;
}
FormSlot::~FormSlot()
{

}
Point2D	FormSlot::getCenter() const
{
	return Point2D(
		(Box.Min.X + Box.Max.X) / 2,
		(Box.Min.Y + Box.Max.Y) / 2
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

void	FormSlot::SwapItem(int & ID)
{
	int temp = ID;
	ID = itemID;
	itemID = temp;
}
void	FormSlot::DrawItem()
{
	if (itemID == -1) { return; }
	Point2D center = getCenter();
	ItemVoxel::Draw(center.X, center.Y, itemID);
}





Form::Form(Box2D box) :
	Main(box)
{
	CreateDraw();

	controls.push_back(&Main);
	renders.push_back(Main.getRenderData());
	Main.setRenderData(&renders[0]);
	Main.UpdateRender();
}
Form::~Form()
{
	DeleteDraw();
}

void	Form::Update(Window * win)
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

void	Form::Insert(Control & control)
{
	controls.push_back(&control);
	renders.push_back(control.getRenderData());

	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i] -> setRenderData(&renders[i]);
		controls[i] -> UpdateRender();
	}
}

void	Form::CreateDraw()
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
void	Form::DeleteDraw()
{
	delete shader;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Data);
	glDeleteVertexArrays(1, &Buffer_Array);
}
void	Form::UpdateBuffer()
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
void	Form::Draw() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(Buffer_Array);
	shader -> Use();
	glDrawArrays(GL_POINTS, 0, Data_Count);
}
