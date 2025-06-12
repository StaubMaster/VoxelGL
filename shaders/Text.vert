#version 330

uniform vec2 windowSize;



layout(location = 0) in vec3 VCharPos;
layout(location = 1) in vec2 VCharTexPos;

out Vert_Char
{
	vec2	TexPos;
} vs_out;



void main()
{
	vec3 pos;
	pos.x = 2 * (VCharPos.x / windowSize.x) - 1;
	pos.y = 1 - (VCharPos.y / windowSize.y) * 2;
	pos.z = VCharPos.z;

	gl_Position = vec4(pos, 1);
	vs_out.TexPos = VCharTexPos;
}
