#include <cstdio>
#include <cstring>
#include <iostream>
#include "DWUnitTest.h"
#include "MassiveObject.h"
#include "Vector3.h"
#include "Visualizer3D.h"
#include <cstdio>

//// Global task manager
//PointerTo<AsyncTaskManager> taskManager = AsyncTaskManager::get_global_ptr();
//
//// Global clock
//PointerTo<ClockObject> globalClock = ClockObject::get_global_clock();
//
//// Camera
//NodePath camera;
//
//// Task -- a global or static function that returns the AsyncTask::DoneStatus, task object pointer passed as argument, and pointer to custom data (we pass void pointer instead)
//
//AsyncTask::DoneStatus massiveObjectMovementTask(GenericAsyncTask* task, void* data)
//{
//	// TODO handle the new positions of the massive objects
//
//	// Tells the task manager to continue this task the next frame
//	return AsyncTask::DS_cont;
//}
//
//AsyncTask::DoneStatus cameraMovementTask(GenericAsyncTask* task, void* data)
//{
//	// TODO handle the movement of the camera
//	
//	// Continue task in next frame
//	return AsyncTask::DS_cont;
//}

using namespace dw;

void runUnitTests();

int main(int argc, char** argv)
{
	// Run the unit tests
	runUnitTests();

	// Visualize
	Visualizer3D* visualizer = Visualizer3D::getInstance("Testin it out");
	visualizer->init(argc, argv);
	visualizer->run();
	visualizer->shutdown();

	return 0;
}

void runUnitTests()
{
	DWUnitTest unitTest("Vector3 Test", false);
	std::cout << "DWUnitTest Version:" << unitTest.version() << std::endl;
	std::cout << "---------------------" << std::endl;

	// ---------- Vector3 testing ---------- //
	std::cout << "Vector3 Testing" << std::endl;

	// Vector3: Constructors
	Vector3 vec3_1(3, 5, 7);
	unitTest.test("\"Default\" Constructor", vec3_1.x == 3 && vec3_1.y == 5 && vec3_1.z == 7);

	Vector3 vec3_2;
	unitTest.test("\"Default\" Constructor, Default Parameters", vec3_2.x == 0 && vec3_2.y == 0 && vec3_2.z == 0);

	Vector3 vec3_3(vec3_1);
	unitTest.test("Copy constructor", vec3_3.x == vec3_1.x && vec3_3.y == vec3_1.y && vec3_3.z == vec3_1.z);

	// Vector3: Operators
	Vector3 vec3_4(2, 4, 6);
	Vector3 vec3_5;
	vec3_5 = vec3_4;

	unitTest.test("\"=\" Operator (Copy & Swap)", vec3_5.x == vec3_4.x && vec3_5.y == vec3_4.y && vec3_5.z == vec3_4.z);

	Vector3 vec3_12(3, 4, 5);
	Vector3 vec3_13(3, 4, 5);
	Vector3 vec3_14(3, 4, 5.1);

	unitTest.test("\"==\" Operator (Equality)", vec3_12 == vec3_13 && !(vec3_12 == vec3_14));

	Vector3 vec3_6(2, 3, 4);
	Vector3 vec3_7(9, 11, 13);

	Vector3 vecOp = vec3_6 + vec3_7;
	unitTest.test("\"+\" Operator", vecOp.x == vec3_6.x + vec3_7.x && vecOp.y == vec3_6.y + vec3_7.y && vecOp.z == vec3_6.z + vec3_7.z);

	vecOp = vec3_6 - vec3_7;
	unitTest.test("\"-\" Operator", vecOp.x == vec3_6.x - vec3_7.x && vecOp.y == vec3_6.y - vec3_7.y && vecOp.z == vec3_6.z - vec3_7.z);

	vecOp = vec3_6 * vec3_7;
	unitTest.test("\"*\" Operator", vecOp.x == vec3_6.x * vec3_7.x && vecOp.y == vec3_6.y * vec3_7.y && vecOp.z == vec3_6.z * vec3_7.z);

	vecOp = vec3_6 / vec3_7;
	unitTest.test("\"/\" Operator", vecOp.x == vec3_6.x / vec3_7.x && vecOp.y == vec3_6.y / vec3_7.y && vecOp.z == vec3_6.z / vec3_7.z);

	double testDouble = 153.05;
	vecOp = vec3_6 + testDouble;
	unitTest.test("\"+\" Operator (Double)", vecOp.x == vec3_6.x + testDouble && vecOp.y == vec3_6.y + testDouble && vecOp.z == vec3_6.z + testDouble);

	vecOp = vec3_6 - 153.05;
	unitTest.test("\"-\" Operator (Double)", vecOp.x == vec3_6.x - testDouble && vecOp.y == vec3_6.y - testDouble && vecOp.z == vec3_6.z - testDouble);

	vecOp = vec3_6 * 153.05;
	unitTest.test("\"*\" Operator (Double)", vecOp.x == vec3_6.x * testDouble && vecOp.y == vec3_6.y * testDouble && vecOp.z == vec3_6.z * testDouble);

	vecOp = vec3_6 / 153.05;
	unitTest.test("\"/\" Operator (Double)", vecOp.x == vec3_6.x / testDouble && vecOp.y == vec3_6.y / testDouble && vecOp.z == vec3_6.z / testDouble);

	// Vector3: Methods
	Vector3 vec3_8(9, 8, 7);
	Vector3 vec3_9(10, 11, 12);

	vec3_8.swap(vec3_9);
	unitTest.test("Swap: swap()", vec3_8.x == 10 && vec3_8.y == 11 && vec3_8.z == 12 && vec3_9.x == 9 && vec3_9.y == 8 && vec3_9.z == 7);

	vec3_9.reset();
	unitTest.test("Reset: reset()", vec3_9.x == 0 && vec3_9.y == 0 && vec3_9.z == 0);

	Vector3 vec3_10(2, 4.74, 6);
	Vector3 vec3_11(7.56, 6, 9);

	double vecDot = vec3_10.dot(vec3_11);
	unitTest.test("Dot Product: dot()", vecDot == (vec3_10.x * vec3_11.x) + (vec3_10.y * vec3_11.y) + (vec3_10.z * vec3_11.z));

	Vector3 vecCross = vec3_10.cross(vec3_11);
	unitTest.test("Cross Product: cross()", vecCross.x == (vec3_10.y * vec3_11.z) - (vec3_10.z * vec3_11.y) && vecCross.y == (vec3_10.z * vec3_11.x) - (vec3_10.x * vec3_11.z) && vecCross.z == (vec3_10.x * vec3_11.y) - (vec3_10.y * vec3_11.x));

	// Vector3: Summary
	unitTest.report();

	// ---------- MassiveObject testing ---------- //
	std::cout << "---------------------" << std::endl;
	std::cout << "MassiveObject Testing" << std::endl;
	unitTest.reinitialize("MassiveObject Test", false);

	MassiveObject mo1;
	MassiveObject mo2(111, 222);
	MassiveObject mo3(333, 444, Vector3(1, 2, 3), Vector3(4, 5, 6));
	MassiveObject mo4(mo2);

	// MassiveObject: Getters
	unitTest.test("Id Getter: getId()", mo1.getId() != mo2.getId() && mo3.getId() != mo4.getId() && mo2.getId() != mo3.getId() && mo1.getId() != mo4.getId() && mo2.getId() != mo4.getId() && mo1.getId() != mo3.getId());
	unitTest.test("Mass Getter: getMass()", mo1.getMass() == 0.0 && mo3.getMass() == 333 && sizeof(mo2.getMass()) == sizeof(long double));
	unitTest.test("Volume Getter: getVolume()", mo1.getVolume() == 0.0 && mo2.getVolume() == 222 && sizeof(mo3.getVolume()) == sizeof(long double));
	unitTest.test("Position Getter: getPosition()", mo1.getPosition() == Vector3() && mo3.getPosition() == Vector3(1, 2, 3));
	unitTest.test("Velocity Getter: getVelocity()", mo1.getVelocity() == Vector3() && mo3.getVelocity() == Vector3(4, 5, 6));

	// MassiveObject: Constructors
	unitTest.test("Default Constructor: no params", mo1.getMass() == 0.0 && mo1.getVolume() == 0.0 && mo1.getPosition() == Vector3() && mo1.getVelocity() == Vector3());
	unitTest.test("Constructor: mass and volume", mo2.getMass() == 111 && mo2.getVolume() == 222 && mo1.getPosition() == Vector3() && mo1.getVelocity() == Vector3());
	unitTest.test("Constructor: all params", mo3.getMass() == 333 && mo3.getVolume() == 444 && mo3.getPosition() == Vector3(1, 2, 3) && mo3.getVelocity() == Vector3(4, 5, 6));
	unitTest.test("Constructor: copy", mo4.getMass() == 111 && mo4.getVolume() == 222 && mo4.getPosition() == Vector3() && mo4.getVelocity() == Vector3());
	
	// MassiveObject: Setters
	mo1.setPosition(Vector3(1010101, 2020202, 3030303));
	mo3.setMass(333333333.333);
	mo4.setVolume(1234554321);
	mo2.setVelocity(Vector3(2000.1, 3000.2, 4000.3));

	unitTest.test("Mass Setter: setMass()", mo3.getMass() == 333333333.333);
	unitTest.test("Volume Setter: setVolume()", mo4.getVolume() == 1234554321);
	unitTest.test("Position Setter: setPosition()", mo1.getPosition() == Vector3(1010101, 2020202, 3030303));
	unitTest.test("Velocity Setter: setVelocity()", mo2.getVelocity() == Vector3(2000.1, 3000.2, 4000.3));

	// MassiveObject: Helper Functions
	mo1.setMass(234234);
	mo1.setVelocity(Vector3(23, 4, 2));
	mo1.setVolume(339939);
	int id = mo1.getId();
	mo1.reset();

	unitTest.test("Reset: reset()", mo1.getPosition() == Vector3() && mo1.getVelocity() == Vector3() && mo1.getMass() == 0.0 && mo1.getVolume() == 0.0 && mo1.getId() == id);

	// MassiveObject: Summary
	unitTest.report();
}

