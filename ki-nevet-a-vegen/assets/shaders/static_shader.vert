#version 450 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

out VertexData
{
	vec2 Uv;
	vec3 Normal;
	vec4 Colour;
} Output;

layout (binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
} matrices;

layout (binding = 1) uniform Object
{
	mat4 transformation;
	vec4 colour;
} object;

void main()
{
	Output.Uv = in_uv;
	Output.Normal = in_normal;
	Output.Colour = object.colour;

	gl_Position = matrices.projection * matrices.view * object.transformation * vec4(in_position, 1.0);
}
