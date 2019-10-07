#include "glew/include/GL/glew.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleGui.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "GuiConfig.h"
#include "GuiAbout.h"
#include "WindowBase.h"
#include <stdio.h>



#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "glew/include/GL/glew.h"

#include "ModuleRenderer3D.h"



ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled){
}

// Destructor
ModuleGui::~ModuleGui()
{}

// Called before render is available
bool ModuleGui::Init()
{
	LOG("Loading GUI atlas");
	windowbase = new WindowBase(true);
	config = new GuiConfig(false);
	about = new GuiAbout(false);

	AddGuiElement(windowbase);
	AddGuiElement(config);
	AddGuiElement(about);

	return true;
}

// Called before the first frame
bool ModuleGui::Start()
{
	for (class std::list<GuiElement*>::iterator item = gui_elements.begin(); item != gui_elements.end(); ++item)
	{
		(*item)->Start();
	}
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	(void)io;

	//TEST
	io = &ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	return true;
}

// Update all guis
update_status ModuleGui::PreUpdate(float dt)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

// Called every frame
update_status ModuleGui::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	for (class std::list<GuiElement*>::iterator item = gui_elements.begin(); item != gui_elements.end(); ++item)
	{
		(*item)->Draw();
	}

	ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 0.50f);

	// Main Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File")){
			
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				ret = UPDATE_STOP;
			}

			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				ret = UPDATE_STOP;
			}

			if (ImGui::MenuItem("Quit", "Alt+F4")) {
				ret = UPDATE_STOP;
			}
				

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")){

			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Copy", "Ctrl+C")) {
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Paste", "Ctrl+V")) {
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Cut", "Ctrl+X")) {
				ret = UPDATE_STOP;
			}

			
				

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window")){
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")){
			
			if (ImGui::MenuItem("Show Demo")) {
				show_demo_window = true;
			}
			
			if (ImGui::MenuItem("Documentation")) {
				ShellExecuteA(NULL, "open", "https://github.com/Rafefix/BismuthEngine", NULL, NULL, SW_SHOWNORMAL);
			}
				
			if (ImGui::MenuItem("Download latest")){
				ShellExecuteA(NULL, "open", "https://github.com/Rafefix/BismuthEngine/releases", NULL, NULL, SW_SHOWNORMAL);
			}
				
			if (ImGui::MenuItem("Report a bug")){
				ShellExecuteA(NULL, "open", "https://github.com/Rafefix/BismuthEngine/issues", NULL, NULL, SW_SHOWNORMAL);
			}
				
			ImGui::MenuItem("About", NULL, &about->visible);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Configuration")) {
			
			config->visible = !config->visible;
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	
	
	if (show_config) {
		config->visible = true;
		
	}

	ImGuiIO& test_io = *io;
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glViewport(0, 0, (int)test_io.DisplaySize.x, (int)test_io.DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

	return ret;
}

void ModuleGui::AddGuiElement(GuiElement* element)
{
	gui_elements.push_back(element);
}


void ModuleGui::HelpMarker(const char * desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


// Called before quitting
bool ModuleGui::CleanUp()
{
	for (class std::list<GuiElement*>::iterator item = gui_elements.begin(); item != gui_elements.end(); ++item)
	{
		(*item)->CleanUp();
		delete (*item);
	}

	gui_elements.clear();

	return true;
}

