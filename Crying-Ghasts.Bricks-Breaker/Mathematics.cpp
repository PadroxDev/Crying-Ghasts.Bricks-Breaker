#include <SFML/Graphics.hpp>
#include "Mathematics.hpp"

namespace Mathematics {
	bool Collision_AABB_AABB(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, sf::Vector2f sizeB) {
		return ((posB.x >= posA.x + sizeA.x)
			|| (posB.x + sizeB.x <= posA.x)
			|| (posB.y >= posA.y + sizeB.y)
			|| (posB.y + sizeB.y <= posA.y));
	}

	float Magnitude(sf::Vector2f u) {
		return std::sqrt(std::pow(u.x, 2) + std::pow(u.y, 2));
	}

	void Normalize(sf::Vector2f* u) {
		float mag = Magnitude(*u);
		if (mag == 0) return;
		*u /= mag;
	}

	float Clamp(float x, float min, float max) {
		float tmp = x < min ? min : x;
		return x > max ? max : x;
	}
}