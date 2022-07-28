#ifndef DW_UNIT_TEST
#define DW_UNIT_TEST

// Version number macro
#define DW_UNIT_TEST_VERSION "1.0.2"

#include <cstdio>

constexpr const char* dw_unit_test_pass_str = "Pass";
constexpr const char* dw_unit_test_fail_str = "Fail";

namespace dw
{
	class DWUnitTest
	{
		const char* testString;
		unsigned long int passCount = 0;
		unsigned long int failCount = 0;
		bool summaryOnly = false;

		// Disallowing use of default, copy, and assignment constructors
		DWUnitTest() {};
		DWUnitTest(DWUnitTest&);
		DWUnitTest operator = (DWUnitTest&);

	public:
		DWUnitTest(const char* testStr, bool summary = false);
		void test(const char*, bool);
		unsigned long int getPassCount();
		unsigned long int getFailCount();
		void report();
		bool summary();
		void summary(bool);
		static const char* version() { return DW_UNIT_TEST_VERSION; }
		void reinitialize(const char* testStr, bool summary = false);
	};
}

#endif