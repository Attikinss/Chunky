#pragma once
#include "Vertex.h"
#include <vector>

namespace Chunky
{
	struct Quad
	{
		const static Quad Top;
		const static Quad Bottom;
		const static Quad Left;
		const static Quad Right;
		const static Quad Front;
		const static Quad Back;

		Vertex Vertices[4];

		Quad() = default;

		Quad(Vector3f pos0, Vector3f pos1, Vector3f pos2, Vector3f pos3)
		{
			Vertices[0].Position = pos0;
			Vertices[1].Position = pos1;
			Vertices[2].Position = pos2;
			Vertices[3].Position = pos3;
			CalculateNormals();
			CalculateUVs();
		}

		void CalculateUVs()
		{
			// TODO: Calculate UVs based on vertex positions
			Vertices[0].UV = { 0.0f, 0.0f };
			Vertices[1].UV = { 0.0f, 1.0f };
			Vertices[2].UV = { 1.0f, 1.0f };
			Vertices[3].UV = { 1.0f, 0.0f };
		}

		void CalculateNormals()
		{
			Vector3f normal = Vector3f::Cross((Vertices[1].Position - Vertices[0].Position), (Vertices[2].Position - Vertices[0].Position));

			Vertices[0].Normal = normal;
			Vertices[1].Normal = normal;
			Vertices[2].Normal = normal;
			Vertices[3].Normal = normal;
		}

		std::vector<Vertex> ToVertexData(bool zInvert = false)
		{
			if (zInvert)
			{
				Vertex inverted0 = Vertices[0].InvertZ();
				Vertex inverted1 = Vertices[1].InvertZ();
				Vertex inverted2 = Vertices[2].InvertZ();
				Vertex inverted3 = Vertices[3].InvertZ();

				return std::vector<Vertex>({ inverted0, inverted1, inverted2, inverted2, inverted3, inverted0 });
			}

			return std::vector<Vertex>({ Vertices[0], Vertices[1], Vertices[2], Vertices[2], Vertices[3], Vertices[0] });
		}
	};

	Quad const Quad::Top	= { { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f, -0.5f } };
	Quad const Quad::Bottom = { { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f } };
	Quad const Quad::Left	= { { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f } };
	Quad const Quad::Right	= { {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, {  0.5f, -0.5f,  0.5f } };
	Quad const Quad::Front	= { { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f } };
	Quad const Quad::Back	= { {  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f } };
}