#include "Tools.h"
#include "Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({1280, 960}), "PokeMaker");
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));

	if (!ImGui::SFML::Init(window))
		return -1;

	ImGuiStyle& guiStyle = ImGui::GetStyle();
	guiStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.18f, 0.22f, 1.f);
	guiStyle.Colors[ImGuiCol_Tab] = ImVec4(0.23f, 0.24f, 0.34f, 1.f);
	guiStyle.Colors[ImGuiCol_TabActive] = ImVec4(0.38f, 0.38f, 0.56f, 1.f);
	guiStyle.Colors[ImGuiCol_ChildBg] = ImVec4(0.23f, 0.23f, 0.27f, 1.f);
	guiStyle.Colors[ImGuiCol_FrameBg] = ImVec4(0.28f, 0.28f, 0.37f, 1.f);

	sf::Clock deltaClock;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>()) window.close();
			else if (const auto* mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (mouseWheel->delta > 0)
					view.zoom(0.9f);  // zoom avant
				else
					view.zoom(1.1f);  // zoom arrière
			}
				
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		if (ImGui::Begin("PokeMaker", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
		{
			updateMap(sf::Vector2u(view.getSize()));
		}
		ImGui::End();

		window.clear();

		window.setView(view);
		renderGril(window);

		window.setView(window.getDefaultView());
		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown(window);
}