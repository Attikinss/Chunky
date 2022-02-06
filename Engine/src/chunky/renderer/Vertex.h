#pragma once
#include "math/vector/Vector2f.h"
#include "math/vector/Vector3f.h"

namespace Chunky
{
	struct Vertex
	{
		Vector3f Position;
		Vector3f Normal;
		Vector2f UV;

		Vertex InvertZ()
		{
			Vertex result = *this;
			result.Position.z *= -1.0f;
			return result;
		}
	};
}