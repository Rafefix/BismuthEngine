#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "glew/include/GL/glew.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(json file);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void DepthTestEnable(bool enable);
	void ColorMaterialEnable(bool enable);
	void CullFaceEnable(bool enable);
	void LightingEnable(bool enable);
	void Texture2DEnable(bool enable);
	void WireframeEnable(bool enable);


public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};