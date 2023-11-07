#pragma once

namespace Mathematics {

	bool Collision_AABB_AABB(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, sf::Vector2f sizeB);

	float Magnitude(sf::Vector2f u);

	void Normalize(sf::Vector2f* u);

	float Clamp(float x, float min, float max);
}
