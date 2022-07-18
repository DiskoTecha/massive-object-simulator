#Massive Body Simulator
Simulating the movement of massive bodies due to their gravitational forces
---
##Main Parts
###The Massive Body Class
A simple class to store and log the position, velocity, mass, and volume of an object.
As of 17 Jul 2022, all bodies will be assumed as perfect spheres and their volume fields will dictate collisions with other bodies.
Position and velocity is stored as Vector3's, which just stores 3-dimensional direction data and has vector dot and cross product helper functions.

###The Gravitational Body Simulator Class
*NOT IN GITHUB REPO YET*
The class that does the work of calculating multi-body movement due to the combined gravitational forces creating an overall field.

###DW Unit Test Class
Custom unit testing class.
Very low specialization, simply recording the results of multiple boolean values making it especially reusable for other projects.
