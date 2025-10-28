#version 450 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

out VertexData
{
	vec2 Uv;
	vec3 Normal;
	vec4 Colour;
	float ObjectIndex;
	vec4 Highlight;
} Output;

layout (binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
	uint object_count;
} matrices;

layout (std140, binding = 1) uniform Object
{
	mat4 transformation;
	vec4 colour;
	uint index;
	vec4 highlight;
} object;

void main()
{
	Output.Uv = in_uv;
	Output.Normal = (object.transformation * vec4(in_normal, 0.0)).xyz;
	Output.Colour = object.colour;
	Output.ObjectIndex = float(object.index) / float(matrices.object_count);
	Output.Highlight = object.highlight;

	gl_Position = matrices.projection * matrices.view * object.transformation * vec4(in_position, 1.0);
}
