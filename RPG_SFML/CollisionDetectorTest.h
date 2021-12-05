#pragma once

#include "IntersectionDetector.h"
#include <assert.h>

namespace jrpg
{
	namespace test
	{
		void pointOnLineShouldReturnTrue()
		{
			Line line = { {0,0}, {0,10} };
			sf::Vector2f point = { 0,5 };

			assert(IntersectionDetector2D::pointOnLine(point, line));
		}
	}
}