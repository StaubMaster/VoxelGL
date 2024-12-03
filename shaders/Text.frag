#version 330

uniform sampler2D texture0;



in Vert_Char
{
	vec2	TexPos;
} fs_in;

out vec4 Pixel;



void main()
{
	vec4 col;
	col = texture(texture0, fs_in.TexPos);

	if (col.a == 0)
		discard;

	Pixel = col;
}
