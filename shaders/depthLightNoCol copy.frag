#version 330

const vec3 light = vec3(+0.267261, +0.534522, +0.801784);

in Geom_Out
{
	vec3 Normal;
} fs_in;

out vec4 Pixel;


void main()
{
	float f;
	f = dot(fs_in.Normal, light);
	f = max(f, 0.3);

	vec4 col;
	col = vec4(0.5, 0.5, 0.5, 1);
	//col = vec4(1, 1, 1, 1);
	col = col * f;

	Pixel = vec4(col);
}
