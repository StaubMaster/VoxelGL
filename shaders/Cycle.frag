#version 330

uniform float cycle;



out vec4 Pixel;



void main()
{
	vec3 col1 = vec3(0, 0, 0);
	vec3 col2 = vec3(1, 1, 1);

	float t = (sin(cycle) + 1) / 2;

	vec3 col = col1 * t + col2 * (1 - t);

	Pixel = vec4(col, 1);
}
