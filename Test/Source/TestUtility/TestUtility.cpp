#include "TestUtility.h"


using namespace std;
using namespace std::chrono;


void PrintTimeCost(const char* name, time_point<system_clock, milliseconds> startTime, time_point<system_clock, milliseconds> endTime)
{
	printf("%s: %lldms", name, (endTime - startTime).count());
}
double GetDoubleValue(const double& value)
{
	if (value == std::numeric_limits<double>::max())
	{
		return 0.0;
	}
	return value;
}
