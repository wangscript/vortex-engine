#include "vtx_assertions.h"
#include <iostream>

void reportAssertionFailure(const char *expr, const char *file, long line)
{
	using namespace std;
	cout << "== Assertion failed ==" << endl << expr << endl << file << ": " << line;
}