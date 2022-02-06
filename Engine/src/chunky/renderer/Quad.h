#pragma once
#include "Vertex.h"
#include <vector>

namespace Chunky
{
	struct Quad
	{
	private:
		const static Quad Top;
		const static Quad Bottom;
		const static Quad Left;
		const static Quad Right;
		const static Quad Front;
		const static Quad Back;

	public:
		Vertex Vertices[4];

	public:
		Quad() = default;
		Quad(Vector3f pos0, Vector3f pos1, Vector3f pos2, Vector3f pos3);

		void CalculateUVs();
		void CalculateNormals();
		std::vector<Vertex> ToVertexData(bool zInvert = false);
		static Quad TopFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
		static Quad BottomFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
		static Quad LeftFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
		static Quad RightFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
		static Quad FrontFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
		static Quad BackFace(const Vector3f& offset = { 0.0f, 0.0f, 0.0f });
	};
}