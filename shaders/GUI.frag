#version 330



in Geom_GUI
{
	vec2	Min;
	vec2	Max;
	vec2	Pos;
	vec3	Color;
} fs_in;

out vec4 Pixel;



void main()
{
	vec3 col = fs_in.Color;

	if (abs(fs_in.Pos.x - fs_in.Min.x) < 0.005)
		col = col * 1.25;
	else if (abs(fs_in.Pos.x - fs_in.Max.x) < 0.005)
		col = col * 1.25;
	else if (abs(fs_in.Pos.y - fs_in.Min.y) < 0.005)
		col = col * 1.25;
	else if (abs(fs_in.Pos.y - fs_in.Max.y) < 0.005)
		col = col * 1.25;

	Pixel = vec4(col, 1);
}
