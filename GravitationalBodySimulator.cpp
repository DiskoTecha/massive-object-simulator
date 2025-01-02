// GravitationalBodySimulator.cpp //
#include "GravitationalBodySimulator.h"

namespace dw
{
    // Define pi as a global constant under dw namespace
#define M_PI 3.14159265358979323846

    GravitationalBodySimulator::GravitationalBodySimulator(MassiveObject* objects, int objectAmount, double forceMultiplier) :
        objects(objects), startingObjects(objects), objectAmount(objectAmount), forceMultiplier(forceMultiplier),
        boundsAction(BoundsAction::NO_BOUNDS), boundsMin(Vector3()), boundsMax(Vector3()) {}

    GravitationalBodySimulator::GravitationalBodySimulator()
    {
        GravitationalBodySimulator(nullptr, 0, 0);
    }

    GravitationalBodySimulator::GravitationalBodySimulator(const GravitationalBodySimulator& other)
    {
        objects = other.objects;
        startingObjects = other.objects;
        objectAmount = other.objectAmount;
        forceMultiplier = other.forceMultiplier;
        boundsAction = other.boundsAction;
        boundsMin = other.boundsMin;
        boundsMax = other.boundsMax;
    }

    void GravitationalBodySimulator::swap(GravitationalBodySimulator& gravSim)
    {
        std::swap(objects, gravSim.objects);
        std::swap(objectAmount, gravSim.objectAmount);
        std::swap(forceMultiplier, gravSim.forceMultiplier);
        std::swap(startingObjects, gravSim.startingObjects);
        std::swap(boundsAction, gravSim.boundsAction);
        std::swap(boundsMin, gravSim.boundsMin);
        std::swap(boundsMax, gravSim.boundsMax);
    }

    // Copy & Swap
    GravitationalBodySimulator& GravitationalBodySimulator::operator=(GravitationalBodySimulator rhs)
    {
        swap(rhs);
        return *this;
    }

    //std::vector<int> GravitationalBodySimulator::step(long double dt)
    //{
    //    std::vector<int> collidedIndices;

    //    // Loop through and add velocity to objects
    //    for (int i = 0; i < objectAmount; i++)
    //    {
    //        for (int j = 0; j < objectAmount; j++)
    //        {
    //            // If checking against self, continue
    //            if (objects[i].getId() == objects[j].getId())
    //            {
    //                continue;
    //            }

    //            // F1 = Gm1m2/r^2 => dv = F1dt/m1 (MATH MORE FULLY DESCRIBED IN README.md)
    //            Vector3 direction = (objects[j].getPosition() - objects[i].getPosition()).unit();
    //            long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
    //            Vector3 dv = (dw_universal_gravitational_constant * forceMultiplier * objects[j].getMass() * dt / (distance * distance)) * direction;

    //            // Add velocity to mass1
    //            objects[i].setVelocity(objects[i].getVelocity() + dv);
    //        }
    //    }

    //    // Loop through and update positions now based on object velocities
    //    for (int i = 0; i < objectAmount; i++)
    //    {
    //        Vector3 dx = objects[i].getVelocity() * dt;
    //        objects[i].setPosition(objects[i].getPosition() + dx);
    //    }

    //    // Check if they went past the bounds and handle it
    //    checkBounds();

    //    for (int i = 0; i < objectAmount; i++)
    //    {
    //        for (int j = i + 1; j < objectAmount; j++)
    //        {
    //            long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
    //            long double radius1 = std::cbrt((3 * objects[i].getVolume()) / (4 * M_PI));
    //            long double radius2 = std::cbrt((3 * objects[j].getVolume()) / (4 * M_PI));

    //            if (distance < (radius1 + radius2))
    //            {
    //                // Calculate the total mass
    //                long double totalMass = objects[i].getMass() + objects[j].getMass();

    //                // Calculate the new velocity using conservation of momentum
    //                Vector3 newVelocity = (objects[i].getVelocity() * objects[i].getMass() + objects[j].getVelocity() * objects[j].getMass()) / totalMass;

    //                // Combine the masses and volumes
    //                objects[i].setMass(totalMass);
    //                objects[i].setVolume(objects[i].getVolume() + objects[j].getVolume());

    //                // Set the new velocity for the combined object
    //                objects[i].setVelocity(newVelocity);

    //                // Remove the overlapped object
    //                for (int k = j; k < objectAmount - 1; k++)
    //                {
    //                    objects[k] = objects[k + 1];
    //                }
    //                objectAmount--;

    //                // Decrement j to recheck the current position
    //                j--;

    //                // Add the index of the object whose volume was increased
    //                collidedIndices.push_back(i);
    //            }
    //        }
    //    }

    //    return collidedIndices;
    //}



    std::pair<std::vector<int>, std::vector<int>> GravitationalBodySimulator::step(long double dt)
    {
        std::vector<int> collidedIndices;
        std::vector<int> removedIndices;

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

        for (int i = 0; i < objectAmount; i++)
        {
            for (int j = i + 1; j < objectAmount; j++)
            {
                long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
                long double radius1 = std::cbrt((3 * objects[i].getVolume()) / (4 * M_PI));
                long double radius2 = std::cbrt((3 * objects[j].getVolume()) / (4 * M_PI));

                if (distance < (radius1 + radius2))
                {
                    // Calculate the total mass
                    long double totalMass = objects[i].getMass() + objects[j].getMass();

                    // Calculate the new velocity using conservation of momentum
                    Vector3 newVelocity = (objects[i].getVelocity() * objects[i].getMass() + objects[j].getVelocity() * objects[j].getMass()) / totalMass;

                    // Combine the masses and volumes
                    objects[i].setMass(totalMass);
                    objects[i].setVolume(objects[i].getVolume() + objects[j].getVolume());

                    // Set the new velocity for the combined object
                    objects[i].setVelocity(newVelocity);

                    // Add the index of the object whose volume was increased
                    collidedIndices.push_back(i);

                    // Record the index of the removed object
                    removedIndices.push_back(j);

                    // Remove the overlapped object
                    for (int k = j; k < objectAmount - 1; k++)
                    {
                        objects[k] = objects[k + 1];
                    }
                    objectAmount--;

                    // Decrement j to recheck the current position
                    j--;
                }
            }
        }

        return std::make_pair(collidedIndices, removedIndices);
    }
//
//
//
//
//
//
//std::vector<std::pair<int, int>> GravitationalBodySimulator::step(long double dt)
//{
//    std::vector<std::pair<int, int>> collidedIndices;
//
//    // Loop through and add velocity to objects
//    for (int i = 0; i < objectAmount; i++)
//    {
//        for (int j = 0; j < objectAmount; j++)
//        {
//            // If checking against self, continue
//            if (objects[i].getId() == objects[j].getId())
//            {
//                continue;
//            }
//
//            // F1 = Gm1m2/r^2 => dv = F1dt/m1 (MATH MORE FULLY DESCRIBED IN README.md)
//            Vector3 direction = (objects[j].getPosition() - objects[i].getPosition()).unit();
//            long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
//            Vector3 dv = (dw_universal_gravitational_constant * forceMultiplier * objects[j].getMass() * dt / (distance * distance)) * direction;
//
//            // Add velocity to mass1
//            objects[i].setVelocity(objects[i].getVelocity() + dv);
//        }
//    }
//
//    // Loop through and update positions now based on object velocities
//    for (int i = 0; i < objectAmount; i++)
//    {
//        Vector3 dx = objects[i].getVelocity() * dt;
//        objects[i].setPosition(objects[i].getPosition() + dx);
//    }
//
//    // Check if they went past the bounds and handle it
//    checkBounds();
//
//    for (int i = 0; i < objectAmount; i++)
//    {
//        for (int j = i + 1; j < objectAmount; j++)
//        {
//            long double distance = (objects[j].getPosition() - objects[i].getPosition()).magnitude();
//            long double radius1 = std::cbrt((3 * objects[i].getVolume()) / (4 * M_PI));
//            long double radius2 = std::cbrt((3 * objects[j].getVolume()) / (4 * M_PI));
//
//            if (distance < (radius1 + radius2))
//            {
//                // Calculate the total mass
//                long double totalMass = objects[i].getMass() + objects[j].getMass();
//
//                // Calculate the new velocity using conservation of momentum
//                Vector3 newVelocity = (objects[i].getVelocity() * objects[i].getMass() + objects[j].getVelocity() * objects[j].getMass()) / totalMass;
//
//                // Combine the masses and volumes
//                objects[i].setMass(totalMass);
//                objects[i].setVolume(objects[i].getVolume() + objects[j].getVolume());
//
//                // Set the new velocity for the combined object
//                objects[i].setVelocity(newVelocity);
//
//                // Record the indices of the objects that have collided and will be removed
//                collidedIndices.emplace_back(i, j);
//
//                // Remove the overlapped object
//                for (int k = j; k < objectAmount - 1; k++)
//                {
//                    objects[k] = objects[k + 1];
//                }
//                objectAmount--;
//
//                // Decrement j to recheck the current position
//                j--;
//            }
//        }
//    }
//
//    return collidedIndices;
//}



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

    // Getter for the array of MassiveObject instances
    MassiveObject* GravitationalBodySimulator::getObjects() const
    {
        return objects;
    }

    int GravitationalBodySimulator::getObjectAmount() const
    {
        return objectAmount;
    }
}
