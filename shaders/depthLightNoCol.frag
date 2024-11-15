#version 330

uniform float[7] depthFactor;
const vec3 light = normalize(vec3(2, 3, 1));



in Geom_Default
{
	vec3 Normal;
} fs_in;

out vec4 Pixel;



void main()
{
	float dep;
	dep = gl_FragCoord.z;dep = gl_FragCoord.z;
	dep = depthFactor[4] / (depthFactor[3] - dep * depthFactor[2]);
	dep = (dep - depthFactor[0]) / depthFactor[1];
	dep = 1.0 - dep;

	float l;
	l = dot(normalize(fs_in.Normal), light);
	l = max(l, 0.3);

	vec3 col;
	col = vec3(1, 1, 1);
	col = col * l * dep;

	Pixel = vec4(col, 1);
}
