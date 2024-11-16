#version 330



layout(location = 0) in vec2 VPos;
layout(location = 1) in vec2 VTex;

out Tex
{
	vec2	Tex_pos;
}	vs_out;



void main()
{
	vs_out.Tex_pos = VTex;

	gl_Position = vec4(VPos, 0, 1);
}
