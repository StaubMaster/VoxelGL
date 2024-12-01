#version 330

uniform vec2 UPos;
uniform vec3[2] USpin;
uniform uint UTex_Idx;
uniform vec2 UAspect;
uniform vec2 UWin_Size;

layout(location = 0) in vec3 VPos;
layout(location = 1) in vec2 VTex_pos;

out Vert_Inv
{
	vec3	Absolut;
	vec3	Tex_pos;
} vs_out;



void rot(inout float pls, inout float mns, in float fsin, in float fcos)
{
	float tmp;
	tmp = fcos * pls - fsin * mns;
	mns = fcos * mns + fsin * pls;
	pls = tmp;
}

vec3 ASD(in vec3 p, in vec3 wSin, in vec3 wCos)
{
	vec3 n = p;
	rot(n.x, n.z, wSin.x, wCos.x);
	rot(n.y, n.z, wSin.y, wCos.y);
	rot(n.y, n.x, wSin.z, wCos.z);
	return n;
}

vec3 DSA(in vec3 p, in vec3 wSin, in vec3 wCos)
{
	vec3 n = p;
	rot(n.x, n.y, wSin.z, wCos.z);
	rot(n.z, n.y, wSin.y, wCos.y);
	rot(n.z, n.x, wSin.x, wCos.x);
	return n;
}

void main()
{
	vs_out.Tex_pos = vec3(VTex_pos, UTex_Idx);
	vs_out.Absolut = DSA(VPos, USpin[0], USpin[1]);
	vs_out.Absolut.xy *= UAspect;

	vec2	pos;
	pos.x = 2 * (UPos.x / UWin_Size.x) - 1;
	pos.y = 1 - (UPos.y / UWin_Size.y) * 2;

	vs_out.Absolut.xy += pos;
	vs_out.Absolut.z *= 0.01;
	gl_Position = vec4(vs_out.Absolut, 1);
}
