#include "infoc/core/engine.h"

int main(int argc, char** argv)
{
	bool success = engine_initialise();
	if (!success)
	{
		fprintf(stderr, "Failed to initialise engine!\n");
		return -1;
	}

	engine_run();

	engine_shutdown();
}
