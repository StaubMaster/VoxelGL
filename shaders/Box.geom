#version 330

layout(points) in;
layout(line_strip, max_vertices = 16) out;

in Box_Vert
{
	vec3[8]	Absolut;
	vec4[8]	Project;
}	gs_in[];

out vec3 Color;



void emitCorner(int i)
{
	gl_Position = gs_in[0].Project[i];
	EmitVertex();
}

void emitSegment(int i1, int i2, int i3, int i4)
{
	emitCorner(i1);
	emitCorner(i2);
	emitCorner(i3);
	emitCorner(i4);
	EndPrimitive();
}

void main()
{
	Color = vec3(0, 0, 0);
	emitSegment(0, 1, 5, 4);
	emitSegment(1, 2, 6, 5);
	emitSegment(2, 3, 7, 6);
	emitSegment(3, 0, 4, 7);
}
