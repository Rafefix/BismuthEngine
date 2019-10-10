#pragma once
#include "Module.h"

#include "Globals.h"
#include "NewPrimitives.h"
#include <vector>



#define MAX_SNAKE 8

struct PhysBody3D;
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
	Primitives* shape;

public:
	void createSquare();
	void createSquareElements();
	void createfloor();
	

};

