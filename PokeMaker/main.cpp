#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "PokeMaker");
	if (!ImGui::SFML::Init(window))
		return -1;

	sf::Clock deltaClock;
	float float1 = 0.f;
	float float2 = 0.f;
	float float3 = 0.f;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Test");
		ImGui::BeginTabBar("0");
		ImGui::BeginTabItem("1");
		ImGui::SliderFloat("Float", &float1, 0.f, 10.f);
		ImGui::EndTabItem();
		ImGui::BeginTabItem("2");
		ImGui::SliderFloat("Float", &float2, 0.f, 10.f);
		ImGui::EndTabItem();
		ImGui::BeginTabItem("3");
		ImGui::SliderFloat("Float", &float3, 0.f, 10.f);
		ImGui::EndTabItem();
		ImGui::EndTabBar();
		ImGui::End();

		window.clear(sf::Color(150, 150, 175, 255));

		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown(window);
}