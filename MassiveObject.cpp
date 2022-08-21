#include "MassiveObject.h"

namespace dw
{
	// Initialize static variable
	int MassiveObject::objectsInstantiated = 0;

	// Constructors
	MassiveObject::MassiveObject() : position(Vector3()), velocity(Vector3()), mass(0.0), volume(0.0)
	{
		++objectsInstantiated;
		id = objectsInstantiated;
	}

	MassiveObject::MassiveObject(long double mass, long double volume, Vector3 pos, Vector3 vel) : position(pos), velocity(vel), mass(mass), volume(volume)
	{
		++objectsInstantiated;
		id = objectsInstantiated;
	}

	MassiveObject::MassiveObject(MassiveObject& otherObject)
	{
		mass = otherObject.mass;
		volume = otherObject.volume;
		position = otherObject.position;
		velocity = otherObject.velocity;

		++objectsInstantiated;
		id = objectsInstantiated;
	}

	MassiveObject::MassiveObject(MassiveObject&& rhs) noexcept
	{
		mass = std::move(rhs.mass);
		volume = std::move(rhs.mass);
		position = std::move(rhs.position);
		velocity = std::move(rhs.velocity);

		// Although it was moved, the rhs still exists and this is a new MassiveObject
		++objectsInstantiated;
		id = objectsInstantiated;

		rhs.reset();
	}

	void MassiveObject::swap(MassiveObject& other)
	{
		std::swap(mass, other.mass);
		std::swap(volume, other.volume);
		std::swap(position, other.position);
		std::swap(velocity, other.velocity);
	}

	MassiveObject& MassiveObject::operator = (MassiveObject rhs)
	{
		swap(rhs);

		return *this;
	}


	void MassiveObject::reset()
	{
		mass = 0.0;
		volume = 0.0;
		position = Vector3();
		velocity = Vector3();
	}

	// Getters
	int MassiveObject::getId()
	{
		return id;
	}

	long double MassiveObject::getMass()
	{
		return mass;
	}

	long double MassiveObject::getVolume()
	{
		return volume;
	}

	Vector3 MassiveObject::getPosition()
	{
		return position;
	}

	Vector3 MassiveObject::getVelocity()
	{
		return velocity;
	}

	// Setters
	void MassiveObject::setMass(long double mass)
	{
		this->mass = mass;
	}

	void MassiveObject::setVolume(long double volume)
	{
		this->volume = volume;
	}

	void MassiveObject::setPosition(Vector3 position)
	{
		this->position = position;
	}

	void MassiveObject::setVelocity(Vector3 velocity)
	{
		this->velocity = velocity;
	}
}
