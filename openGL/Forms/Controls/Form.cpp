
#include "Form.hpp"

static Shader * shader;
static int Uni_Form_Aspect;
static int Uni_Form_Size;

void	Form::CreateDraw()
{
	shader = new Shader("Form",
		"shaders/GUI.vert",
		"shaders/GUI.geom",
		"shaders/GUI.frag"
	);

	Uni_Form_Aspect = shader -> FindUniform("aspectRatio");
	Uni_Form_Size = shader -> FindUniform("windowSize");
}
void	Form::DeleteDraw()
{
	delete shader;
}
int	Form::UniformAspect()
{
	shader -> Use();
	return Uni_Form_Aspect;
}
int	Form::UniformSize()
{
	shader -> Use();
	return Uni_Form_Size;
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

	Visible = false;
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

	Visible = false;
}
Form::~Form()
{
	std::cout << "---- Form " << Buffer_Array << "\n";

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Data);
	glDeleteVertexArrays(1, &Buffer_Array);
}



void	Form::UpdateHover(Point2D mouse)
{
	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i] -> UpdateHover(mouse);
	}
	UpdateBuffer();
}
void	Form::UpdateAnchor(Size2D winSize)
{
	Main.UpdateAnchor(winSize);

	std::cout << "Min: " << Main.Box.Min.X << " : " << Main.Box.Min.Y << "\n";
	std::cout << "Max: " << Main.Box.Max.X << " : " << Main.Box.Max.Y << "\n";

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
	if (!Visible) { return; }

	glClear(GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(Buffer_Array);
	shader -> Use();
	glDrawArrays(GL_POINTS, 0, Data_Count);

	for (size_t i = 1; i < controls.size(); i++)
	{
		controls[i] -> DrawExtra();
	}
}
