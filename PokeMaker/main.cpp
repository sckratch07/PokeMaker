#include "Tools.h"
#include "Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({1280, 960}), "PokeMaker");
	if (!ImGui::SFML::Init(window))
		return -1;

	sf::Clock deltaClock;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::SetNextWindowPos({ 0.f, 0.f });
		ImGui::SetNextWindowSize(ImVec2((float)window.getSize().x, (float)window.getSize().y));
		if (ImGui::Begin("PokeMaker", nullptr,
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::BeginTabBar("principal"))
			{
				if (ImGui::BeginTabItem("Scene", nullptr))
				{
					updateMap();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Script", nullptr))
				{
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Assets", nullptr))
				{
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}

		window.clear();

		ImGui::SFML::Render(window);
		renderMap(window);

		window.display();
	}

	ImGui::SFML::Shutdown(window);
}