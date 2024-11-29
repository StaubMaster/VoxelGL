
#include "Form.hpp"

static Shader * shader;
void	Form::CreateDraw()
{
	shader = new Shader(
		"shaders/GUI.vert",
		"shaders/GUI.geom",
		"shaders/GUI.frag"
	);
}
void	Form::DeleteDraw()
{
	delete shader;
}



Form::Form()
{
	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Data);
	Data_Count = 0;

	std::cout << "++++ Form " << Buffer_Array << "\n";

	controls.push_back(&Main);
	renders.push_back(Main.getRenderData());
	Main.setRenderData(&renders[0]);
}
Form::Form(Box2D box) :
	Main(box)
{
	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Data);
	Data_Count = 0;

	std::cout << "++++ Form " << Buffer_Array << "\n";

	controls.push_back(&Main);
	renders.push_back(Main.getRenderData());
	Main.setRenderData(&renders[0]);
	Main.UpdateRender();
}
Form::~Form()
{
	std::cout << "---- Form " << Buffer_Array << "\n";

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Data);
	glDeleteVertexArrays(1, &Buffer_Array);
}



void	Form::ChangeMainSize(Box2D box)
{
	Main.ChangeBox(box);
}



void	Form::Update(Point2D mouse)
{
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

	for (size_t i = 1; i < controls.size(); i++)
	{
		controls[i] -> DrawExtra();
	}
}
