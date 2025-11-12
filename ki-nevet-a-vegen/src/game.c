#include "game_layer.h"
#include "menu_layer.h"

#include "infoc/core/engine.h"

int main(int argc, char** argv)
{
	bool success = engine_initialise();
	check_error(!success, "Failed to initialise engine!");

	layer_t game_layer = game_layer_create();
	layer_t menu_layer = menu_layer_create(&game_layer);
	engine_attach_layer(&menu_layer);

	engine_run();

	engine_shutdown();
}
