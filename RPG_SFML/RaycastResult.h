#pragma once
#include "VectorFunctions.h"

namespace jrpg
{

	class RaycastResult
	{
	private:
		sf::Vector2f point, normal;
		float t;
		bool hit;

	public:
		RaycastResult() : point{}, normal{}, t{ -1.f }, hit{ false }{}

	public:
		void init(const sf::Vector2f& point, const sf::Vector2f& normal, float t, bool hit) {
			this->point = point;
			this->normal = normal;
			this->t = t;
			this->hit = hit;
		}

		static void reset(RaycastResult* result) {
			if (result != nullptr) {
				result->point = { 0,0 };
				result->normal = { 0,0 };
				result->t = -1.f;
				result->hit = false;
			}
		}
	};

}