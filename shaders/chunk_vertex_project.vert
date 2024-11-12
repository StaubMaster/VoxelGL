#version 330

layout(location = 0) in uint VIdx;

uniform ivec3 chunk_pos;
uniform vec3[3] view;
const float projF = 2.0;

out Vert_Out
{
	vec3 NonProj;
} vs_out;


void rot(inout float pls, inout float mns, float wCos, float wSin)
{
	float tmp;
	tmp = pls * wCos - mns * wSin;
	mns = mns * wCos + pls * wSin;
	pls = tmp;
}

vec3 ASD(vec3 p, vec3 wSin, vec3 wCos)
{
	rot(p.x, p.y, wCos.z, wSin.z);
	rot(p.x, p.z, wCos.y, wSin.y);
	rot(p.y, p.z, wCos.x, wSin.x);
	return (p);
}

vec3 DSA(vec3 p, vec3 wSin, vec3 wCos)
{
	rot(p.y, p.z, wCos.x, wSin.x);
	rot(p.x, p.z, wCos.y, wSin.y);
	rot(p.x, p.y, wCos.z, wSin.z);
	return (p);
}

vec4 proj(vec3 p)
{
	p = ASD(p - view[0], view[1], view[2]);
	vec4 n;
	n.x = -p.x * projF + p.x;
	n.y = -p.y * projF + p.y;
	n.z = +p.z * projF;
	n.w = 1 + n.z;
	return n;
}

void main()
{
	uvec3 idx;
	idx.x = (VIdx) & uint((0xFF));
	idx.y = (VIdx >> 8) & uint((0xFF));
	idx.z = (VIdx >> 16) & uint((0xFF));

	vs_out.NonProj = vec3(idx) + (chunk_pos * (8));

	gl_Position = proj(vs_out.NonProj);
}
