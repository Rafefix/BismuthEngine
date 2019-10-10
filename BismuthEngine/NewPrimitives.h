#ifndef __NEWPRIMITIVES__H__
#define __NEWPRIMITIVES__H__

#include "Globals.h"
#include "par_shapes.h"
#include "glmath.h"

#include "glew/include/GL/glew.h"

#include <vector>

using namespace std;

class Primitives
{
public:
	Primitives::Primitives(vec3 position, vec3 size);
	~Primitives();

private:
	void ChangeList(par_shapes_mesh * mesh);
public:
	void Draw();

	par_shapes_mesh* mesh = nullptr;

	vector<float> triangle_vec;
	vector<float> normal_vec;

	GLuint vertex_id;
	GLuint normal_id;

};
#endif __NEWPRIMITIVES__H__