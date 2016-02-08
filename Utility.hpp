#pragma once

#include <cmath>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF
#define M_PI 3.1415926535897932384626433832795
#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

namespace utility
{
	void clearScreen();
	void initGraphics();
}
