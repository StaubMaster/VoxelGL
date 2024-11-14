#version 330

uniform float[7] depthFactor;
const vec3 light = vec3(+0.267261, -0.534522, +0.801784);
uniform sampler2D texture0;


in Geom_Tex
{
	vec3	Normal;
	uint	Tex_idx;
	vec2	Tex_pos;
} fs_in;

out vec4 Pixel;



void main()
{
	float dep;
	dep = gl_FragDepth;
	dep = depthFactor[4] / (depthFactor[3] - dep * depthFactor[2]);
	dep = (dep - depthFactor[0]) / depthFactor[1];
	dep = 1.0 - dep;

	float l;
	l = dot(normalize(fs_in.Normal), light);
	l = max(l, 0.3);

	vec4 col;
	col = texture(texture0, fs_in.Tex_pos);

	Pixel = vec4(col * l * dep);
}
