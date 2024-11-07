#version 330

layout(location = 0) in vec2 Pos;
layout(location = 1) in vec3 Col;

out vec3 Color;

void main()
{
	Color = Col;
	gl_Position = vec4(Pos, 0, 1);
}
