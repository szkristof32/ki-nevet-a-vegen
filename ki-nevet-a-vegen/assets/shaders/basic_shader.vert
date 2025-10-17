#version 450 core

layout (location = 0) in vec3 in_position;

layout (location = 0) out vec2 pass_position;

layout (binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
} matrices;

void main()
{
	pass_position = in_position.xy + 0.5;

	gl_Position = matrices.projection * matrices.view * vec4(in_position, 1.0);
}