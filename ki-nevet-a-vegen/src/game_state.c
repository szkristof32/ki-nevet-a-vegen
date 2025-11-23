#include "game_state.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"
#include "infoc/core/darray.h"

#include "infoc/renderer/sdl_renderer.h"
#include "infoc/renderer/ui_renderer.h"

#include "infoc/utils/file_utils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum game_state_enum
{
	game_state_normal,
	game_state_move_picking,
	game_state_moving,
	game_state_game_over
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
	float time;
	bool roll_button_hovered;
	bool enable_ui_input;
	game_state_enum state;
	piece_animation_t* animations; // darray
	move_t* moves; // darray
} game_state_internal_t;

static void _game_state_serialise_game_data(game_state_t* game_state);

void game_state_create(scene_t* scene, game_state_t* out_game_state, const game_configuration_t* configuration)
{
	memset(out_game_state, 0, sizeof(game_state_t));

	out_game_state->configuration = configuration;
	out_game_state->winner = -1;

	board_create(scene, &out_game_state->board);

	arena_allocator_t* allocator = engine_get_allocator();
	out_game_state->internal_state = arena_allocator_allocate(allocator, sizeof(game_state_internal_t));

	game_state_internal_t* internal_state = (game_state_internal_t*)out_game_state->internal_state;
	internal_state->moves = darray_create(move_t);
	internal_state->animations = darray_create(piece_animation_t);
}

void game_state_destroy(game_state_t* game_state)
{
	_game_state_serialise_game_data(game_state);

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	darray_destroy(internal_state->animations);
	darray_destroy(internal_state->moves);

	board_destroy(&game_state->board);
}

static void _game_state_normal(game_state_t* game_state);
static void _game_state_move_picking(game_state_t* game_state);
static void _game_state_moving(game_state_t* game_state);
static void _game_state_game_over(game_state_t* game_state);

void game_state_update(game_state_t* game_state, uint32_t hovered_object, float delta, bool enable_ui_input)
{
	game_state->hovered_object = hovered_object;
	game_state->delta = delta;

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;
	internal_state->time += delta;
	internal_state->enable_ui_input = enable_ui_input;

	game_state_enum state = internal_state->state;
	switch (state)
	{
		case game_state_normal: _game_state_normal(game_state); break;
		case game_state_move_picking: _game_state_move_picking(game_state); break;
		case game_state_moving: _game_state_moving(game_state); break;
		case game_state_game_over: _game_state_game_over(game_state); break;
	}

	if (state != internal_state->state)
		internal_state->time = 0;
}

static const char* _get_player_name(player_enum index)
{
	switch (index)
	{
		case player_red:	return "red";
		case player_blue:	return "blue";
		case player_green:	return "green";
		case player_yellow:	return "yellow";
	}

	return "???";
}

const float text_padding = 10.0f;
const float text_height = 10.0f;

extern float ui_padding;

bool game_state_render_ui(game_state_t* game_state, SDL_Renderer* renderer)
{
	char player_to_go[22] = { 0 };
	sprintf_s(player_to_go, sizeof(player_to_go), "Next player: %s", _get_player_name(game_state->player_to_go));

	sdl_renderer_draw_text(player_to_go, text_padding, text_padding, false);

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (internal_state->state == game_state_move_picking)
	{
		char choose[35] = { 0 };
		sprintf_s(choose, sizeof(choose), "You rolled: %d. Choose a piece!", game_state->rolled);
		sdl_renderer_draw_text(choose, text_padding, 2.0f * (text_padding + text_height), false);
	}

	if (internal_state->state == game_state_game_over)
	{
		char winner[17] = { 0 };
		sprintf_s(winner, sizeof(winner), "Winner: %s", _get_player_name(game_state->winner));
		sdl_renderer_draw_text(winner, 100, 100, false);
	}

	item_info roll_button = ui_draw_button("Roll", 100.0f, 100.0f,
		item_placement_end, item_placement_end, ui_padding, ui_padding,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	internal_state->roll_button_hovered = roll_button.hovered;

	return roll_button.hovered;
}

vec3 _animation_get_position(float t, vec3 start, vec3 end);

void game_state_play_move(game_state_t* game_state, const move_t* move, bool animate)
{
	board_move_t board_move = board_make_move(&game_state->board, move->object, move->player, move->move_count);

	game_state->rolled = 0;
	game_state->player_to_go = (game_state->player_to_go + 1) % 4;

	game_object_index_t object_index = game_state->board.piece_objects[move->object - 1];

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;
	darray_push(internal_state->moves, *move);

	if (animate)
	{
		piece_animation_t animation = { 0 };
		animation.object = object_index;
		animation.positions = board_move.positions;
		animation.get_position = _animation_get_position;
		darray_push(internal_state->animations, animation);

		for (uint32_t i = 0; i < darray_count(board_move.captured_pieces); i++)
		{
			captured_piece_t* capture = &board_move.captured_pieces[i];
			game_object_index_t captured_object_index = capture->object_index;

			piece_animation_t animation = { 0 };
			animation.object = capture->object_index;
			animation.positions = darray_create(vec3);
			animation.get_position = _animation_get_position;
			for (uint32_t i = 0; i < capture->step; i++)
				darray_push(animation.positions, scene_get_object(game_state->board.scene, captured_object_index)->transform.position);
			darray_push(animation.positions, board_get_piece_start_position(&game_state->board, captured_object_index));

			darray_push(internal_state->animations, animation);
		}
	}
	else
	{
		scene_get_object(game_state->board.scene, object_index)->transform.position = board_move.positions[darray_count(board_move.positions) - 1];
		darray_destroy(board_move.positions);

		for (uint32_t i = 0; i < darray_count(board_move.captured_pieces); i++)
		{
			captured_piece_t* capture = &board_move.captured_pieces[i];
			game_object_index_t captured_object_index = capture->object_index;

			scene_get_object(game_state->board.scene, captured_object_index)->transform.position = board_get_piece_start_position(&game_state->board, captured_object_index);
		}
	}
	darray_destroy(board_move.captured_pieces);

	player_enum winner = -1;
	for (uint32_t i = 0; i < 4; i++)
	{
		uint32_t pieces_in_house = 0;

		for (uint32_t j = 0; j < 4; j++)
		{
			if (game_state->board.pieces_in_house[i][j].object_index != 0)
				pieces_in_house++;
			else
				break;
		}

		if (pieces_in_house == 4)
		{
			winner = (player_enum)i;
			break;
		}
	}

	if (winner != -1)
		game_state->winner = winner;
}

void game_state_save(game_state_t* game_state)
{
	_game_state_serialise_game_data(game_state);
}

void _game_state_normal(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	player_type current_player_type = game_state->configuration->players[game_state->player_to_go];

	if (current_player_type == player_human)
	{
		if (internal_state->roll_button_hovered && internal_state->enable_ui_input && input_is_mouse_button_released(mouse_button_left))
		{
			game_state->rolled = dice_roll(&game_state->configuration->dice);
			internal_state->state = game_state_move_picking;
		}
	}
	else
	{
		if (internal_state->time >= 1.0f)
		{
			game_state->rolled = dice_roll(&game_state->configuration->dice);
			internal_state->state = game_state_move_picking;
		}
	}
}

void _game_state_move_picking(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	player_type current_player_type = game_state->configuration->players[game_state->player_to_go];

	uint32_t picked_piece = -1;

	if (current_player_type == player_human)
	{
		if (game_state->hovered_object != 0 && internal_state->enable_ui_input && input_is_mouse_button_released(mouse_button_left))
		{
			if (game_state->hovered_object - 1 >= (uint32_t)game_state->player_to_go * 4 &&
				game_state->hovered_object - 1 < ((uint32_t)game_state->player_to_go + 1) * 4 &&
				!board_is_piece_in_house(&game_state->board, game_state->hovered_object))
			{
				picked_piece = game_state->hovered_object;
			}
		}
	}
	else
	{
		if (internal_state->time >= 1.0f)
		{
			picked_piece = (rand() % 4) + (uint32_t)game_state->player_to_go * 4 + 1;
		}
	}

	if (picked_piece == -1)
		return;

	move_t move = { 0 };
	move.player = game_state->player_to_go;
	move.move_count = game_state->rolled;
	move.object = picked_piece;

	game_state_play_move(game_state, &move, true);

	internal_state->state = game_state_moving;
}

const float animation_duration = 0.2f;
const float wait_time = 0.4f;

static bool _game_state_animate(piece_animation_t* animation, scene_t* scene, float delta);

void _game_state_moving(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	uint32_t finished_count = 0;
	int32_t animation_count = (int32_t)darray_count(internal_state->animations);

	for (int32_t i = 0; i < animation_count; i++)
	{
		bool finished = _game_state_animate(&internal_state->animations[i], game_state->board.scene, game_state->delta);
		if (finished)
			finished_count++;
	}

	if (finished_count == animation_count)
	{
		for (int32_t i = animation_count - 1; i >= 0; i--)
		{
			darray_destroy(internal_state->animations[i].positions);
			darray_erase(internal_state->animations, i);
		}

		if (game_state->winner == -1)
			internal_state->state = game_state_normal;
		else
			internal_state->state = game_state_game_over;
	}
}

bool _game_state_animate(piece_animation_t* animation, scene_t* scene, float delta)
{
	if (animation->current_time >= 1.0f + wait_time && animation->position_index + 2 >= darray_count(animation->positions))
		return true;

	vec3 prev_position = animation->positions[animation->position_index];
	vec3 next_position = animation->positions[animation->position_index + 1];
	vec3 position = animation->get_position(animation->current_time, prev_position, next_position);
	if (vec3_eq(prev_position, next_position))
	{
		position = next_position;
	}
	scene_get_object(scene, animation->object)->transform.position = position;

	animation->current_time += delta / animation_duration;

	if (animation->current_time >= 1.0f + wait_time)
	{
		if (animation->position_index + 2 >= darray_count(animation->positions))
			return true;

		animation->current_time = 0.0f;
		animation->position_index++;
	}

	return false;
}

void _game_state_game_over(game_state_t* game_state)
{
	_game_state_serialise_game_data(game_state);
}

vec3 _animation_get_position(float t, vec3 start, vec3 end)
{
	if (t > 1.0f)
		return end;

	const float bounce_height = 3.0f;

	float distance = vec3_length(vec3_sub(end, start));
	(void)distance;

	float x = start.x + (end.x - start.x) * t;
	float z = start.z + (end.z - start.z) * t;
	float y = -4 * bounce_height * (t * (t - 1.0f)) / (powf(-1.0f, 2.0f));

	return vec3_create(x, y, z);
}

static char _player_type_to_char(player_type type)
{
	switch (type)
	{
		case player_computer:	return 'c';
		case player_human:		return 'h';
	}

	return '?';
}

void _game_state_serialise_game_data(game_state_t* game_state)
{
	file_utils_create_directory("saves");
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	size_t length = strlen(game_state->configuration->game_name) + 11;
	char* save_path = (char*)malloc(length * sizeof(char));
	sprintf_s(save_path, length, "saves/%s.dat", game_state->configuration->game_name);

	FILE* file = fopen(save_path, "wb");
	if (file == NULL)
	{
		char msg[64] = "";
		sprintf_s(msg, sizeof(msg), "Failed to open file (%s)", save_path);
		perror(msg);
		free(save_path);
		return;
	}
	free(save_path);

	fprintf(file, "nev: %s\n", game_state->configuration->game_name);
	fprintf(file, "kocka: %dd%d\n", game_state->configuration->dice.dice_count, game_state->configuration->dice.sides);
	fprintf(file, "jatekosok: %c,%c,%c,%c\n",
		_player_type_to_char(game_state->configuration->players[0]),
		_player_type_to_char(game_state->configuration->players[1]),
		_player_type_to_char(game_state->configuration->players[2]),
		_player_type_to_char(game_state->configuration->players[3]));
	fprintf(file, "---\n");

	for (uint32_t i = 0; i < darray_count(internal_state->moves); i++)
	{
		move_t* move = &internal_state->moves[i];
		fprintf(file, "%d: %d %d\n", move->player, move->move_count, move->object);
	}

	fclose(file);
}
