#include "infoc/core/engine.h"

static void on_attach();

int main(int argc, char** argv)
{
	bool success = engine_initialise();
	if (!success)
	{
		fprintf(stderr, "Failed to initialise engine!\n");
		return -1;
	}

	layer_t layer = { 0 };
	layer.on_attach = on_attach;
	engine_attach_layer(&layer);

	engine_run();

	engine_shutdown();
}

void on_attach()
{
	printf("On attach\n");
}
