#ifndef __NEWPRIMITIVES__H__
#define __NEWPRIMITIVES__H__

#include "Globals.h"

#include "glmath.h"
#include "glew/include/GL/glew.h"
#include <vector>
#include "par_shapes.h"


enum class SHAPE
{
	CUBE,
	OCTOHEDRON,
	DODECAHEDRON,
	ICOSAHEDRON,
	TETRAHEDRON,
	PLANE,
	SPHERE,
	TORUS,
	CONE,
	CYLINDER
};


class Primitives
{
public:
	Primitives::Primitives(SHAPE shape,vec3 &position, vec3 &size);
	Primitives::Primitives(SHAPE shape, vec3 &position, vec3 &size, float radius, float slices, float stacks);
	~Primitives();

private:
	void ChangeList(par_shapes_mesh * mesh);
	void Bufferer();
public:
	void Draw();

	par_shapes_mesh* mesh = nullptr;
	par_shapes_mesh* disk1 = nullptr;
	par_shapes_mesh* disk2 = nullptr;

	std::vector<float> triangle_vec;
	std::vector<float> normal_vec;

	GLuint vertex_id;
	GLuint normal_id;
	float radius;
	int slices;
	int stacks;
	float rotation[3] = { 1, 0, 0 };
	float center[3] = { 0, 0, 1 };
	float normal[3] = { 0, 0, 1 };
	float center2[3] = { 0, 0, 0 };
	
};
#endif __NEWPRIMITIVES__H__