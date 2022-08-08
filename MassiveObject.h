#ifndef DW_MASSIVE_OBJECT
#define DW_MASSIVE_OBJECT

// Version number macro
#define DW_MASSIVE_OBJECT_VERSION "1.0.2"

#include "MassiveObject.h"
#include "Vector3.h"
#include <memory>

namespace dw
{
	class MassiveObject
	{
		Vector3 position;
		Vector3 velocity;
		long double mass;
		long double volume;
		static int objectsInstantiated;
		int id;

	public:
		MassiveObject();
		MassiveObject(long double, long double, Vector3 pos = Vector3(), Vector3 vel = Vector3());
		MassiveObject(MassiveObject&);
		MassiveObject(MassiveObject&&) noexcept;

		int getId();
		long double getMass();
		long double getVolume();
		Vector3 getPosition();
		Vector3 getVelocity();
		
		void setMass(long double);
		void setVolume(long double);
		void setPosition(Vector3);
		void setVelocity(Vector3);

		void reset();
	};
}

#endif