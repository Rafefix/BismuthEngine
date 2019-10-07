#pragma once
#include "Module.h"

#include "Globals.h"
#include "Primitive.h"

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
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];




public:
	void createSquare();
	void createSquareElements();

	

};

