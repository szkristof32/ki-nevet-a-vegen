#pragma once

#include "infoc/core/defines.h"
#include "infoc/core/window.h"

typedef struct context_t
{
	void* internal_state;
} context_t;

bool context_create(const window_t* window, context_t* out_context);
void context_destroy(context_t* context);

void context_swap(const context_t* context);
