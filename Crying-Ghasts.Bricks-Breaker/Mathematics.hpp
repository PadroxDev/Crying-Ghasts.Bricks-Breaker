#pragma once

#include <SFML/System/Vector2.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class GameObject;
namespace sf {
	class RenderWindow;
}

namespace Mathematics {
	const double RAD2DEG = 180 / M_PI;

	float Clamp(float x, float min, float max);

	bool Collision_AABB_AABB(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, sf::Vector2f sizeB);

	bool Collision_AABB_Circle(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, float radius);

	bool Collision_Circle_Circle(sf::Vector2f posA, float radiusA,
		sf::Vector2f posB, float radiusB);

	double Magnitude(sf::Vector2f u);

	void Normalize(sf::Vector2f* u);

	float VectorDistance(sf::Vector2f A, sf::Vector2f B);

	float Dot(sf::Vector2f A, sf::Vector2f B);

	float AngleFromDirection(sf::Vector2f u);
}
