#include <cstdio>
#include <cstring>
#include <iostream>
#include "DWUnitTest.h"
#include "MassiveObject.h"
#include "Vector3.h"
#include "Visualizer3D.h"
#include "GravitationalBodySimulator.h"
#include <cstdio>
#include <time.h>
#include <cstdlib>

using namespace dw;

void runUnitTests();
void runVisualizer(int argc, char** argv);

constexpr int object_amount = 150;

GravitationalBodySimulator gravSim;
MassiveObject objectsToMove[object_amount];
NodePath models[object_amount];
Camera* camera;
NodePath cameraGroup;

float forceMultiplier = 1000000000;
float speed = 2;
float camSpeed = 60;
Vector3 camMoveDir = Vector3();
double xBound = 5000;
double yBound = 5000;
double zBound = 5000;
int velMin = -1;
int velMax = 1;
int massMin = 2000000;
int massMax = 2500000;
int volumeMin = 1200;
int volumeMax = 5000;

bool exitProgram = false;
double mouseSensitivity = 0.2;

int main(int argc, char** argv)
{
	// Run the unit tests
	runUnitTests();

	// Run visualizer
	runVisualizer(argc, argv);

	return 0;
}

MassiveObject massiveObjectRandomizer()
{
	Vector3 pos = Vector3(rand() % (int)(xBound * 2) - xBound, rand() % (int)(yBound * 2) - yBound, rand() % (int)(zBound * 2) - zBound);
	//Vector3 vel = Vector3(rand() % (velMax - velMin) + velMin, rand() % (velMax - velMin) + velMin, rand() % (velMax - velMin) + velMin);
	Vector3 vel = Vector3();
	MassiveObject newObject = MassiveObject(rand() % (massMax - massMin) + massMin, rand() % (volumeMax - volumeMin) + volumeMin, pos, vel);
	return newObject;
}

AsyncTask::DoneStatus moveSpheresTask(GenericAsyncTask* task, void* data)
{
	double dt = dw_visualizer_3d_clock->get_dt();
	gravSim.step(dt);

	for (int i = 0; i < object_amount; ++i)
	{
		Vector3 pos = objectsToMove[i].getPosition();
		models[i].set_pos(pos.x, pos.y, pos.z);
	}


	return AsyncTask::DS_cont;
}

AsyncTask::DoneStatus moveCameraTask(GenericAsyncTask* task, void* data)
{
	LPoint3 pos = cameraGroup.get_pos();
	LQuaternion rot = cameraGroup.get_quat();
	Vector3 dir = camMoveDir.rotateByQuaternion(rot.get_i(), rot.get_j(), rot.get_k(), rot.get_r());

	cameraGroup.set_pos(pos.get_x() + dir.x * camSpeed, pos.get_y() + dir.y * camSpeed, pos.get_z() + dir.z * camSpeed);

	return AsyncTask::DS_cont;
}

void moveCamFromKeyboardEvent(const Event* event, void* data)
{
	switch (*(int*)data)
	{
	case 1:
		camMoveDir += Vector3(0, 1, 0);
		break;
	case 2:
		camMoveDir -= Vector3(1, 0, 0);
		break;
	case 3:
		camMoveDir -= Vector3(0, 1, 0);
		break;
	case 4:
		camMoveDir += Vector3(1, 0, 0);
		break;
	case 5:
		camMoveDir -= Vector3(0, 0, 1);
		break;
	case 6:
		camMoveDir += Vector3(0, 0, 1);
		break;
	case -1:
		camMoveDir -= Vector3(0, 1, 0);
		break;
	case -2:
		camMoveDir += Vector3(1, 0, 0);
		break;
	case -3:
		camMoveDir += Vector3(0, 1, 0);
		break;
	case -4:
		camMoveDir -= Vector3(1, 0, 0);
		break;
	case -5:
		camMoveDir += Vector3(0, 0, 1);
		break;
	case -6:
		camMoveDir -= Vector3(0, 0, 1);
		break;
	default:
		break;
	}
}

void moveCamOnBoundaryEvent(const Event* event, void* data)
{
	float fov = camera->get_lens()->get_fov().get_x();
	float tanFov = std::tan(fov * 3.1415926 / 180);

	if (*(int*)data == 1)
	{
		// Move to x boundary and account for fov to see most of the bounding box with y = z = 0, rotate towards origin
		cameraGroup.set_pos(yBound / tanFov + xBound, 0, 0);
		cameraGroup.set_hpr(90, 0, 0);
	}
	else if (*(int*)data == 2)
	{
		// Move to y boundary and account for fov to see most of the bounding box with x = z = 0, rotate towards origin
		cameraGroup.set_pos(0, xBound / tanFov + yBound, 0);
		cameraGroup.set_hpr(180, 0, 0);
	}
	else if (*(int*)data == 3)
	{
		// Move to z boundary and account for fov to see most of the bounding box with x = y = 0, rotate towards origin
		cameraGroup.set_pos(0, 0, xBound / tanFov + zBound);
		cameraGroup.set_hpr(0, 270, 0);
	}
}

void exitEvent(const Event* event, void* data)
{
	exitProgram = true;
}

void handleMouse(WindowFramework* window)
{
	if (window) {
		GraphicsWindow* graphicsWindow = window->get_graphics_window();
		if (graphicsWindow) {
			double mouseXDif = graphicsWindow->get_pointer(0).get_x() - graphicsWindow->get_properties().get_x_size() / 2;
			double mouseYDif = graphicsWindow->get_pointer(0).get_y() - graphicsWindow->get_properties().get_y_size() / 2;
			std::cout << "mouseXDif = " << mouseXDif << std::endl;
			std::cout << "mouseYDif = " << mouseYDif << std::endl;

			cameraGroup.set_hpr(cameraGroup, -mouseXDif * mouseSensitivity, -mouseYDif * mouseSensitivity, 0);

			graphicsWindow->move_pointer(0, graphicsWindow->get_properties().get_x_size() / 2, graphicsWindow->get_properties().get_y_size() / 2);
		}
	}
}

void runVisualizer(int argc, char** argv)
{
	// Visualize
	Visualizer3D* visualizer = Visualizer3D::getInstance("Testin it out");
	visualizer->init(argc, argv);

	for (int i = 0; i < object_amount; ++i)
	{
		objectsToMove[i] = massiveObjectRandomizer();
		float r = std::cbrt(3 * objectsToMove[i].getVolume() / (4 * 3.14159));
		models[i] = visualizer->loadModel("../../models/sphere", Vector3(r, r, r), objectsToMove[i].getPosition());
	}

	gravSim = GravitationalBodySimulator(objectsToMove, object_amount, forceMultiplier);
	gravSim.setBounds(BoundsAction::BOUNCE, Vector3(-xBound, -yBound, -zBound), Vector3(xBound, yBound, zBound));

	camera = visualizer->getWindow()->get_camera(0);
	cameraGroup = *visualizer->getCameraGroup();

	visualizer->addTask("Move Spheres Task", &moveSpheresTask);
	visualizer->addTask("Move Camera Task", &moveCameraTask);

	visualizer->getWindow()->enable_keyboard();

	// Set relative mouse mode, hide cursor, enable fullscreen
	WindowProperties props = visualizer->getWindow()->get_graphics_window()->get_properties();
	props.set_cursor_hidden(true);
	props.set_mouse_mode(WindowProperties::M_relative);
	props.set_fullscreen(true);
	visualizer->getWindow()->get_graphics_window()->request_properties(props);

	// Key events for camera on boundary keys ('1', '2', '3')
	int x = 1;
	int y = 2;
	int z = 3;
	void* xData = &x;
	void* yData = &y;
	void* zData = &z;
	visualizer->addKeyEvent("1", "Cam on X Boundary", moveCamOnBoundaryEvent, xData);
	visualizer->addKeyEvent("2", "Cam on Y Boundary", moveCamOnBoundaryEvent, yData);
	visualizer->addKeyEvent("3", "Cam on Z Boundary", moveCamOnBoundaryEvent, zData);

	// Key events for camera movement keys ('w', 'a', 's', 'd')
	int wDown = 1;
	int wUp = -1;
	int aDown = 2;
	int aUp = -2;
	int sDown = 3;
	int sUp = -3;
	int dDown = 4;
	int dUp = -4;
	int qDown = 5;
	int qUp = -5;
	int eDown = 6;
	int eUp = -6;
	void* wDownData = &wDown;
	void* wUpData = &wUp;
	void* aDownData = &aDown;
	void* aUpData = &aUp;
	void* sDownData = &sDown;
	void* sUpData = &sUp;
	void* dDownData = &dDown;
	void* dUpData = &dUp;
	void* qDownData = &qDown;
	void* qUpData = &qUp;
	void* eDownData = &eDown;
	void* eUpData = &eUp;
	visualizer->addKeyEvent("w", "MoveForward", moveCamFromKeyboardEvent, wDownData);
	visualizer->addKeyEvent("w-up", "StopMoveForward", moveCamFromKeyboardEvent, wUpData);
	visualizer->addKeyEvent("a", "MoveLeft", moveCamFromKeyboardEvent, aDownData);
	visualizer->addKeyEvent("a-up", "StopMoveLeft", moveCamFromKeyboardEvent, aUpData);
	visualizer->addKeyEvent("s", "MoveBack", moveCamFromKeyboardEvent, sDownData);
	visualizer->addKeyEvent("s-up", "StopMoveBack", moveCamFromKeyboardEvent, sUpData);
	visualizer->addKeyEvent("d", "MoveRight", moveCamFromKeyboardEvent, dDownData);
	visualizer->addKeyEvent("d-up", "StopMoveRight", moveCamFromKeyboardEvent, dUpData);
	visualizer->addKeyEvent("q", "MoveDown", moveCamFromKeyboardEvent, qDownData);
	visualizer->addKeyEvent("q-up", "StopMoveDown", moveCamFromKeyboardEvent, qUpData);
	visualizer->addKeyEvent("e", "MoveUp", moveCamFromKeyboardEvent, eDownData);
	visualizer->addKeyEvent("e-up", "StopMoveUp", moveCamFromKeyboardEvent, eUpData);

	// Add exit event
	visualizer->addKeyEvent("escape", "QuitApplication", exitEvent);

	if (visualizer->getWindow()) {
		GraphicsWindow* graphicsWindow = visualizer->getWindow()->get_graphics_window();
		if (graphicsWindow) {
			// Set mouse to center of graphics window (in fullscreen, basically the center of the screen)
			graphicsWindow->move_pointer(0, graphicsWindow->get_properties().get_x_size() / 2, graphicsWindow->get_properties().get_y_size() / 2);
		}
	}

	while (!exitProgram)
	{
		handleMouse(visualizer->getWindow());
		dw_visualizer_3d_task_manager->poll();
	}

	visualizer->shutdown();
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

