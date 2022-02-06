#include "Quad.h"

namespace Chunky
{
	Quad const Quad::Top	= { { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f, -0.5f } };
	Quad const Quad::Bottom = { { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f } };
	Quad const Quad::Left	= { { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f } };
	Quad const Quad::Right	= { {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, {  0.5f, -0.5f,  0.5f } };
	Quad const Quad::Front	= { { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f } };
	Quad const Quad::Back	= { {  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f } };

	Quad::Quad(Vector3f pos0, Vector3f pos1, Vector3f pos2, Vector3f pos3)
	{
		Vertices[0].Position = pos0;
		Vertices[1].Position = pos1;
		Vertices[2].Position = pos2;
		Vertices[3].Position = pos3;
		CalculateNormals();
		CalculateUVs();
	}

	void Quad::CalculateUVs()
	{
		// TODO: Calculate UVs based on vertex positions
		Vertices[0].UV = { 0.0f, 0.0f };
		Vertices[1].UV = { 0.0f, 1.0f };
		Vertices[2].UV = { 1.0f, 1.0f };
		Vertices[3].UV = { 1.0f, 0.0f };
	}

	void Quad::CalculateNormals()
	{
		Vector3f normal = Vector3f::Cross((Vertices[1].Position - Vertices[0].Position), (Vertices[2].Position - Vertices[0].Position));

		Vertices[0].Normal = normal;
		Vertices[1].Normal = normal;
		Vertices[2].Normal = normal;
		Vertices[3].Normal = normal;
	}

	std::vector<Vertex> Quad::ToVertexData(bool zInvert)
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

	Quad Quad::TopFace(const Vector3f& offset)
	{
		Quad top = Top;
		top.Vertices[0].Position += offset;
		top.Vertices[1].Position += offset;
		top.Vertices[2].Position += offset;
		top.Vertices[3].Position += offset;
		return top;
	}

	Quad Quad::BottomFace(const Vector3f& offset)
	{
		Quad bottom = Bottom;
		bottom.Vertices[0].Position += offset;
		bottom.Vertices[1].Position += offset;
		bottom.Vertices[2].Position += offset;
		bottom.Vertices[3].Position += offset;
		return bottom;
	}

	Quad Quad::LeftFace(const Vector3f& offset)
	{
		Quad left = Left;
		left.Vertices[0].Position += offset;
		left.Vertices[1].Position += offset;
		left.Vertices[2].Position += offset;
		left.Vertices[3].Position += offset;
		return left;
	}

	Quad Quad::RightFace(const Vector3f& offset)
	{
		Quad right = Right;
		right.Vertices[0].Position += offset;
		right.Vertices[1].Position += offset;
		right.Vertices[2].Position += offset;
		right.Vertices[3].Position += offset;
		return right;
	}

	Quad Quad::FrontFace(const Vector3f& offset)
	{
		Quad front = Front;
		front.Vertices[0].Position += offset;
		front.Vertices[1].Position += offset;
		front.Vertices[2].Position += offset;
		front.Vertices[3].Position += offset;
		return front;
	}

	Quad Quad::BackFace(const Vector3f& offset)
	{
		Quad back = Back;
		back.Vertices[0].Position += offset;
		back.Vertices[1].Position += offset;
		back.Vertices[2].Position += offset;
		back.Vertices[3].Position += offset;
		return back;
	}
}