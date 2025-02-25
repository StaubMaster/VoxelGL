#version 330

uniform vec3[3] view;
uniform float[7] depthFactor;



layout(location = 0) in vec3 VPos;

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

vec4 proj(vec3 p_inn)
{
	vec4 p_out;

	p_out.x = p_inn.x;
	p_out.y = p_inn.y;
	p_out.z = p_inn.z * depthFactor[5] - depthFactor[6];
	p_out.w = p_inn.z;

	return p_out;
}

void main()
{
	vs_out.NonProj = VPos;

	gl_Position = proj(ASD(vs_out.NonProj - view[0], view[1], view[2]));
}
