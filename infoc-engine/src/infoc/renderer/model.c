#include "model.h"

void model_destroy(model_t* model)
{
	mesh_destroy(&model->mesh);
	texture_destroy(&model->model_texture);
}
