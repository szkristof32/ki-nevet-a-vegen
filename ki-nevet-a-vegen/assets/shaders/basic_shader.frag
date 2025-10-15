#version 450 core

layout (location = 0) in vec2 pass_position;

layout (location = 0) out vec4 out_colour;

void main()
{
	out_colour = vec4(pass_position, 0.0, 1.0);
}