#pragma once
#include "Module.h"

#include "Globals.h"


#define MAX_SNAKE 8

struct PhysBody3D;

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


public:
	void createSquare();
	void createSquareElements();

	

};

