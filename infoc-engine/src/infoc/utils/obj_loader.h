#pragma once

#include "infoc/renderer/mesh.h"

/*
* Loads and processes an .obj file from disk
*
* @param filepath The path of the model file
* @param out_mesh A pointer to a `mesh_t` object to be filled in
*/
void obj_loader_load_model(const char* filepath, mesh_t* out_mesh);
