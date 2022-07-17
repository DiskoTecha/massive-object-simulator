#include "MassiveObject.h"

namespace dw
{
	MassiveObject::MassiveObject() : position(Vector3()), velocity(Vector3()), mass(0.0), volume(0.0) {}
	MassiveObject::MassiveObject(long double mass, long double volume, Vector3 pos, Vector3 vel) : position(pos), velocity(vel), mass(mass), volume(volume) {}

	MassiveObject::MassiveObject(MassiveObject& otherObject)
	{
		mass = otherObject.mass;
		volume = otherObject.volume;
		position = otherObject.position;
		velocity = otherObject.velocity;
	}

	MassiveObject::MassiveObject(MassiveObject&& rhs) noexcept
	{
		mass = std::move(rhs.mass);
		volume = std::move(rhs.mass);
		position = std::move(rhs.position);
		velocity = std::move(rhs.velocity);

		rhs.reset();
	}

	void MassiveObject::reset()
	{
		mass = 0.0;
		volume = 0.0;
		position = Vector3();
		velocity = Vector3();
	}
}
