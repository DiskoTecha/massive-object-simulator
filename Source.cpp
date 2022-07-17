#include <cstdio>
#include <cstring>
#include <iostream>
#include "DWUnitTest.h"
#include "MassiveObject.h"
#include "Vector3.h"

using namespace dw;

int main()
{
	DWUnitTest unitTest("Vector3 Test", false);
	printf("DWUnitTest Version: %s\n", unitTest.version());

	// ---------- Vector3 testing ---------- //

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

	unitTest.test("C String Print: c_str()", !strncmp(vec3_8.c_str(), "<10.000000, 11.000000, 12.000000>", sizeof(vec3_8.c_str())));

	Vector3 vec3_10(2, 4.74, 6);
	Vector3 vec3_11(7.56, 6, 9);

	double vecDot = vec3_10.dot(vec3_11);
	unitTest.test("Dot Product: dot()", vecDot == (vec3_10.x * vec3_11.x) + (vec3_10.y * vec3_11.y) + (vec3_10.z * vec3_11.z));

	Vector3 vecCross = vec3_10.cross(vec3_11);
	unitTest.test("Cross Product: cross()", vecCross.x == (vec3_10.y * vec3_11.z) - (vec3_10.z * vec3_11.y) && vecCross.y == (vec3_10.z * vec3_11.x) - (vec3_10.x * vec3_11.z) && vecCross.z == (vec3_10.x * vec3_11.y) - (vec3_10.y * vec3_11.x));

	// Version getter
	unitTest.test("Version Getter: version()", !strncmp(vecCross.version(), DW_VECTOR_3_VERSION, sizeof(vecCross.version())));

	// Vector3: Summary
	unitTest.report();

	printf("\n1.989e60 * 3 = %f", 1.989e60 * 3);
}