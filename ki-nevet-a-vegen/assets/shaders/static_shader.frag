#version 450 core

in VertexData
{
	vec2 Uv;
	vec3 Normal;
	vec4 Colour;
} Input;

layout (location = 0) out vec4 out_colour;

layout (binding = 0) uniform sampler2D model_texture;

void main()
{
	vec4 colour = texture(model_texture, Input.Uv);
	out_colour = Input.Colour * colour;
}
