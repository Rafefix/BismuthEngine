#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleRenderer3D.h"
#include "Math.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleScene::Update(float dt)
{
	
	directcube();

	/*
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	*/

	return UPDATE_CONTINUE;
}

void ModuleScene::directcube()
{
	//Direct CUBE
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 2.f, 0.f);

	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 2.f, 0.f);

	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(0.f, 2.f, 2.f);

	glVertex3f(2.f, 0.f, 2.f);
	glVertex3f(2.f, 2.f, 2.f);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);

	glVertex3f(0.f, 2.f, 0.f);
	glVertex3f(2.f, 2.f, 0.f);

	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(2.f, 0.f, 2.f);

	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(2.f, 2.f, 2.f);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 2.f);

	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 2.f);

	glVertex3f(0.f, 2.f, 0.f);
	glVertex3f(0.f, 2.f, 2.f);

	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(2.f, 2.f, 2.f);

	glEnd();

}
void ModuleScene::arraycube()
{
	

}