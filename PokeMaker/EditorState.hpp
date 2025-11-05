#pragma once
#include <SFML/Graphics.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

class EditorState
{
public:
	EditorState();
	~EditorState();

	void Update(float dt);
	void HandleEvent(const std::optional<sf::Event>& event);
	void Render(sf::RenderWindow& window);

private:
	bool showDemoWindow;
};

