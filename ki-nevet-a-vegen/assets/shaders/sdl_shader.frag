#version 450 core

in vec2 pass_uv;

layout (location = 0) out vec4 out_colour;

layout (binding = 0) uniform sampler2D sdl_texture;

void main()
{
	vec4 colour = texture(sdl_texture, pass_uv);
	if (colour.a < 0.5)
		discard;
	out_colour = colour;
}
