#include <QtTest>

#include "channel_test.h"
#include "phisical_engine_test.h"

#define ADD_TEST( className ) \
{ \
className test; \
status |= QTest::qExec(&test, argc, argv); \
} \

int main(int argc, char** argv)
{
   int status = 0;

   ADD_TEST(CChannelTest)
   ADD_TEST(CPhisicalEngineTest)

   return status;
}
