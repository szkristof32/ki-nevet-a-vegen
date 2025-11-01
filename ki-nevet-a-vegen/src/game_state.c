#include "game_state.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include <string.h>

typedef enum game_state_enum
{
	game_state_normal,
	game_state_move,
} game_state_enum;

typedef struct game_state_internal_t
{
	game_state_enum state;
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
	board_destroy(&game_state->board);
}

static void _game_state_normal(game_state_t* game_state);
static void _game_state_move(game_state_t* game_state);

void game_state_update(game_state_t* game_state, uint32_t hovered_object)
{
	game_state->hovered_object = hovered_object;

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	switch (internal_state->state)
	{
		case game_state_normal:
		{
			_game_state_normal(game_state);
			break;
		}
		case game_state_move:
		{
			_game_state_move(game_state);
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
	SDL_SetRenderScale(renderer, 2.0f, 2.0f);
	SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, 1.0f);

	char player_to_go[26] = { 0 };
	sprintf_s(player_to_go, sizeof(player_to_go), "Kovetkezo jatekos: %s", _get_player_name(game_state->player_to_go));

	SDL_RenderDebugText(renderer, text_padding, text_padding, player_to_go);

	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (internal_state->state == game_state_move)
	{
		char choose[32] = { 0 };
		sprintf_s(choose, sizeof(choose), "Dobtal: %d. Valassz egy babut!", game_state->rolled);
		SDL_RenderDebugText(renderer, text_padding, 2.0f * text_padding + text_height, choose);
	}

	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void _game_state_normal(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (input_is_mouse_button_clicked(mouse_button_right))
	{
		game_state->rolled = dice_roll(&game_state->dice);
		internal_state->state = game_state_move;
	}
}

void _game_state_move(game_state_t* game_state)
{
	game_state_internal_t* internal_state = (game_state_internal_t*)game_state->internal_state;

	if (game_state->hovered_object != 0 && input_is_mouse_button_clicked(mouse_button_left))
	{
		if (game_state->hovered_object - 1 >= game_state->player_to_go * 4 &&
			game_state->hovered_object - 1 < (game_state->player_to_go + 1) * 4)
		{
			board_make_move(&game_state->board, game_state->hovered_object, game_state->player_to_go, game_state->rolled);
			game_state->rolled = 0;
			game_state->player_to_go = (game_state->player_to_go + 1) % 4;

			internal_state->state = game_state_normal;
		}
	}
}
