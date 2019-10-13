#include "ModuleImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include  "Assimp/include/postprocess.h"
#include  "Assimp/include/cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleImporter::ModuleImporter(Application * app, bool start_enabled) : Module(app, start_enabled) {}

ModuleImporter::~ModuleImporter() {}
void MyAssimpCallback(const char * msg, char * userData)
{
	LOG("[Assimp]: %s", msg);
}

bool ModuleImporter::Init(json file) {

	struct aiLogStream stream;
	stream.callback = MyAssimpCallback;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

bool ModuleImporter::Start() { LoadFile("Assets/Baker_house.fbx"); return true; }

update_status ModuleImporter::Update(float dt) { return UPDATE_CONTINUE; }

bool ModuleImporter::CleanUp() {

	aiDetachAllLogStreams();

	glDeleteBuffers(1, (GLuint*)&VerticesID);
	glDeleteBuffers(1, (GLuint*)&IndicesID);

	RELEASE_ARRAY(Vertices);
	RELEASE_ARRAY(Indices);

	return true;
	return true;
}



void ModuleImporter::Draw() {


	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VerticesID);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesID);
	glDrawElements(GL_TRIANGLES, IndicesSize, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}

bool ModuleImporter::LoadFile(const char* path) {

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {

		for (uint i = 0; i < scene->mNumMeshes; ++i) {}

		aiMesh* mesh = scene->mMeshes[0];
		verticesSize = mesh->mNumVertices;
		Vertices = new vec3[mesh->mNumVertices];

		for (unsigned i = 0; i < mesh->mNumVertices; ++i) {

			Vertices[i] = *((vec3*)&mesh->mVertices[i]);
		}

		glGenBuffers(1, (GLuint*)&VerticesID);
		glBindBuffer(GL_ARRAY_BUFFER, VerticesID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * verticesSize, Vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		IndicesSize = mesh->mNumFaces * 3;
		Indices = new uint[IndicesSize];

		for (unsigned j = 0; j < mesh->mNumFaces; ++j) {

			const aiFace& face = mesh->mFaces[j];

			assert(face.mNumIndices == 3);

			Indices[j * 3] = face.mIndices[0];
			Indices[j * 3 + 1] = face.mIndices[1];
			Indices[j * 3 + 2] = face.mIndices[2];
		}
		glGenBuffers(1, (GLuint*)&IndicesID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * IndicesSize, Indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		aiReleaseImport(scene);


	}
	return true;
}