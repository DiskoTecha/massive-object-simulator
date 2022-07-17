#ifndef DW_MASSIVE_OBJECT
#define DW_MASSIVE_OBJECT

#define DW_MASSIVE_OBJECT_VERSION "1.0.1"

#include "MassiveObject.h"
#include "Vector3.h"

namespace dw
{
	class MassiveObject
	{
		Vector3 position;
		Vector3 velocity;
		long double mass;
		long double volume;
	public:
		MassiveObject();
		MassiveObject(long double, long double, Vector3 pos = Vector3(), Vector3 vel = Vector3());
		MassiveObject(MassiveObject&);
		MassiveObject(MassiveObject&&) noexcept;
	};
}

#endif