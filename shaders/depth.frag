#version 330

uniform float[7] depthFactor;
const vec3 light = vec3(+0.267261, -0.534522, +0.801784);



in Geom_Out
{
	vec3 Normal;
} fs_in;

out vec4 Color;



void main()
{
	float dep;
	dep = gl_FragCoord.z;
	dep = depthFactor[4] / (depthFactor[3] - dep * depthFactor[2]);
	dep = (dep - depthFactor[0]) / depthFactor[1];
	dep = 1.0 - dep;

	vec3 col;
	col = vec3(dep, dep, dep);
	Color = vec4(col, 1);
}
