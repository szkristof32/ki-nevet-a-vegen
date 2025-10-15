#include "game_layer.h"

#include "infoc/core/engine.h"

int main(int argc, char** argv)
{
	bool success = engine_initialise();
	if (!success)
	{
		fprintf(stderr, "Failed to initialise engine!\n");
		return -1;
	}

	layer_t game_layer = game_layer_create();
	engine_attach_layer(&game_layer);

	engine_run();

	engine_shutdown();
}
