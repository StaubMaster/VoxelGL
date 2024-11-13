#version 330

uniform vec3 color;



out vec4 Pixel;



void main()
{
	Pixel = vec4(color, 1);
}
