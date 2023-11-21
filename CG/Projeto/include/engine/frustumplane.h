#ifndef __FRUSTUMPLANE__
#define __FRUSTUMPLANE__

#include <vector>
#include "../point.h"

using namespace std;

class FrustumPlane {
	public:
		float A;
		float B;
		float C;
		float D;

		FrustumPlane();
		FrustumPlane(float A, float B, float C, float D);
		float distance(Point(p));
		int boxInNormalSide(vector<Point> box);
};

#endif