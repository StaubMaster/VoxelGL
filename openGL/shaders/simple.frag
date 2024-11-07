#version 330

in vec3 Color;

out vec4 Pixel;

void main()
{
	Pixel = vec4(Color, 1);
}
