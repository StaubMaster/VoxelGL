#version 330

uniform sampler2D texture0;



in Tex
{
	vec2	Tex_pos;
} fs_in;

out vec4 Pixel;



void main()
{
	vec4 col;
	col = texture(texture0, fs_in.Tex_pos);

	Pixel = vec4(col);
}
