#pragma once
#include "math/vector/Vector2f.h"
#include "math/matrix/Matrix4f.h"

namespace Chunky
{
	enum class Projection { Orthographic, Perspective };

	class Camera
	{
	public:
		Camera(Projection projectionType = Projection::Perspective, double nearPlane = 0.3, double farPlane = 1000.0, double fieldOfView = 60.0);
		Camera(const Vector2f& viewSize, Projection projectionType = Projection::Perspective, double nearPlane = 0.3, double farPlane = 1000.0, double fieldOfView = 60.0);
		virtual ~Camera() = default;

		void SetFOV(double fieldOfView);
		void SetProjectionType(Projection projectionType);
		void SetNearPlane(double nearPlane);
		void SetFarPlane(double farPlane);
		void SetViewSize(const Vector2f& viewSize);
		void SetView(const Matrix4f& viewMatrix);

		const Matrix4f& GetView() const { return m_ViewMatrix; }
		const Matrix4f& GetProjection() const { return m_ProjectionMatrix; }
		const Matrix4f& GetViewProjection() const { return m_ViewProjectionMatrix; }

	protected:
		void RecalculateProjection();

	protected:
		Matrix4f m_ViewMatrix = Matrix4f(1.0f);
		Matrix4f m_ProjectionMatrix = Matrix4f(1.0f);
		Matrix4f m_ViewProjectionMatrix = Matrix4f(1.0f);

		Projection m_ProjectionType;
		Vector2f m_ViewSize;
		float m_NearPlane;
		float m_FarPlane;
		float m_FieldOfView;
	};
}