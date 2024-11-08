#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vert_Out
{
	vec3 NonProj;
} gs_in[];

out Geom_Out
{
	vec3 Normal;
} gs_out;


vec3 calcNormal(vec3 a, vec3 b, vec3 c)
{
	vec3 e1, e2;
	e1 = a - c;
	e2 = b - c;

	vec3 n;
	n.x = e1.y * e2.z - e1.z * e2.y;
	n.y = e1.z * e2.x - e1.x * e2.z;
	n.z = e1.x * e2.y - e1.y * e2.x;
	return (normalize(n));
}

void calcCorner(int i)
{
	gl_Position = gl_in[i].gl_Position;
	EmitVertex();
}

void main()
{
	gs_out.Normal = calcNormal(gs_in[0].NonProj, gs_in[1].NonProj, gs_in[2].NonProj);
	//gl_Position = vec4(+0.5, +0.5, 0.5, 1);
	//EmitVertex();
	//gl_Position = vec4(+0.5, -0.5, 0.5, 1);
	//EmitVertex();
	//gl_Position = vec4(-0.5, -0.5, 0.5, 1);
	//EmitVertex();
	calcCorner(0);
	calcCorner(1);
	calcCorner(2);
	EndPrimitive();
}
