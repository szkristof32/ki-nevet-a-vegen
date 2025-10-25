#version 450 core

in VertexData
{
	vec2 Uv;
	vec3 Normal;
	vec4 Colour;
	float ObjectIndex;
} Input;

layout (location = 0) out vec4 out_colour;
layout (location = 1) out vec4 out_id;

layout (binding = 0) uniform sampler2D model_texture;

const vec3 light_direction = vec3(-1.0, -1.0, -0.5);

void main()
{
	vec3 light_dir_norm = normalize(light_direction);
	vec3 to_light_vector = -light_dir_norm;
	vec3 unit_normal = normalize(Input.Normal);
	float NdotL = dot(unit_normal, to_light_vector);

	vec4 colour = texture(model_texture, Input.Uv);
	out_colour = Input.Colour * colour * max(NdotL, 0.1);

	out_id = vec4(Input.ObjectIndex);
}
