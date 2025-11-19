#include "game_layer.h"
#include "menu_layer.h"

#include "game.h"

#include "infoc/core/engine.h"
#include "infoc/core/darray.h"

#include "infoc/utils/file_utils.h"

static int game_main(int argc, char** argv)
{
	bool success = engine_initialise();
	check_error(!success, "Failed to initialise engine!");

	layer_t game_layer = game_layer_create();
	layer_t menu_layer = menu_layer_create(&game_layer);
	engine_attach_layer(&menu_layer);

	engine_run();

	engine_shutdown();

	return 0;
}

#if _WIN32 && IC_RELEASE

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	return game_main(__argc, __argv);
}

#else
	
int main(int argc, char** argv)
{
	return game_main(argc, argv);
}

#endif

void game_load_save(const char* path, game_save_t* out_save)
{
	memset(out_save, 0, sizeof(game_save_t));

	if (!file_utils_file_exists(path))
		return;

	char* save_game = file_utils_read_file(path);

	char* next_token = NULL;
	char* line = strtok_s(save_game, "\n", &next_token);

	size_t line_length = strlen(line);
	out_save->configuration.game_name = (char*)malloc(line_length * sizeof(char));
	sscanf_s(line, "nev: %s", out_save->configuration.game_name, (uint32_t)line_length);

	line = strtok_s(NULL, "\n", &next_token);
	sscanf_s(line, "kocka: %dd%d", &out_save->configuration.dice.dice_count, &out_save->configuration.dice.sides);

	line = strtok_s(NULL, "\n", &next_token);
	char players[4] = { 0 };
	sscanf_s(line, "jatekosok: %c,%c,%c,%c", &players[0], 1, &players[1], 1, &players[2], 1, &players[3], 1);
	for (uint32_t i = 0; i < 4; i++)
		out_save->configuration.players[i] = players[i] == 'h' ? player_human : player_computer;

	line = strtok_s(NULL, "\n", &next_token);
	line = strtok_s(NULL, "\n", &next_token);

	out_save->moves = darray_create(move_t);

	while (line)
	{
		move_t move = { 0 };
		sscanf_s(line, "%d: %d %d", (uint32_t*)&move.player, &move.move_count, &move.object);
		darray_push(out_save->moves, move);
		line = strtok_s(NULL, "\n", &next_token);
	}

	free(save_game);
}
