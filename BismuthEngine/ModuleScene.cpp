#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "NewPrimitives.h"
#include "ModuleRenderer3D.h"
#include "math.h"



GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				   -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

					1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
					1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

					1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				   -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				   -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				   -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
					1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

					1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				   -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

GLfloat normals1[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
					0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

					1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
					1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

					0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
					0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

				   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
				   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

					0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
					0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

					0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
					0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
					1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
					1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
				   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
				   -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
					1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

// normal array
GLfloat normals2[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
						1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
						0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
					   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
						0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
						0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)


GLfloat colors1[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
						1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

						1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
						0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

						1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
						0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

						1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
						0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

						0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
						1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

						0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
						0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4
// color array
GLfloat colors2[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
						1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
						1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
						1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
						0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
						0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
					   4, 5, 6,   6, 7, 4,      // right
					   8, 9,10,  10,11, 8,      // top
					  12,13,14,  14,15,12,      // left
					  16,17,18,  18,19,16,      // bottom
					  20,21,22,  22,23,20 };    // back



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
	createfloor();
	//directcube();
	createSquare();
	createSquareElements();
	/*
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	*/
	//creatingshapes();

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

void ModuleScene::createSquare()
{

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals1);
	glColorPointer(3, GL_FLOAT, 0, colors1);
	glVertexPointer(3, GL_FLOAT, 0, vertices1);

	glPushMatrix();
	glTranslatef(2, 2, 0);                  // move to upper-right corner

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}


void ModuleScene::createSquareElements()
{

	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals2);
	glColorPointer(3, GL_FLOAT, 0, colors2);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void ModuleScene::createfloor()
{
	//Direct CUBE
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	for (int i = -200.f; i < 200.f; i=i+1.f) {
		
		glVertex3f(-200.f, 0.f, i);
		glVertex3f(200.f, 0.f, i);
	}

	for (int i = -200.f; i < 200.f; i = i + 1.f) {

		glVertex3f(i, 0.f, -200.f);
		glVertex3f(i, 0.f, 200.f);
	}


	


	glEnd();

}