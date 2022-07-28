#ifndef DW_GRAVITATIONAL_BODY_SIMULATOR
#define DW_GRAVITATIONAL_BODY_SIMULATOR

#define DW_GRAVITATION_BODY_SIMULATOR_VERSION "1.0.1"

#include "MassiveObject.h"
#include "Vector3.h"

constexpr double dw_universal_gravitational_constant = 6.6743e-11;

namespace dw
{
	class GravitationalBodySimulator
	{
		MassiveObject* objects;
		MassiveObject* startingObjects;
		double forceMultiplier;
		int objectAmount;
	public:
		GravitationalBodySimulator(MassiveObject*, int, double);
		MassiveObject* step(long double);
	};
}

#endif