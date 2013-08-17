#ifndef T3D_UNITTEST_H
#define T3D_UNITTEST_H

// DEFINE_TESTFUNC(hello) {
//   ASSERT_TRUE(1 == 1);
// }
//
// int main() {
//   RUN_ALL_TEST();
//   ...
// }

#include <vector>
#include <assert.h>

typedef void (*UNITTEST_FUNC)(void);

#define RUN_ALL_TEST()  T3DTestSuite::instance().runAll()
#define DEFINE_TESTFUNC(func)											\
	void func(void);																\
	T3DTestRegister testRegister##func(func);				\
	void func(void)
#define ASSERT_TRUE(expr)													\
	T3DTestSuite::instance().assertTrue(expr, #expr, __FILE__, __LINE__)


class T3DTestSuite
{
public:
	static T3DTestSuite& instance();

	void addTest(UNITTEST_FUNC func);
	void assertTrue(bool isTrue, const char *expr, const char *fileName, int lineNo);
	void runAll();

private:
	T3DTestSuite();
	T3DTestSuite& operator=(const T3DTestSuite&);

private:
	typedef std::vector<UNITTEST_FUNC> TestFuncArray;
	TestFuncArray testArray_;
};	

class T3DTestRegister
{
public:
	T3DTestRegister(UNITTEST_FUNC func)
	{
		T3DTestSuite::instance().addTest(func);
	}

private:
	T3DTestRegister();
	T3DTestRegister& operator=(const T3DTestRegister&);
};


#endif
