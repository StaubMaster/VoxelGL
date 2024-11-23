#version 330

const vec3 light = normalize(vec3(+1, -2, +3));
uniform sampler2DArray texture0;



in Geom_Tex
{
	vec3	Normal;
	vec3	Tex_pos;
} fs_in;

out vec4 Pixel;



void main()
{
	float l;
	l = dot(normalize(fs_in.Normal), light);
	l = max(l, 0.3);
	l = 1;

	vec4 col;
	col = texture(texture0, fs_in.Tex_pos);

	if (col.a == 0)
		discard;

	Pixel = vec4(col * l);
}
