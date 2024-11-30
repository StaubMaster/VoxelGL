#version 330

uniform vec2 aspectRatio;
uniform vec2 windowSize;

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
	vec2	min_screen = 2 * (gs_in[0].Min / windowSize) - 1;
	vec2	max_screen = 2 * (gs_in[0].Max / windowSize) - 1;

	gs_out.Min = gs_in[0].Min;
	gs_out.Max = gs_in[0].Max;
	gs_out.Color = gs_in[0].Color;

	gs_out.Pos = vec2(gs_in[0].Min.x, gs_in[0].Min.y);
	gl_Position = vec4(min_screen.x, min_screen.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Min.x, gs_in[0].Max.y);
	gl_Position = vec4(min_screen.x, max_screen.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Max.x, gs_in[0].Min.y);
	gl_Position = vec4(max_screen.x, min_screen.y, gs_in[0].Depth, 1); EmitVertex();

	gs_out.Pos = vec2(gs_in[0].Max.x, gs_in[0].Max.y);
	gl_Position = vec4(max_screen.x, max_screen.y, gs_in[0].Depth, 1); EmitVertex();
}
