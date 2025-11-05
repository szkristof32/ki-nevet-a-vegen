#include "game_state.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"
#include "infoc/core/darray.h"

#include "infoc/renderer/sdl_renderer.h"

#include <string.h>

typedef enum game_state_enum
{
	game_state_normal,
	game_state_move_picking,
	game_state_moving
} game_state_enum;

typedef struct piece_animation_t
{
	game_object_index_t object;
	vec3(*get_position)(float t, vec3 start, vec3 end);
	float current_time;
	vec3* positions; // darray
	uint32_t position_index;
} piece_animation_t;

typedef struct game_state_internal_t
{
	game_state_enum state;
	piece_animation_t animation;
} game_state_internal_t;

void game_state_create(scene_t* scene, game_state_t* out_game_state)
{
	memset(out_game_state, 0, sizeof(game_state_t));

	out_game_state->dice.dice_count = 1;
	out_game_state->dice.sides = 6;

	board_create(scene, &out_game_state->board);

	arena_allocator_t* allocator = engine_get_allocator();
	out_game_state->internal_state = arena_allocator_allocate(allocator, sizeof(game_state_internal_t));
}

void game_state_destroy(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;
	piece_animation_t* animation = &internal_state->animation;

	if (animation && animation->positions)
		darray_destroy(animation->positions);

	board_destroy(&game_state->board);
}

static void _game_state_normal(game_state_t* game_state);
static void _game_state_move_picking(game_state_t* game_state);
static void _game_state_moving(game_state_t* game_state);

void game_state_update(game_state_t* game_state, uint32_t hovered_object, float delta)
{
	game_state->hovered_object = hovered_object;
	game_state->delta = delta;

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	switch (internal_state->state)
	{
		case game_state_normal:
		{
			_game_state_normal(game_state);
			break;
		}
		case game_state_move_picking:
		{
			_game_state_move_picking(game_state);
			break;
		}
		case game_state_moving:
		{
			_game_state_moving(game_state);
			break;
		}
	}
}

static const char* _get_player_name(player_enum index)
{
	switch (index)
	{
		case player_red:	return "piros";
		case player_green:	return "zold";
		case player_blue:	return "kek";
		case player_yellow:	return "sarga";
	}

	return "???";
}

const float text_padding = 10.0f;
const float text_height = 10.0f;

void game_state_render_ui(game_state_t* game_state, SDL_Renderer* renderer)
{
	char player_to_go[26] = { 0 };
	sprintf_s(player_to_go, sizeof(player_to_go), "Kovetkezo jatekos: %s", _get_player_name(game_state->player_to_go));

	sdl_renderer_draw_text(player_to_go, text_padding, text_padding);

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (internal_state->state == game_state_move_picking)
	{
		char choose[32] = { 0 };
		sprintf_s(choose, sizeof(choose), "Dobtal: %d. Valassz egy babut!", game_state->rolled);
		sdl_renderer_draw_text(choose, text_padding, 2.0f * (text_padding + text_height));
	}
}

void _game_state_normal(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (input_is_mouse_button_clicked(mouse_button_right))
	{
		game_state->rolled = dice_roll(&game_state->dice);
		internal_state->state = game_state_move_picking;
	}
}

vec3 _animation_get_position(float t, vec3 start, vec3 end);

void _game_state_move_picking(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (game_state->hovered_object != 0 && input_is_mouse_button_clicked(mouse_button_left))
	{
		if (game_state->hovered_object - 1 >= game_state->player_to_go * 4 &&
			game_state->hovered_object - 1 < (game_state->player_to_go + 1) * 4)
		{
			vec3* positions = board_make_move(&game_state->board, game_state->hovered_object, game_state->player_to_go, game_state->rolled);
			game_state->rolled = 0;
			game_state->player_to_go = (game_state->player_to_go + 1) % 4;

			game_object_index_t object_index = game_state->board.piece_objects[game_state->hovered_object - 1];

			piece_animation_t* animation = &internal_state->animation;
			animation->object = object_index;
			animation->positions = positions;
			animation->get_position = _animation_get_position;

			internal_state->state = game_state_moving;
		}
	}
}

const float animation_duration = 0.7f;
const float wait_time = 0.4f;

void _game_state_moving(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	piece_animation_t* animation = &internal_state->animation;

	vec3 prev_position = animation->positions[animation->position_index];
	vec3 next_position = animation->positions[animation->position_index + 1];
	vec3 position = animation->get_position(animation->current_time, prev_position, next_position);
	scene_get_object(game_state->board.scene, animation->object)->transform.position = position;

	animation->current_time += game_state->delta / animation_duration;

	if (animation->current_time >= 1.0f + wait_time)
	{
		if (animation->position_index + 2 >= darray_count(animation->positions))
		{
			darray_destroy(animation->positions);
			memset(animation, 0, sizeof(piece_animation_t));
			internal_state->state = game_state_normal;
		}
		else
		{
			animation->current_time = 0.0f;
			animation->position_index++;
		}
	}
}

vec3 _animation_get_position(float t, vec3 start, vec3 end)
{
	if (t > 1.0f)
		return end;

	const float bounce_height = 3.0f;

	float distance = vec3_length(vec3_sub(end, start));

	float x = start.x + (end.x - start.x) * t;
	float z = start.z + (end.z - start.z) * t;
	float y = -4 * bounce_height * (t * (t - 1.0f)) / (powf(-1.0f, 2.0f));

	return vec3_create(x, y, z);
}
