#include "GuiAbout.h"
#include "Application.h"
#include "ModuleWindow.h"

GuiAbout::GuiAbout(bool is_visible) : GuiElement(is_visible) {}

GuiAbout::~GuiAbout() {}

void GuiAbout::Start()
{
}

void GuiAbout::Draw()
{
	if (!visible) {
		return;
	}
	ImGui::SetNextWindowPos(ImVec2(450, 18), ImGuiCond_Once);

	if (ImGui::Begin("About", &visible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)){

		ImGui::Text("%s ", SDL_GetWindowTitle(App->window->window));
		ImGui::Separator();

		ImGui::Text("3D Game Engine");
		ImGui::Text("By Ferran Barnes & Rafel Brau");

		if (ImGui::Button("Github")) {
			ShellExecuteA(NULL, "open", "https://github.com/Rafefix/BismuthEngine", NULL, NULL, SW_SHOWNORMAL);
		}
			

		ImGui::Text("\n3rd Party Libraries used:");
		ImGui::BulletText("SDL");
		ImGui::BulletText("Glew");
		ImGui::BulletText("ImGui");
		ImGui::BulletText("MathGeoLib");
		ImGui::BulletText("OpenGL");
		//RANDOM NUMBER GENERATOR CHECK LATER

		ImGui::Text("\nMIT License");
		ImGui::Text("Copyright (c) 2019 Ferran Barnes Garica & Rafel Brau");
		ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
		ImGui::Text("of this software and associated documentation files (the 'Software'), to deal");
		ImGui::Text("in the Software without restriction, including without limitation the rights");
		ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and / or sell");
		ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
		ImGui::Text("furnished to do so, subject to the following conditions :");

		ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all");
		ImGui::Text("copies or substantial portions of the Software.");

		ImGui::Text("\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
		ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
		ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
		ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
		ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
		ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
		ImGui::Text("SOFTWARE.");

		ImGui::End();
	}
}

void GuiAbout::CleanUp()
{
}