#ifndef DW_GRAVITATIONAL_BODY_SIMULATOR
#define DW_GRAVITATIONAL_BODY_SIMULATOR

#define DW_GRAVITATION_BODY_SIMULATOR_VERSION "1.0.3"

#include "MassiveObject.h"
#include "Vector3.h"

constexpr double dw_universal_gravitational_constant = 6.6743e-11;

namespace dw
{
	enum BoundsAction
	{
		NO_BOUNDS,
		BOUNCE,
		STOP,
		SLIDE,
		FLIP
	};

	class GravitationalBodySimulator
	{
		MassiveObject* objects;
		MassiveObject* startingObjects;
		double forceMultiplier;
		int objectAmount;
		BoundsAction boundsAction;
		Vector3 boundsMin;
		Vector3 boundsMax;

		void checkBounds();
	public:
		GravitationalBodySimulator();
		GravitationalBodySimulator(const GravitationalBodySimulator&);
		GravitationalBodySimulator(MassiveObject*, int, double);
		MassiveObject* step(long double);
		void setBounds(BoundsAction, Vector3, Vector3);

		void swap(GravitationalBodySimulator&);
		GravitationalBodySimulator& operator = (GravitationalBodySimulator);
	};
}

#endif