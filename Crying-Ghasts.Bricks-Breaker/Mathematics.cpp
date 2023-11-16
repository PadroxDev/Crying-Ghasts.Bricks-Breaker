#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mathematics.hpp"
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

namespace Mathematics {
	bool Collision_AABB_AABB(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, sf::Vector2f sizeB) {
		return (posA.x < posB.x + sizeB.x &&
			posA.x + sizeA.x > posB.x &&
			posA.y < posB.y + sizeB.y &&
			posA.y + sizeA.y > posB.y);
	}

	bool Collision_AABB_Circle(sf::Vector2f posA, sf::Vector2f sizeA,
		sf::Vector2f posB, float radius) {
		return false;
	}

	bool Collision_Circle_Circle(sf::Vector2f posA, float radiusA,
		sf::Vector2f posB, float radiusB) {
		float d = VectorDistance(posA, posB);
		return (d <= radiusA + radiusB);
	}

	double Magnitude(sf::Vector2f u) {
		return std::sqrt(std::pow(u.x, 2) + std::pow(u.y, 2));
	}

	void Normalize(sf::Vector2f* u) {
		float mag = Magnitude(*u);
		if (mag == 0) return;
		*u /= mag;
	}

	float VectorDistance(sf::Vector2f A, sf::Vector2f B) {
		sf::Vector2f C = B - A;
		return Magnitude(C);
	}

	float Clamp(float x, float min, float max) {
		return std::max(min, std::min(max, x));
	}

	float Dot(sf::Vector2f A, sf::Vector2f B) {
		return A.x * B.x + A.y * B.y;
	}

	float AngleFromDirection(sf::Vector2f u) {
		return std::atan2(u.y, u.x);
	}
}