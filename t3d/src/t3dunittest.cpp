#include "t3dunittest.h"

T3DTestSuite& T3DTestSuite::instance()
{
	static T3DTestSuite s_instance;
	return s_instance;
}

T3DTestSuite::T3DTestSuite()
{
}

void T3DTestSuite::addTest(UNITTEST_FUNC func)
{
	testArray_.push_back(func);
}

void T3DTestSuite::assertTrue(bool isTrue, const char *expr, const char *fileName, int lineNo)
{
	if (!isTrue)
		printf("FAIL: %s(%d), %s\n", fileName, lineNo, expr);
}

void T3DTestSuite::runAll()
{
	TestFuncArray::iterator it = testArray_.begin();
	while (it != testArray_.end())
	{
		(*it)();
		++it;
	}
}

