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
		std::cout << "DOT: " << Mathematics::Dot(posA, posB) << std::endl;
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

	sf::Vector2f GetNormalOfCollision(GameObject* obj, GameObject* collider) {
		sf::Vector2f d = collider->Position() - obj->Position();

		sf::Vector2f ux = collider->Position() + sf::Vector2f(1, 0);
		sf::Vector2f uy = collider->Position() + sf::Vector2f(0, 1);

		float ex = collider->Size().x * 0.5f;
		float ey = collider->Size().y * 0.5f;

		float dx = Dot(d, ux);
		if (dx > ex) {
			dx = ex;
			std::cout << "Apple tree" << std::endl;
		}
		if (dx < -ex) dx = -ex;

		float dy = Dot(d, uy);
		if (dy > ey) dy = ey;
		else if (dy < -ey) dy = -ey;

		sf::Vector2f p = obj->Position() + dx * ux + dy * uy;
		sf::Vector2f n = obj->Position() - p;
		Normalize(&n);

		return n;
	}

	sf::Vector2f Reflect(sf::Vector2f inNormal, sf::Vector2f inDirection) {
		return -2 * Dot(inNormal, inDirection) * inNormal + inDirection;
	}
}