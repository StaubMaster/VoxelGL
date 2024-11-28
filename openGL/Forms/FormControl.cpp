#include "FormControl.hpp"



FormControl::FormControl(float min_x, float min_y, float max_x, float max_y) :
	MinX(min_x), MinY(min_y), MaxX(max_x), MaxY(max_y),
	render(NULL)
{

}
FormControl::~FormControl()
{

}
FormControl::FormControl(const FormControl & other) :
	MinX(other.MinX), MinY(other.MinY), MaxX(other.MaxX), MaxY(other.MaxY),
	render(other.render)
{

}
const FormControl & FormControl::operator =(const FormControl & other)
{
	MinX = other.MinX;
	MinY = other.MinY;
	MaxX = other.MaxX;
	MaxY = other.MaxY;
	render = other.render;
	return *this;
}

bool	FormControl::isHover(float mouse_x, float mouse_y) const
{
	return (MinX < mouse_x && mouse_x < MaxX && 
			MinY < mouse_y && mouse_y < MaxY
	);
}
void	FormControl::Update(float mouse_x, float mouse_y)
{
	(void)mouse_x;
	(void)mouse_y;
}

void	FormControl::UpdateRender()
{
	if (render == NULL)
		return;
}
FormControlRenderData	FormControl::getRenderData() const
{
	return (FormControlRenderData) {
		MinX, MinY, MaxX, MaxY,
		0.5f, 0.5f, 0.5f,
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

void	FormButton::Update(float mouse_x, float mouse_y)
{
	if (isHover(mouse_x, mouse_y))
	{
		render -> ColR = 0.25;
		render -> ColG = 0.75;
		render -> ColB = 0.25;
	}
	else
	{
		render -> ColR = 0.25;
		render -> ColG = 0.25;
		render -> ColB = 0.25;
	}
}

void	FormButton::UpdateRender()
{
	if (render == NULL)
		return;
	render -> ColR = 0.25;
	render -> ColG = 0.25;
	render -> ColB = 0.25;
	render -> Depth = 0.5f;
}





FormSlot::FormSlot(float min_x, float min_y, float max_x, float max_y) :
	FormControl(min_x, min_y, max_x, max_y)
{
	
}
FormSlot::~FormSlot()
{

}

void	FormSlot::Update(float mouse_x, float mouse_y)
{
	if (isHover(mouse_x, mouse_y))
	{
		render -> ColR = 0.85;
		render -> ColG = 0.85;
		render -> ColB = 0.85;
	}
	else
	{
		render -> ColR = 0.75;
		render -> ColG = 0.75;
		render -> ColB = 0.75;
	}
}

void	FormSlot::UpdateRender()
{
	if (render == NULL)
		return;
	render -> ColR = 0.75;
	render -> ColG = 0.75;
	render -> ColB = 0.75;
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
	float	mouse_x;
	float	mouse_y;

	glfwGetCursorPos(win -> win, &mouse_x_dbl, &mouse_y_dbl);
	mouse_x = (mouse_x_dbl / 500) - 1;
	mouse_y = 1 - (mouse_y_dbl / 500);

	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i] -> Update(mouse_x, mouse_y);
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
