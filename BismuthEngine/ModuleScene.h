#pragma once
#include "Module.h"

#include "Globals.h"
#include "NewPrimitives.h"
#include <vector>

#include "glew/include/GL/glew.h"

#include <gl/GL.h>
#include <gl/GLU.h>


#define MAX_SNAKE 8


class Primitives;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void directcube();
	



public:
	void createSquare();
	void createSquareElements();
	void createfloor();
	Primitives* createShape(SHAPE type, vec3 &position, vec3 &size);
public:
	std::list<Primitives*> objectList;

};

