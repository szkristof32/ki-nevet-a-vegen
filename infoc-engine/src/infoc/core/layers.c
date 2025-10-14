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
