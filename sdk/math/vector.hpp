#pragma once

#include "shared/auto.hpp"
#include "sdk/math/vector4d.hpp"
#include <functional>

class Vector
{
public:
	Vector();
	Vector(const float vector_x, const float vector_y, const float vector_z);
	Vector(const Vector& vector);
	Vector(const float* vector);

public:
	void Init(const float vector_x = 0.f, const float vector_y = 0.f, const float vector_z = 0.f);
	void Invalidate();

	float* Base();
	float* Base() const;

	bool IsValid() const;
	bool IsZero() const;

	float Dot(const Vector& vector) const;
	float Dot2D(const Vector& vector) const;

	float LengthSqr() const;
	float Length() const;

	float Length2DSqr() const;
	float Length2D() const;

	float DistToSqr(const Vector& vector) const;
	float DistTo(const Vector& vector) const;

	float Normalize();
	void NormalizeFast();

	Vector Cross(const Vector& vector) const;

	Vector4D ToVector4() const;

public:
	float operator[](const std::size_t index) const;
	float& operator[](const std::size_t index);

public:
	Vector& operator=(const Vector& vector);

public:
	bool operator==(const Vector& vector) const;
	bool operator!=(const Vector& vector) const;

public:
	Vector& operator+=(const Vector& vector);
	Vector& operator-=(const Vector& vector);
	Vector& operator*=(const Vector& vector);
	Vector& operator/=(const Vector& vector);

public:
	Vector& operator+=(const float value);
	Vector& operator-=(const float value);
	Vector& operator*=(const float value);
	Vector& operator/=(const float value);

public:
	Vector operator+(const Vector& vector) const;
	Vector operator-(const Vector& vector) const;
	Vector operator*(const Vector& vector) const;
	Vector operator/(const Vector& vector) const;

public:
	Vector operator+(const float value) const;
	Vector operator-(const float value) const;
	Vector operator*(const float value) const;
	Vector operator/(const float value) const;

public:
	static Vector Zero;

public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

class __declspec(align(16)) VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned& operator=(const VectorAligned& vOther)
	{
		_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
		return *this;
	}
	float w;
};