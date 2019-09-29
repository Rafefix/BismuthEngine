#include "glew/include/GL/glew.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleGui.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "GuiConfig.h"
#include "GuiAbout.h"
#include "WindowOrder.h"
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
	windoworder = new WindowOrder();
	config = new GuiConfig();
	about = new GuiAbout();

	AddGuiElement(windoworder);
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
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit", "Alt+F4")) {
				ret = UPDATE_STOP;
			}
				

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Style Editor")) {
				show_style_editor = true;
			}
				

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Configuration")) {
				show_config = true;
			}
			
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
				
			if (ImGui::MenuItem("About")) {}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	

	if (show_style_editor) {
		StyleEditor();
	}
		
	if (show_config) {
		//CHECK LATER
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


void ModuleGui::StyleEditor(ImGuiStyle* ref)
{
	ImGui::Begin("Style Editor", &show_style_editor);
	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
	ImGuiStyle& style = ImGui::GetStyle();
	static ImGuiStyle ref_saved_style;

	// Default to using internal storage as reference
	static bool init = true;
	if (init && ref == NULL)
		ref_saved_style = style;
	init = false;
	if (ref == NULL)
		ref = &ref_saved_style;

	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

	bool window_border = (style.WindowBorderSize > 0.0f);
	bool child_border = (style.ChildBorderSize > 0.0f);
	bool frame_border = (style.FrameBorderSize > 0.0f);
	bool popup_border = (style.PopupBorderSize > 0.0f);
	bool tab_border = (style.TabBorderSize > 0.0f);


	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Sizes"))
		{
			ImGui::Text("Borders");
			if (ImGui::Checkbox("WindowBorder", &window_border))
				style.WindowBorderSize = window_border ? 1.0f : 0.0f;
			if (ImGui::Checkbox("ChildBorderSize", &child_border))
				style.ChildBorderSize = child_border ? 1.0f : 0.0f;
			if (ImGui::Checkbox("PopupBorder", &popup_border))
				style.PopupBorderSize = popup_border ? 1.0f : 0.0f;
			if (ImGui::Checkbox("FrameBorder", &frame_border))
				style.FrameBorderSize = frame_border ? 1.0f : 0.0f;
			if (ImGui::Checkbox("TabBorderSize", &tab_border))
				style.TabBorderSize = tab_border ? 1.0f : 0.0f;
			ImGui::Text("Rounding");
			ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
			ImGui::Text("Alignment");
			ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
			ImGui::Combo("WindowMenuButtonPosition", (int*)&style.WindowMenuButtonPosition, "Left\0Right\0");
			ImGui::Combo("ColorButtonPosition", (int*)&style.ColorButtonPosition, "Left\0Right\0");
			ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
			ImGui::SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
			ImGui::Text("Safe Area Padding"); ImGui::SameLine(); HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
			ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Colors"))
		{
			static int output_dest = 0;
			static bool output_only_modified = true;
			if (ImGui::Button("Export Unsaved"))
			{
				if (output_dest == 0)
					ImGui::LogToClipboard();
				else
					ImGui::LogToTTY();
				ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;" IM_NEWLINE);
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const ImVec4& col = style.Colors[i];
					const char* name = ImGui::GetStyleColorName(i);
					if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
						ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
				}
				ImGui::LogFinish();
			}
			ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
			ImGui::SameLine(); ImGui::Checkbox("Only Modified Colors", &output_only_modified);

			static ImGuiTextFilter filter;
			filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

			static ImGuiColorEditFlags alpha_flags = 0;
			ImGui::RadioButton("Opaque", &alpha_flags, 0); ImGui::SameLine();
			ImGui::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine();
			ImGui::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); ImGui::SameLine();
			HelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");

			ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
			ImGui::PushItemWidth(-160);
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const char* name = ImGui::GetStyleColorName(i);
				if (!filter.PassFilter(name))
					continue;
				ImGui::PushID(i);
				ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
				if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
				{
					// Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
					// Read the FAQ and misc/fonts/README.txt about using icon fonts. It's really easy and super convenient!
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) ref->Colors[i] = style.Colors[i];
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) style.Colors[i] = ref->Colors[i];
				}
				ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
				ImGui::TextUnformatted(name);
				ImGui::PopID();
			}
			ImGui::PopItemWidth();
			ImGui::EndChild();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Rendering"))
		{
			ImGui::Checkbox("Anti-aliased lines", &style.AntiAliasedLines); ImGui::SameLine(); HelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
			ImGui::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, "%.2f", 2.0f);
			if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;
			ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
			ImGui::PopItemWidth();

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
	ImGui::PopItemWidth();

	ImGui::End();
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