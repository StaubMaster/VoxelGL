#version 330

uniform vec3[3] viewTrans;
uniform float[7] depthFactor;
uniform vec2 aspectRatio;



layout(location = 0) in vec3 VMin;
layout(location = 1) in vec3 VMax;

out Box_Vert
{
	vec3[8]	Absolut;
	vec4[8]	Project;
}	vs_out;



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
	p_out.x = p_inn.x * aspectRatio.x;
	p_out.y = p_inn.y * aspectRatio.y;
	p_out.z = p_inn.z * depthFactor[5] - depthFactor[6];
	p_out.w = p_inn.z;
	return p_out;
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
