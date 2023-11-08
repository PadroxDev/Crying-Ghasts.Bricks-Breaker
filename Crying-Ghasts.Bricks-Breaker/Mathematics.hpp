#pragma once

namespace Mathematics {
	float Clamp(float x, float min, float max);

	bool Collision_AABB_AABB(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, sf::Vector2f sizeB);

	bool Collision_AABB_Circle(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, float radius);

	float Magnitude(sf::Vector2f u);

	void Normalize(sf::Vector2f* u);

	float VectorDistance(sf::Vector2f A, sf::Vector2f B);

	float Dot(sf::Vector2f A, sf::Vector2f B);


}
