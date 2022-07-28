#include "GravitationalBodySimulator.h"

namespace dw
{
	GravitationalBodySimulator::GravitationalBodySimulator(MassiveObject* objects, int objectAmount, double forceMultiplier) : 
		objects(objects), startingObjects(objects), objectAmount(objectAmount), forceMultiplier(forceMultiplier) {}

	MassiveObject* GravitationalBodySimulator::step(long double dt)
	{
		// Loop through and add velocity to objects
		for (int i = 0; i < objectAmount; i++)
		{
			for (int j = 0; j < objectAmount; j++)
			{
				// If checking against self, continue
				if (objects[i].getId() == objects[j].getId())
				{
					continue;
				}

				// TODO add collision check using volume amounts, and then combine objects into one new one
				
				// F1 = Gm1m2/r^2 => dv = F1dt/m1 (MATH MORE FULLY DESCRIBED IN README.md)
				Vector3 direction = (objects[j].getPosition() - objects[i].getPosition()).unit();
				long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
				Vector3 dv = (dw_universal_gravitational_constant * forceMultiplier * objects[j].getMass() * dt / (distance * distance)) * direction;
				
				// Add velocity to mass1
				objects[i].setVelocity(objects[i].getVelocity() + dv);
			}
		}

		// Loop through and update positions now based on object velocities
		for (int i = 0; i < objectAmount; i++)
		{
			Vector3 dx = objects[i].getVelocity() * dt;
			objects[i].setPosition(objects[i].getPosition() + dx);
		}

		return objects;
	}
}