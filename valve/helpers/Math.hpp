#pragma once
#include "valve/auto.hpp"

constexpr auto g_pi_radians = static_cast<float>(3.14159265358979323846);
constexpr auto g_pi_degrees = static_cast<float>(180.0);

namespace math
{
	float ToDegrees(const float radians);
	float ToRadians(const float degrees);

	float AngleNormalize(float angle);

	void VectorTransform(const Vector& input, const matrix3x4_t& transform, Vector& output);

	void VectorAngles(const Vector& forward, QAngle& angles);
	void VectorAngles(const Vector& forward, const Vector& pseudoup, QAngle& angles);

	void AngleVectors(const QAngle& angles, Vector* forward);
	void AngleVectors(const QAngle& angles, Vector* forward, Vector* right, Vector* up);
	void AngleVectorsTranspose(const QAngle& angles, Vector* forward, Vector* right, Vector* up);
}