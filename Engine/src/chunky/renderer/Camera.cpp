#include "Camera.h"

namespace Chunky
{
	Camera::Camera(Projection projectionType, double nearPlane, double farPlane, double fieldOfView)
		: m_ProjectionType(projectionType), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_FieldOfView(fieldOfView)
	{
		RecalculateProjection();
	}

	Camera::Camera(const Vector2f& viewSize, Projection projectionType, double nearPlane, double farPlane, double fieldOfView)
		: m_ViewSize(viewSize), m_ProjectionType(projectionType), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_FieldOfView(fieldOfView)
	{
		RecalculateProjection();
	}

	void Camera::SetFOV(double fieldOfView)
	{
		if (m_FieldOfView == fieldOfView)
			return;

		m_FieldOfView = fieldOfView;
		RecalculateProjection();
	}

	void Camera::SetProjectionType(Projection projectionType)
	{
		if (m_ProjectionType == projectionType)
			return;

		m_ProjectionType = projectionType;
		RecalculateProjection();
	}

	void Camera::SetNearPlane(double nearPlane)
	{
		if (m_NearPlane == nearPlane)
			return;

		m_NearPlane = nearPlane;
		RecalculateProjection();
	}

	void Camera::SetFarPlane(double farPlane)
	{
		if (m_FarPlane == farPlane)
			return;

		m_FarPlane = farPlane;
		RecalculateProjection();
	}

	void Camera::SetViewSize(const Vector2f& viewSize)
	{
		if (m_ViewSize == viewSize)
			return;

		m_ViewSize = viewSize;
		RecalculateProjection();
	}

	void Camera::SetView(const Matrix4f& viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateProjection()
	{
		m_ProjectionMatrix = m_ProjectionType == Projection::Orthographic ?
			Matrix4f::Orthographic(-m_ViewSize.x * 0.0025f, m_ViewSize.x * 0.0025f, -m_ViewSize.y * 0.0025f, m_ViewSize.y * 0.0025f, m_NearPlane, m_FarPlane) :
			Matrix4f::Perspective(Math::Deg2Rad * m_FieldOfView, m_ViewSize.x / m_ViewSize.y, m_NearPlane, m_FarPlane);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}