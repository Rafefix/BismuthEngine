#include "NewPrimitives.h"

Primitives::Primitives(vec3 position, vec3 size)
{
}


Primitives::~Primitives()
{
	
}

void Primitives::Draw()
{
	
}

void Primitives::ChangeList(par_shapes_mesh * mesh){

	for (int i = 0; i < mesh->ntriangles * 3; ++i){

		PAR_SHAPES_T indices = mesh->triangles[i];
		float* vertices = mesh->points + indices * 3;
		float* normals = mesh->normals + indices * 3;

		for (int j = 0; j < 3; ++j){

			triangle_vec.push_back(*vertices++);
			normal_vec.push_back(*normals++);
		}
	}
}