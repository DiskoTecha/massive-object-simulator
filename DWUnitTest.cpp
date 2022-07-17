#include "DWUnitTest.h"

namespace dw 
{
	// Required constructor with variable initialization
	DWUnitTest::DWUnitTest(const char* testStr, bool summary)
	{
		reinitialize(testStr, summary);
	}

	// Run the test, print the result
	void DWUnitTest::test(const char* description, bool test)
	{
		if (!summaryOnly)
		{
			printf("%s: %s\n", description, (test ? dw_unit_test_pass_str : dw_unit_test_fail_str));
		}

		if (test)
		{
			++passCount;
		}
		else
		{
			++failCount;
		}
	}

	// Getters for pass and fail count
	unsigned long int DWUnitTest::getPassCount()
	{
		return passCount;
	}

	unsigned long int DWUnitTest::getFailCount()
	{
		return failCount;
	}

	// Returns result report for tests since last reinitialization
	void DWUnitTest::report()
	{
		printf("%s: Overall %s, with %ld tests that %s and %ld tests that %s\n", 
			testString, 
			(failCount == 0 ? dw_unit_test_pass_str : dw_unit_test_fail_str), 
			failCount, 
			dw_unit_test_fail_str, 
			passCount, 
			dw_unit_test_pass_str);

		fflush(stdout);
	}
	
	// Getter for the summaryOnly flag
	bool DWUnitTest::summary()
	{
		return summaryOnly;
	}

	// Setter for the summaryOnly flag
	void DWUnitTest::summary(bool summary)
	{
		summaryOnly = summary;
	}

	// Initializes the private fields
	void DWUnitTest::reinitialize(const char* testStr, bool summary)
	{
		testString = testStr;
		summaryOnly = summary;
		failCount = 0;
		passCount = 0;
	}
}
