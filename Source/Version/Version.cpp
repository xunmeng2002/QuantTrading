#include "Version.h"
#include <cstring>
#include <string>

extern const char* Version;
extern const char* BuildTimeStamp;

void ShowVersion(int argc, const char* argv[])
{
	if ((argc == 2) && (!strcmp(argv[1], "-v")))
	{
		printf("%s: Version:%s, BuildTime:%s\n", argv[0], Version, BuildTimeStamp);
		exit(0);
	}
}

