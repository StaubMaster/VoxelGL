#version 330

uniform vec3[3] view;
const float projF = 2.0;

layout(location = 0) in vec3 VMin;
layout(location = 1) in vec3 VMax;

out Box_Vert
{
	vec3[8]	Absolut;
	vec4[8]	Project;
}	vs_out;



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
	vs_out.Absolut[0] = vec3(VMin.x, VMin.y, VMin.z);
	vs_out.Absolut[1] = vec3(VMax.x, VMin.y, VMin.z);
	vs_out.Absolut[2] = vec3(VMax.x, VMax.y, VMin.z);
	vs_out.Absolut[3] = vec3(VMin.x, VMax.y, VMin.z);
	vs_out.Absolut[4] = vec3(VMin.x, VMin.y, VMax.z);
	vs_out.Absolut[5] = vec3(VMax.x, VMin.y, VMax.z);
	vs_out.Absolut[6] = vec3(VMax.x, VMax.y, VMax.z);
	vs_out.Absolut[7] = vec3(VMin.x, VMax.y, VMax.z);

	vs_out.Project[0] = proj(vs_out.Absolut[0]);
	vs_out.Project[1] = proj(vs_out.Absolut[1]);
	vs_out.Project[2] = proj(vs_out.Absolut[2]);
	vs_out.Project[3] = proj(vs_out.Absolut[3]);
	vs_out.Project[4] = proj(vs_out.Absolut[4]);
	vs_out.Project[5] = proj(vs_out.Absolut[5]);
	vs_out.Project[6] = proj(vs_out.Absolut[6]);
	vs_out.Project[7] = proj(vs_out.Absolut[7]);

	gl_Position = vec4(0, 0, 0, 1);
}
