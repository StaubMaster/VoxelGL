#version 330

uniform float[7] depthFactor;
const vec3 light = normalize(vec3(+1, -2, +3));
uniform sampler2D texture0;



in Geom_Tex
{
	vec3	Normal;
	vec2	Tex_pos;
} fs_in;

out vec4 Pixel;



void main()
{
	//float dep;
	//dep = gl_FragCoord.z;
	//dep = depthFactor[4] / (depthFactor[3] - dep * depthFactor[2]);
	//dep = (dep - depthFactor[0]) / depthFactor[1];
	//dep = 1.0 - dep;

	float dep0, dep1;
	dep1 = ((depthFactor[4] / (depthFactor[3] - (gl_FragCoord.z) * depthFactor[2])) - depthFactor[0]) / depthFactor[1];
	dep0 = 1.0 - dep1;

	float l;
	l = dot(normalize(fs_in.Normal), light);
	l = max(l, 0.3);
	l = 1;

	vec4 back = vec4(0.5, 0.5, 0.5, 1);

	vec4 col;
	col = texture(texture0, fs_in.Tex_pos);

	Pixel = vec4(col * l * dep0 + back * dep1);
}
