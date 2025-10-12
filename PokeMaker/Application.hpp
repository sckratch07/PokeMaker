#pragma once
#include "ProjectManager.hpp"
#include "SceneManager.hpp"
#include "EditorUI.hpp"

class Application
{
public:
	void run();
	void handleEvents();
	void update();
	void render();

	inline ProjectManager& getProjectManager()
		{ return this->projectManager; }
	inline SceneManager& getSceneManager()
		{ return this->sceneManager; }
private:
	sf::RenderWindow window;
	bool isRunning = false;
	sf::Clock deltaClock;

	ProjectManager projectManager;
	SceneManager sceneManager;
	EditorUI editorUI;
};