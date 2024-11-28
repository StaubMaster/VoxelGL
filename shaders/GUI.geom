#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;



in Vert_GUI
{
	vec2	Min;
	vec2	Max;
	vec3	Color;
	float	Depth;
} gs_in[];

out Geom_GUI
{
	vec2	Min;
	vec2	Max;
	vec2	Pos;
	vec3	Color;
} gs_out;



void main()
{
	gs_out.Min = gs_in[0].Min;
	gs_out.Max = gs_in[0].Max;
	gs_out.Color = gs_in[0].Color;

	gs_out.Pos = vec2(gs_in[0].Min.x, gs_in[0].Min.y);
	gl_Position = vec4(gs_in[0].Min.x, gs_in[0].Min.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Min.x, gs_in[0].Max.y);
	gl_Position = vec4(gs_in[0].Min.x, gs_in[0].Max.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Max.x, gs_in[0].Min.y);
	gl_Position = vec4(gs_in[0].Max.x, gs_in[0].Min.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Max.x, gs_in[0].Max.y);
	gl_Position = vec4(gs_in[0].Max.x, gs_in[0].Max.y, gs_in[0].Depth, 1); EmitVertex();
}
