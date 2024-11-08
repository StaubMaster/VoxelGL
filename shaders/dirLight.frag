#version 330

const vec3 light = vec3(+0.267261, -0.534522, +0.801784);

uniform sampler2D texture0;

in Geom_Out
{
	vec2 Tex;
	vec3 Normal;
} fs_in;

out vec4 Pixel;


void main()
{
	float f;
	f = dot(fs_in.Normal, light);
	f = max(f, 0.03);

	vec4 col;
	col = texture(texture0, fs_in.Tex);
	col = col * f;

	Pixel = vec4(col);
}
