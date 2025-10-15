#version 450 core

layout (location = 0) in vec3 in_position;

layout (location = 0) out vec2 pass_position;

void main()
{
	pass_position = in_position.xy + 0.5;

	gl_Position = vec4(in_position, 1.0);
}