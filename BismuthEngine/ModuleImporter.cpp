#include "ModuleImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include  "Assimp/include/postprocess.h"
#include  "Assimp/include/cfileio.h"

#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilut.h"
#include "DevIL/include/IL/ilu.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment( lib, "Devil/lib/x86/Release/DevIL.lib" )
#pragma comment( lib, "Devil/lib/x86/Release/ILU.lib" )
#pragma comment( lib, "Devil/lib/x86/Release/ILUT.lib" )

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled) {}
ModuleImporter::~ModuleImporter() {}

bool ModuleImporter::Init()
{
	ilInit();
	iluInit();
	ilEnable(IL_CONV_PAL);
	ilutEnable(ILUT_OPENGL_CONV);
	ilutRenderer(ILUT_OPENGL);
	ilutInit();
	glEnable(GL_TEXTURE_2D);
	return true;
}

bool ModuleImporter::Start(){
	
	texture = GetTexture("Assets/Baker_house.png");
	LoadFile("Assets/BakerHouse.fbx");
	loadedAll = true;
	
	return true;
}

update_status ModuleImporter::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleImporter::CleanUp()
{
	
	return true;
}

void ModuleImporter::LoadFile(const char* path, uint tex) {

	std::string n = path;
	std::string directory;

	size_t i;
	if (loadedAll) i = n.rfind('\\', n.length());
	else i = n.rfind('//', n.length());

	if (i != std::string::npos) {
		directory = (n.substr(i + 1, n.length() - i));
	}

	std::string name;
	const size_t last_slash_idx = directory.rfind('.');
	if (std::string::npos != last_slash_idx)
	{
		name = directory.substr(0, last_slash_idx);
	}

	GameObject Loadmesh(name);

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()){

		for (uint i = 0; i < scene->mNumMeshes; ++i) {

			MeshData* indexes = new MeshData;

			
			indexes->num_vertices = scene->mMeshes[i]->mNumVertices;
			indexes->vertices = new float[indexes->num_vertices * 3];
			memcpy(indexes->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * indexes->num_vertices * 3);

			glGenBuffers(1, (GLuint*)&indexes->id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, indexes->id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * indexes->num_vertices, indexes->vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (scene->mMeshes[i]->HasFaces()){

				indexes->num_indices = scene->mMeshes[i]->mNumFaces * 3;
				indexes->indices = new uint[indexes->num_indices];

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j){

					memcpy(&indexes->indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}

			glGenBuffers(1, (GLuint*)&indexes->id_index);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes->id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexes->num_indices, indexes->indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			if (scene->mMeshes[i]->HasTextureCoords(0)){

				indexes->num_texture = scene->mMeshes[i]->mNumVertices;
				indexes->textures = new float[scene->mMeshes[i]->mNumVertices * 2];

				for (uint j = 0; j < scene->mMeshes[i]->mNumVertices; ++j){

					indexes->textures[j * 2] = scene->mMeshes[i]->mTextureCoords[0][j].x;
					indexes->textures[(j * 2) + 1] = scene->mMeshes[i]->mTextureCoords[0][j].y;
				}

			}

			glGenBuffers(1, (GLuint*)&indexes->id_texture);
			glBindBuffer(GL_ARRAY_BUFFER, indexes->id_texture);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * indexes->num_texture, indexes->textures, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			Loadmesh.Mesh_comp->mesh.push_back(indexes);
		}

	
		if (tex == 0) { 
			Loadmesh.Tex_comp->texture = texture;
		}
		else { 
			Loadmesh.Tex_comp->texture = tex;
		}
		App->scene->objectsList.push_back(Loadmesh);

		aiReleaseImport(scene);
	}
	else LOG("Error loading FBX: %s", path);
}


uint ModuleImporter::GetTexture(const char* path){

	ilInit();
	iluInit();
	ilEnable(IL_CONV_PAL);
	ilutEnable(ILUT_OPENGL_CONV);
	ilutRenderer(ILUT_OPENGL);
	ilutInit();

	ILuint pic;
	uint aux_texture;

	ilGenImages(1, &pic);
	ilBindImage(pic);

	if (!ilLoadImage(path)) {
		ilDeleteImages(1, &pic);
		return 0;
	}
	else{

		aux_texture = ilutGLBindTexImage();

		long width;
		long height;
		long bit_depth;
		long format;

		ILubyte *texdata = 0;

		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		bit_depth = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		format = ilGetInteger(IL_IMAGE_FORMAT);
		texdata = ilGetData();

		glGenTextures(1, &aux_texture);

		glBindTexture(GL_TEXTURE_2D, aux_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, bit_depth, width, height, format, GL_UNSIGNED_BYTE, texdata);

		glBindTexture(GL_TEXTURE_2D, 0);

		ilBindImage(0);
		ilDeleteImage(pic);

		return aux_texture;
	}
}

GameObject* ModuleImporter::CreateGameObject() {
	GameObject* ret = nullptr;

	return ret;
}