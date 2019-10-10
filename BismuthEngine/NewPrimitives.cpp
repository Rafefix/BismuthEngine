#include "NewPrimitives.h"



Primitives::Primitives(){
	//mesh = par_shapes_create_parametric_sphere(24, 12);
}


Primitives::~Primitives(){

	glDeleteBuffers(1, &vertex_id);
	glDeleteBuffers(1, &normal_id);
}

void Primitives::Draw(){

	glPushMatrix();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normal_id);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	
	
	glDrawArrays(GL_TRIANGLES, 0, triangle_vec.size() / 3);

	glPopMatrix();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
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

void Primitives::createcube(vec3 &position, vec3 &size) {

	mesh = par_shapes_create_cube();
	par_shapes_compute_normals(mesh);
	bufferfigure(position,size);
	
}

void Primitives::bufferfigure(vec3 &position, vec3 &size) {
	
	par_shapes_scale(mesh, size.x, size.y, size.z);
	par_shapes_translate(mesh, position.x, position.y, position.z);

	ChangeList(mesh);
	par_shapes_free_mesh(mesh);

	glGenBuffers(1, &vertex_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);

	glBufferData(GL_ARRAY_BUFFER, triangle_vec.size() * sizeof(GL_FLOAT), &triangle_vec[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, normal_id);
	glBufferData(GL_ARRAY_BUFFER, normal_vec.size() * sizeof(GL_FLOAT), &normal_vec[0], GL_STATIC_DRAW);
}