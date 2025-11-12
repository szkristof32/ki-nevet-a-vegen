#include "layers.h"

#include "darray.h"

bool layer_stack_create(layer_stack_t* out_layer_stack)
{
	out_layer_stack->layers = darray_create(layer_t);

	return true;
}

void layer_stack_destroy(layer_stack_t* layer_stack)
{
	darray_destroy(layer_stack->layers);
}

void layer_stack_push_layer(layer_stack_t* layer_stack, layer_t* layer)
{
	darray_push(layer_stack->layers, *layer);
}

void layer_stack_pop_layer(layer_stack_t* layer_stack, layer_t* layer)
{
	for (uint32_t i = 0; i < darray_count(layer_stack->layers); i++)
	{
		if (layer_stack->layers[i].internal_state == layer->internal_state)
		{
			darray_erase(layer_stack->layers, i);
			return;
		}
	}
}
