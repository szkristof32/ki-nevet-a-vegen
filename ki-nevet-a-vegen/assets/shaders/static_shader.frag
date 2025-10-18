#version 450 core

in VertexData
{
	vec2 Uv;
	vec3 Normal;
	vec4 Colour;
} Input;

layout (location = 0) out vec4 out_colour;

void main()
{
	out_colour = Input.Colour;
}