#include "Application.hpp"
#include "tinyfiledialogs.h"

void Application::run()
{
	this->window = sf::RenderWindow(sf::VideoMode({ 1280, 960 }), "PokeMaker");
	this->window.setFramerateLimit(120);

	if (ImGui::SFML::Init(this->window))
	{
		ImGuiStyle& guiStyle = ImGui::GetStyle();
		guiStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.18f, 0.22f, 1.f);
		guiStyle.Colors[ImGuiCol_Tab] = ImVec4(0.23f, 0.24f, 0.34f, 1.f);
		guiStyle.Colors[ImGuiCol_TabActive] = ImVec4(0.38f, 0.38f, 0.56f, 1.f);
		guiStyle.Colors[ImGuiCol_ChildBg] = ImVec4(0.23f, 0.23f, 0.27f, 1.f);
		guiStyle.Colors[ImGuiCol_FrameBg] = ImVec4(0.28f, 0.28f, 0.37f, 1.f);
	}

	this->update();
}

void Application::handleEvents()
{
	while (const std::optional event = this->window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(this->window, *event);
		if (event->is<sf::Event::Closed>()) this->window.close();
	}
}

void Application::update()
{
	bool windowOpen = this->window.isOpen();
	const char* filters[] = { "*.pokeProject" };

	while (window.isOpen())
	{
		windowOpen = this->window.isOpen();
		this->handleEvents();

		sf::Time time = this->deltaClock.restart();
		ImGui::SFML::Update(this->window, time);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project"))
				{
					const char* path = tinyfd_saveFileDialog("Create Project", "../projects/project.pokeProject", 1, filters, "PokeMaker Project (*.pokeProject)");
					if (path)
						if (this->projectManager.getCurrentProject().projectName != "null")
						{
							this->projectManager.saveProject();
							this->projectManager.createProject(std::filesystem::path(path).stem().string(), path);
						}
						else
							this->projectManager.createProject(std::filesystem::path(path).stem().string(), path);
				}
				if (ImGui::MenuItem("Open Project"))
				{
					const char* path = tinyfd_openFileDialog("Create Project", "../projects/", 1, filters, "PokeMaker Project (*.pokeProject)", 0);
					if (path)
						if (this->projectManager.getCurrentProject().projectName != "null")
						{
							this->projectManager.saveProject();
							this->projectManager.loadProject(path);
						}
						else
						{
							this->projectManager.loadProject(path);
						}
				}
						ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		this->editorUI.drawProjectPanel();
		this->editorUI.drawTileMapEditor();
		this->editorUI.drawEntityEditor();

		this->window.clear(sf::Color(58, 68, 69));

		this->render();

		this->window.display();
	}

	ImGui::SFML::Shutdown(this->window);
}

void Application::render()
{
	ImGui::SFML::Render(this->window);
}