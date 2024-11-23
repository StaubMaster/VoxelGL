#version 330

uniform vec3[3] viewTrans;
uniform float[7] depthFactor;
uniform ivec3 chunk_pos;



layout(location = 0) in uint VIdx;
layout(location = 1) in uint VTex_Idx;
layout(location = 2) in vec2 VTex_pos;

out Vert_Tex
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

vec4 proj(vec3 p_inn)
{
	p_inn = ASD(p_inn - viewTrans[0], viewTrans[1], viewTrans[2]);

	vec4 p_out;
	p_out.x = p_inn.x;
	p_out.y = p_inn.y;
	p_out.z = p_inn.z * depthFactor[5] - depthFactor[6];
	p_out.w = p_inn.z;
	return p_out;
}

void main()
{
	uvec3 idx;
	idx.x = (VIdx) & uint((0xFF));
	idx.y = (VIdx >> 8) & uint((0xFF));
	idx.z = (VIdx >> 16) & uint((0xFF));

	vs_out.Absolut = vec3(idx) + (chunk_pos * 16);
	vs_out.Tex_pos = vec3(VTex_pos, VTex_Idx);

	gl_Position = proj(vs_out.Absolut);
}
