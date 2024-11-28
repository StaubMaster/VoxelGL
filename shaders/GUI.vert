#version 330



layout(location = 0) in vec2 VMin;
layout(location = 1) in vec2 VMax;
layout(location = 2) in vec3 VColor;
layout(location = 3) in float VDepth;

out Vert_GUI
{
	vec2	Min;
	vec2	Max;
	vec3	Color;
	float	Depth;
} vs_out;



void main()
{
	vs_out.Min = VMin;
	vs_out.Max = VMax;
	vs_out.Color = VColor;
	vs_out.Depth = VDepth;
	gl_Position = vec4((VMin + VMax) / 2, 0, 1);
}
