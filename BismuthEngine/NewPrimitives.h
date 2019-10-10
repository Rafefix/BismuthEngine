#ifndef __NEWPRIMITIVES__H__
#define __NEWPRIMITIVES__H__

#include "Globals.h"

#include "glmath.h"
#include "glew/include/GL/glew.h"
#include <vector>
#include "par_shapes.h"




class Primitives
{
public:
	Primitives::Primitives();
	~Primitives();

	void bufferfigure(vec3 &position, vec3 &size);
	void createcube(vec3 &position, vec3 &size);

private:
	void ChangeList(par_shapes_mesh * mesh);

public:
	void Draw();

	par_shapes_mesh* mesh = nullptr;

	std::vector<float> triangle_vec;
	std::vector<float> normal_vec;

	GLuint vertex_id;
	GLuint normal_id;

};
#endif __NEWPRIMITIVES__H__