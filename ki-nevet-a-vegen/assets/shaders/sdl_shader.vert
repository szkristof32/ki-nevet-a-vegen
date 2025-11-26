#version 450 core

out vec2 pass_uv;

const vec2 positions[6] = vec2[](
	vec2(-1.0, 1.0),
	vec2(-1.0, -1.0),
	vec2(1.0, 1.0),
	vec2(1.0, 1.0),
	vec2(-1.0, -1.0),
	vec2(1.0, -1.0)
);

void main()
{
	pass_uv = positions[gl_VertexID] * 0.5 + 0.5;
	pass_uv.y = 1.0 - pass_uv.y;
	gl_Position = vec4(positions[gl_VertexID], 1.0, 1.0);
}
