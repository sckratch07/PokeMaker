#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"
#include "SFML/Graphics.hpp"

// ---- sf::Vector2f with ImVec2 ---- //

inline sf::Vector2f operator+(sf::Vector2f left, ImVec2 right) {
	return sf::Vector2f(left.x + right.x, left.y + right.y);
}

inline sf::Vector2f operator-(sf::Vector2f left, ImVec2 right) {
	return sf::Vector2f(left.x + right.x, left.y + right.y);
}

inline sf::Vector2f operator+=(sf::Vector2f& left, ImVec2 right) {
	left.x += right.x;
	left.y += right.y;
	return left;
}

inline sf::Vector2f operator-=(sf::Vector2f& left, ImVec2 right) {
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

// ---- ImVec2 with sf::Vector2f ---- //

inline ImVec2 operator+(ImVec2 left, sf::Vector2f right) {
	return ImVec2(left.x + right.x, left.y + right.y);
}

inline ImVec2 operator-(ImVec2 left, sf::Vector2f right) {
	return ImVec2(left.x + right.x, left.y + right.y);
}

inline ImVec2 operator+=(ImVec2& left, sf::Vector2f right) {
	left.x += right.x;
	left.y += right.y;
	return left;
}

inline ImVec2 operator-=(ImVec2& left, sf::Vector2f right) {
	left.x -= right.x;
	left.y -= right.y;
	return left;
}
