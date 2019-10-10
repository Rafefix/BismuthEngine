#include "NewPrimitives.h"



Primitives::Primitives(SHAPE shape,vec3& position, vec3& size){

	switch (shape){

	case SHAPE::CUBE:
		mesh = par_shapes_create_cube();
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::SPHERE:
		mesh = par_shapes_create_parametric_sphere(24, 12);
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::OCTOHEDRON:
		mesh = par_shapes_create_octahedron();
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::DODECAHEDRON:
		mesh = par_shapes_create_dodecahedron();
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::ICOSAHEDRON:
		mesh = par_shapes_create_icosahedron();
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::TETRAHEDRON:
		mesh = par_shapes_create_tetrahedron();
		par_shapes_compute_normals(mesh);
		break;
	
	case SHAPE::PLANE:
		mesh = par_shapes_create_plane(3, 3);
		par_shapes_rotate(mesh, -M_PI_2, rotation);
		break;

	}

	par_shapes_scale(mesh, size.x, size.y, size.z);
	par_shapes_translate(mesh, position.x, position.y, position.z);

	ChangeList(mesh);
	par_shapes_free_mesh(mesh);

	Bufferer();
	

}

Primitives::Primitives(SHAPE shape, vec3& position, vec3& size, float radius, float slices, float stacks) {

	switch (shape) {

	/*case SHAPE::TORUS:
		mesh = par_shapes_create_torus(slices, stacks, radius);
		par_shapes_rotate(mesh, -M_PI_2, rotation);*/

	case SHAPE::CONE:
		
		mesh = par_shapes_create_cone(slices, stacks);
		disk1 = par_shapes_create_disk(radius, slices, center2, normal);
		par_shapes_rotate(disk1, -M_PI, rotation);
		par_shapes_merge(mesh, disk1);
		par_shapes_free_mesh(disk1);
		par_shapes_rotate(mesh, -M_PI_2, rotation);
		break;

	case SHAPE::CYLINDER:
	
		mesh = par_shapes_create_cylinder(slices, stacks);
		disk2 = par_shapes_create_disk(radius, slices, center, normal);
		par_shapes_merge(mesh, disk2);
		par_shapes_free_mesh(disk2);
		disk1 = par_shapes_create_disk(radius, slices, center2, normal);
		par_shapes_rotate(disk1, M_PI, rotation);
		par_shapes_merge(mesh, disk1);
		par_shapes_free_mesh(disk1);
		par_shapes_rotate(mesh, M_PI_2, rotation);
		break;
	}

	par_shapes_scale(mesh, size.x, size.y, size.z);
	par_shapes_translate(mesh, position.x, position.y, position.z);

	ChangeList(mesh);
	par_shapes_free_mesh(mesh);

	Bufferer();
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

void Primitives::Bufferer() {

	glGenBuffers(1, &vertex_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);

	glBufferData(GL_ARRAY_BUFFER, triangle_vec.size() * sizeof(GL_FLOAT), &triangle_vec[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, normal_id);
	glBufferData(GL_ARRAY_BUFFER, normal_vec.size() * sizeof(GL_FLOAT), &normal_vec[0], GL_STATIC_DRAW);
}