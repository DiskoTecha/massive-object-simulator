#include "Vector3.h"

namespace dw
{
	// Constructors
	Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}
	Vector3::Vector3(long double x, long double y, long double z) : x(x), y(y), z(z) {}
	Vector3::Vector3(Vector3& otherVector) : x(otherVector.x), y(otherVector.y), z(otherVector.z) {}
	Vector3::Vector3(Vector3&& rhs) noexcept
	{
		x = std::move(rhs.x);
		y = std::move(rhs.y);
		z = std::move(rhs.z);

		rhs.reset();
	}

	// Destructor (no extra functionality needed as of now)
	Vector3::~Vector3() {}

	// Reinitializes the fields
	void Vector3::reset()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	// Swaps pointers between values (or values between pointers..?)
	void Vector3::swap(Vector3& v)
	{
		std::swap(x, v.x);
		std::swap(y, v.y);
		std::swap(z, v.z);
	}

	// Copy & Swap
	Vector3& Vector3::operator = (Vector3 rhs)
	{
		swap(rhs);
		return *this;
	}

	// C string getter
	const char* Vector3::c_str()
	{
		char buffer[100];
		snprintf(buffer, sizeof(buffer), "<%f, %f, %f>", x, y, z);

		return buffer;
	}

	// Class version getter
	const char* Vector3::version()
	{
		return DW_VECTOR_3_VERSION;
	}

	// Vector3 on Vector3 operators
	Vector3 Vector3::operator + (const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 Vector3::operator - (const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 Vector3::operator * (const Vector3& rhs) const
	{
		return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Vector3 Vector3::operator / (const Vector3& rhs) const
	{
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	// Double on Vector3 operators
	Vector3 Vector3::operator + (const long double& rhs) const
	{
		return Vector3(x + rhs, y + rhs, z + rhs);
	}

	Vector3 Vector3::operator - (const long double& rhs) const
	{
		return Vector3(x - rhs, y - rhs, z - rhs);
	}

	Vector3 Vector3::operator * (const long double& rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	Vector3 Vector3::operator / (const long double& rhs) const
	{
		return Vector3(x / rhs, y / rhs, z / rhs);
	}

	// Vector operations
	double Vector3::dot(const Vector3& rhs) const
	{
		Vector3 multiplied = *this * rhs;
		return multiplied.x + multiplied.y + multiplied.z;
	}

	Vector3 Vector3::cross(const Vector3& rhs) const
	{
		return Vector3((this->y * rhs.z) - (this->z * rhs.y),
			(this->z * rhs.x) - (this->x * rhs.z),
			(this->x * rhs.y) - (this->y * rhs.x));
	}
}

// Left bit shift overload for use with std::cout
std::ostream& operator << (std::ostream& os, const dw::Vector3& rhs)
{
	os << "<" << rhs.x << ", " << rhs.y << ", " << rhs.z << ">";
	return os;
}
