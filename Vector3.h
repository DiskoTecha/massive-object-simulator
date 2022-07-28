#ifndef DW_VECTOR_3
#define DW_VECTOR_3

// Version number macro
#define DW_VECTOR_3_VERSION "1.0.2"

#include <memory>
#include <cstdio>
#include <iostream>

namespace dw
{
	class Vector3
	{
	public:
		long double x = 0.0;
		long double y = 0.0;
		long double z = 0.0;

		Vector3();
		Vector3(long double x, long double y = 0, long double z = 0);
		Vector3(Vector3&);
		Vector3(Vector3&&) noexcept;
		~Vector3();

		Vector3& operator = (Vector3);
		Vector3 operator + (const Vector3&) const;
		Vector3 operator - (const Vector3&) const;
		Vector3 operator * (const Vector3&) const;		
		Vector3 operator / (const Vector3&) const;

		Vector3 operator += (long double) const;
		Vector3 operator -= (long double) const;
		Vector3 operator *= (long double) const;
		Vector3 operator /= (long double) const;

		void reset();
		void swap(Vector3&);
		const char* c_str();
		const char* version();

		long double dot(const Vector3&) const;
		Vector3 cross(const Vector3&) const;
		long double magnitude();
		Vector3 unit();
	};

	Vector3 operator + (Vector3, const long double&);
	Vector3 operator - (Vector3, const long double&);
	Vector3 operator * (Vector3, const long double&);
	Vector3 operator / (Vector3, const long double&);

	Vector3 operator + (const long double&, Vector3);
	Vector3 operator - (const long double&, Vector3);
	Vector3 operator * (const long double&, Vector3);
	Vector3 operator / (const long double&, Vector3);

}


// Left bit shift overload for use with std::cout
std::ostream& operator << (std::ostream& os, const dw::Vector3& rhs);


#endif