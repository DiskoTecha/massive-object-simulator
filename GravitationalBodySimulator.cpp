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

		// Check if they went past the bounds and handle it
		checkBounds();

		return objects;
	}

	void GravitationalBodySimulator::setBounds(BoundsAction boundsAction, Vector3 boundsMin, Vector3 boundsMax)
	{
		this->boundsAction = boundsAction;
		this->boundsMin = boundsMin;
		this->boundsMax = boundsMax;
	}

	void GravitationalBodySimulator::checkBounds()
	{
		// Loop through each object and check the bounds
		for (int i = 0; i < objectAmount; i++)
		{
			short int oobDir = 0;

			// Check bounds by dimensions individually
			if (objects[i].getPosition().x > boundsMax.x) oobDir = 1;
			else if (objects[i].getPosition().x < boundsMin.x) oobDir = -1;

			if (objects[i].getPosition().y > boundsMax.y) oobDir = 2;
			else if (objects[i].getPosition().y < boundsMin.y) oobDir = -2;

			if (objects[i].getPosition().z > boundsMax.z) oobDir = 3;
			else if (objects[i].getPosition().z < boundsMin.z) oobDir = -3;

			// If out of bounds
			if (oobDir != 0)
			{
				switch (boundsAction)
				{
				case BOUNCE:
					// Flip the velocity of the bounds dimension it hit
					switch (oobDir)
					{
					case -1:
					case 1:
						objects[i].setVelocity(Vector3(-objects[i].getVelocity().x, objects[i].getVelocity().y, objects[i].getVelocity().z));
						break;
					case -2:
					case 2:
						objects[i].setVelocity(Vector3(objects[i].getVelocity().x, -objects[i].getVelocity().y, objects[i].getVelocity().z));
						break;
					case -3:
					case 3:
						objects[i].setVelocity(Vector3(objects[i].getVelocity().x, objects[i].getVelocity().y, -objects[i].getVelocity().z));
						break;
					default:
						break;
					}
					break;
				case STOP:
					// Zero the velocity
					objects[i].setVelocity(Vector3(0, 0, 0));
					break;
				case SLIDE:
					// Zero the velocity of the bounds dimension it hit
					switch (oobDir)
					{
					case -1:
					case 1:
						objects[i].setVelocity(Vector3(0, objects[i].getVelocity().y, objects[i].getVelocity().z));
						break;
					case -2:
					case 2:
						objects[i].setVelocity(Vector3(objects[i].getVelocity().x, 0, objects[i].getVelocity().z));
						break;
					case -3:
					case 3:
						objects[i].setVelocity(Vector3(objects[i].getVelocity().x, objects[i].getVelocity().y, 0));
						break;
					default:
						break;
					}
					break;
				case FLIP:
					// Flip the position to the min or max bound of the dimension it hit
					switch (oobDir)
					{
					case -1:
						objects[i].setPosition(Vector3(boundsMax.x, objects[i].getPosition().y, objects[i].getPosition().z));
						break;
					case 1:
						objects[i].setPosition(Vector3(boundsMin.x, objects[i].getPosition().y, objects[i].getPosition().z));
						break;
					case -2:
						objects[i].setPosition(Vector3(objects[i].getPosition().x, boundsMax.y, objects[i].getPosition().z));
						break;
					case 2:
						objects[i].setPosition(Vector3(objects[i].getPosition().x, boundsMin.y, objects[i].getPosition().z));
						break;
					case -3:
						objects[i].setPosition(Vector3(objects[i].getPosition().x, objects[i].getPosition().y, boundsMax.z));
						break;
					case 3:
						objects[i].setPosition(Vector3(objects[i].getPosition().x, objects[i].getPosition().y, boundsMin.z));
						break;
					default:
						break;
					}
					break;
				default:
					// No action taken for NO_BOUNDS or default
					break;
				}
			}
		}
	}
}