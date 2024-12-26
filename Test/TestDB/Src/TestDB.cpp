#include <iostream>
#include "Mdb.h"

using namespace std;
using namespace mdb;

int main(int argc, char* argv[])
{
	Mdb* mdb = new Mdb();
	mdb->InitDB();
	return 0;
}
